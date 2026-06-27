# domain/services/session.py
from dataclasses import dataclass, field
from typing import List, Optional, Dict, Any
from domain.models.characters import Character, Enemy
from domain.models.map import Level, Position, Room, Corridor
from domain.models.item import Item, use_consumable_item
from domain.models.visibility import VisibilityMap
from domain.services.combat import CombatEngine
from domain.services.enemy_ai import EnemyAIEngine
from domain.services.fov import FOVEngine
from domain.services import DungeonGenerator
from domain.services.difficulty_balancer import DifficultyBalancer


@dataclass
class GameSession:
    """The root coordinator that manages a single active playthrough run."""
    player: Character
    current_level: Optional[Level] = None
    level_generator: Optional[DungeonGenerator] = None
    dungeon_history: List[Level] = field(default_factory=list)
    is_active: bool = True
    score: int = 0

    storage_engine: Any = None
    # Leaderboard tracking storage table
    # Stores finished runs as a list of dicts: [{"depth": X, "treasure": Y}, ...]
    high_scores: List[Dict[str, int]] = field(default_factory=list)

    # Kept independent of the Level structures
    visibility: VisibilityMap = field(default_factory=VisibilityMap)

    def descend_level(self, next_level: Level) -> None:
        """Pushes the current floor to history and transitions to the new level depth."""
        if self.current_level is not None:
            self.dungeon_history.append(self.current_level)
        self.current_level = next_level

        # clear field
        self.visibility.discovered_tiles.clear()
        FOVEngine.calculate_visibility(self.player.position, next_level, self.visibility)
        # AUTOMATIC AUTO-SAVE TRIGGER
        if self.storage_engine:
            self.storage_engine.save_session_state(self.to_serialized_dict())

    def add_score(self, points: int) -> None:
        """Safely increments the player's total value score (e.g., collecting gold)."""
        if points > 0:
            self.score += points

    def end_session(self) -> None:
        """Flags the current game session as over (due to death or victory)."""
        self.is_active = False
        self.record_run_ended()
        if self.storage_engine:
            self.storage_engine.clear_save_file()
            self.storage_engine.save_scores(self.high_scores)

    def record_run_ended(self) -> None:
        """Saves current progress into the leaderboard, sorted by treasure count."""
        # Grab depth from current floor if available, otherwise default to history length + 1
        depth_reached = self.current_level.depth if self.current_level else (len(self.dungeon_history) + 1)

        run_data = {
            "treasure": self.player.treasure_collected,
            "depth": depth_reached,
            "enemies_defeated": self.player.enemies_defeated,
            "food_consumed": self.player.food_consumed,
            "elixirs_used": self.player.elixirs_used,
            "scrolls_read": self.player.scrolls_read,
            "attacks_made": self.player.attacks_made,
            "hits_taken": self.player.hits_taken,
            "tiles_traversed": self.player.tiles_traversed
        }
        self.high_scores.append(run_data)

        # Task 2 Requirement: Sort the table strictly by total treasure collected descending
        self.high_scores.sort(key=lambda run: run["treasure"], reverse=True)

    def _is_walkable_tile(self, pos: Position) -> bool:
        """
        Validates if a target position is a legal walkable tile.
        Returns True if the position is inside a room floor or on a corridor path.
        """
        if not self.current_level:
            return False

        # 1. Check if the coordinate sits inside any valid room's inner walls
        for room in self.current_level.rooms:
            if room.is_maze:
                # If a sector is flagged as a maze tile, its top-left root is a walkway
                if room.top_left == pos:
                    return True
            else:
                # Standard Room: Walkable only if strictly inside the inner walls
                inside_x = room.top_left.x < pos.x < room.top_left.x + room.width - 1
                inside_y = room.top_left.y < pos.y < room.top_left.y + room.height - 1
                if inside_x and inside_y:
                    return True

        # 2. Check if the coordinate matches any carved corridor path pixel
        for corridor in self.current_level.corridors:
            if pos in corridor.path:
                return True

        return False

    def process_turn_actions(self, target_position: Position, game_log: List[str]) -> None:
        """Executes a single game turn loop triggered by a player action."""
        if not self.is_active or not self.current_level:
            return

        # Calculate fresh visibility matrices on turn start
        FOVEngine.calculate_visibility(self.player.position, self.current_level, self.visibility)

        # 1. Handle Sleep Status Constraints
        if self.player.sleep_turns > 0:
            self.player.sleep_turns -= 1
            game_log.append("You are fast asleep and cannot move!")
            self._resolve_monster_turns(game_log)
            self.player.tick_elixirs()
            return

        # 2. Check Combat Collision Trigger vs Map Grid Movement
        collided_enemy = next((e for e in self.current_level.enemies_list if e.position == target_position), None)

        if collided_enemy:

            # awake mimic
            if collided_enemy.is_mimic and not collided_enemy.is_awake:
                collided_enemy.is_awake = True
                # collided_enemy.hostility = 4
                game_log.append("The Mimic reveals itself!")

            self.player.attacks_made += 1
            attack_result = CombatEngine.resolve_player_attack(self.player, collided_enemy)
            game_log.append(attack_result)
            if collided_enemy.health <= 0:
                self.current_level.enemies_list.remove(collided_enemy)
                self.player.enemies_defeated += 1
                # Keep your score property synced up with the newly gained treasure points
                self.score = self.player.treasure_collected
        else:
            # Check wall collisions before moving!
            if self._is_walkable_tile(target_position):
                self.player.position = target_position
                self.player.tiles_traversed += 1
                self._handle_item_pickup_triggers(game_log)
            else:
                # Block the movement, send a notification, and stop turn sequence
                game_log.append("Ouch! A solid stone wall blocks your path.")
                return  # Exit early: Your turn isn't wasted, monsters stay idle!

        # 3. Check Level Advancement Exit Thresholds
        if self.player.position == self.current_level.exit_position:
            # Outer game coordinator checks this state to call generator.generate_level()
            if self.current_level.depth >= 21:
                game_log.append("VICTORY! You found the final exit and escaped the dungeon!")
                self.end_session()
                return
            else:
                game_log.append("You step on the stairs and prepare to descend...")
                self._ascend_to_next_level(game_log)
                return

        # 4. Resolve Hostile Monster Action Cycles
        self._resolve_monster_turns(game_log)

        # 5. Tick Down Active Elixir Status Durations
        self.player.tick_elixirs()

        # 6. Check Run End Death Condition
        if self.player.current_health <= 0:
            game_log.append("Your health hit zero... You have perished!")
            self.end_session()

    # change level funcs
    def set_level_generator(self, generator: DungeonGenerator) -> None:
        self.level_generator = generator

    def _ascend_to_next_level(self, game_log: List[str]) -> None:
        """Calculates running performance telemetry via DDA, and spawns the next floor."""
        if not self.level_generator:
            game_log.append("No level generator available")
            return
        if not self.current_level:
            return
        # Determine target floor depth sequence
        next_depth = self.current_level.depth + 1
        # Fire up the Balancer engine to evaluate historical run metrics
        dda_score = DifficultyBalancer.calculate_adjustment_factor(self.player)

        # Append narrative notifications to the text log
        if dda_score > 0.3:
            game_log.append("The dungeon grows more sinister as it senses your strength...")
        elif dda_score < -0.3:
            game_log.append("The spirits of the dungeon take pity on your broken form...")

        # 4. Request a customized layout built to accommodate current performance levels
        next_level = self.level_generator.generate_level(depth=next_depth, dda_factor=dda_score)
        next_level.starting_player_max_hp = self.player.max_health

        # set position Relocate the hero actor onto a safe floor coordinate in the new starting room
        if next_level.starting_room:
            self.player.position = Position(
                next_level.starting_room.top_left.x + 2,
                next_level.starting_room.top_left.y + 2
            )

        # change level Execute the transition step (which resets fog of war and fires the auto-saver)
        self.descend_level(next_level)

        game_log.append(f"You descend to level {next_depth}.")

    def _handle_item_pickup_triggers(self, game_log: List[str]) -> None:
        """Automatically intercepts items when stepping over map positions."""
        if self.player.position in self.current_level.items_map:
            stepped_item = self.current_level.items_map[self.player.position]

            # Add item to backpack checking category capacities
            added_successfully = self.player.backpack.add_item(stepped_item)
            if added_successfully:
                game_log.append(f"Found item: {stepped_item.subtype}!")
                del self.current_level.items_map[self.player.position]
            else:
                game_log.append(f"Your inventory slots for {stepped_item.type} items are full!")

    def _resolve_monster_turns(self, game_log: List[str]) -> None:
        """Loops through active floor enemies allowing them to step or swing."""
        for enemy in list(self.current_level.enemies_list):
            # Calculate simple spatial proximity to find if monster is adjacent

            if enemy.is_mimic and not enemy.is_awake:
                continue

            dist_x = abs(enemy.position.x - self.player.position.x)
            dist_y = abs(enemy.position.y - self.player.position.y)

            if dist_x <= 1 and dist_y <= 1:
                health_before = self.player.current_health

                attack_log = CombatEngine.resolve_enemy_attack(enemy, self.player)
                game_log.append(attack_log)
                # If player health dropped, they took a hit
                if self.player.current_health < health_before:
                    self.player.hits_taken += 1
            else:
                EnemyAIEngine.process_enemy_turn(enemy, self.player, self.current_level)

    def unequip_current_weapon_to_backpack(self) -> str:
        """
        Domain Use Case: Player wants to unequip their weapon without dropping it (Choice '0').
        """
        if not self.player.current_weapon:
            return "Your hands are already empty!"

        old_weapon_name = self.player.current_weapon.subtype
        # Attempt to put back in backpack. Returns the item if backpack is full.
        dropped_item = self.player.unequip_weapon(drop_on_ground=False)

        if dropped_item:
            # Backpack was full, fallback to dropping it on a neighbor tile
            drop_pos = self.current_level.find_valid_neighbor_tile(self.player.position)
            self.current_level.items_map[drop_pos] = dropped_item
            return f"Backpack full! Unequipped and dropped {old_weapon_name} nearby."

        return f"Unequipped {old_weapon_name} back into your backpack."

    def equip_weapon_from_backpack(self, weapon_item: Item) -> str:
        """
        Domain Use Case: Player selects a weapon from their inventory to equip (Choices '1'-'9').
        """
        log_messages = []

        # 1. If already holding a weapon, unequip it and force-drop it onto a neighboring tile
        if self.player.current_weapon:
            old_weapon = self.player.unequip_weapon(drop_on_ground=True)
            if old_weapon:
                drop_pos = self.current_level.find_valid_neighbor_tile(self.player.position)
                self.current_level.items_map[drop_pos] = old_weapon
                log_messages.append(f"Dropped your old weapon ({old_weapon.subtype}) on the ground.")

        # 2. Equip the new weapon and remove it from the backpack array
        self.player.current_weapon = weapon_item
        self.player.backpack.remove_item(weapon_item)
        log_messages.append(f"Equipped: {weapon_item.subtype}")

        return " ".join(log_messages)

    def to_serialized_dict(self) -> Dict[str, Any]:
        """Translates the deep internal domain architecture state into simple dictionary primitives."""
        if not self.current_level:
            return {}

            # 1. Serialize Room Layout Structures
        rooms_serialized = []
        for room in self.current_level.rooms:
            rooms_serialized.append({
                "id": getattr(room, "id", 0),
                "x": room.top_left.x,
                "y": room.top_left.y,
                "width": room.width,
                "height": room.height,
                "is_maze": getattr(room, "is_maze", False)
            })

        # 2. Serialize Corridor Paths
        corridors_serialized = []
        for corridor in self.current_level.corridors:
            corridors_serialized.append({
                "path": [{"x": pos.x, "y": pos.y} for pos in corridor.path]
            })

        # 3. Serialize items, enemies, backpack, and elixirs (Keep your existing loops here)
        backpack_serialized = [
            {
                "type": item.type,
                "subtype": item.subtype,
                "health": item.health,
                "max_health": item.max_health,
                "dexterity": item.dexterity,
                "strength": item.strength,
                "value": item.value
            } for item in self.player.backpack.items
        ]

        current_weapon_serialized = None
        if self.player.current_weapon:
            w = self.player.current_weapon
            current_weapon_serialized = {"type": w.type, "subtype": w.subtype, "health": w.health,
                                         "max_health": w.max_health, "dexterity": w.dexterity, "strength": w.strength,
                                         "value": w.value}

        active_elixirs_serialized = [{"attribute": ex.attribute, "modifier": ex.modifier, "duration": ex.duration} for
                                     ex in self.player.active_elixirs]
        discovered_tiles_serialized = [{"x": pos.x, "y": pos.y} for pos in self.visibility.discovered_tiles]

        items_map_serialized = [
            {"x": pos.x, "y": pos.y,
             "item": {"type": it.type, "subtype": it.subtype, "health": it.health, "max_health": it.max_health,
                      "dexterity": it.dexterity, "strength": it.strength, "value": it.value}}
            for pos, it in self.current_level.items_map.items()
        ]

        enemies_serialized = [
            {"type": en.type, "health": en.health, "max_health": en.max_health, "dexterity": en.dexterity,
             "strength": en.strength, "x": en.position.x, "y": en.position.y, "hostility": en.hostility,
             "color_char": en.color_char, "is_invisible": getattr(en, 'is_invisible', False),
             "ogre_resting": getattr(en, 'ogre_resting', False),
             "had_been_attacked": getattr(en, 'had_been_attacked', False),
             "current_room_id": getattr(en, 'current_room_id', None)}
            for en in self.current_level.enemies_list
        ]

        # Combine everything into the master save object
        return {
            "score": self.score,
            "depth": self.current_level.depth,
            "discovered_tiles": discovered_tiles_serialized,
            "player": {
                "max_health": self.player.max_health, "current_health": self.player.current_health,
                "dexterity": self.player.dexterity, "strength": self.player.strength, "x": self.player.position.x,
                "y": self.player.position.y, "experience_points": self.player.experience_points,
                "level": self.player.level, "sleep_turns": self.player.sleep_turns,
                "treasure_collected": self.player.treasure_collected, "enemies_defeated": self.player.enemies_defeated,
                "food_consumed": self.player.food_consumed, "elixirs_used": self.player.elixirs_used,
                "scrolls_read": self.player.scrolls_read, "attacks_made": self.player.attacks_made,
                "hits_taken": self.player.hits_taken, "tiles_traversed": self.player.tiles_traversed,
                "backpack": backpack_serialized, "current_weapon": current_weapon_serialized,
                "active_elixirs": active_elixirs_serialized
            },
            "level_metadata": {
                "rooms": rooms_serialized,  # save rooms
                "corridors": corridors_serialized,  # save corridors
                "items_map": items_map_serialized,
                "enemies": enemies_serialized,
                "exit_x": self.current_level.exit_position.x if self.current_level.exit_position else None,
                "exit_y": self.current_level.exit_position.y if self.current_level.exit_position else None
            }
        }

    @classmethod
    def load_from_snapshot(cls, snapshot: Dict[str, Any], generator: DungeonGenerator) -> "GameSession":
        """
        Factory method that builds complete clean domain models from a saved snapshot.
        Fulfills Task 5 by restoring attributes, positions, items, and map entities.
        """
        meta = snapshot["level_metadata"]
        regenerated_level = Level(depth=snapshot["depth"])
        p_data = snapshot["player"]

        # 1. Rehydrate pure Character Entity from saved runtime stats
        player = Character(
            max_health=p_data["max_health"],
            current_health=p_data["current_health"],
            dexterity=p_data["dexterity"],
            strength=p_data["strength"],
            position=Position(p_data["x"], p_data["y"]),
            experience_points=p_data["experience_points"],
            level=p_data["level"],
            sleep_turns=p_data["sleep_turns"],
            treasure_collected=p_data["treasure_collected"],
            enemies_defeated=p_data["enemies_defeated"],
            food_consumed=p_data["food_consumed"],
            elixirs_used=p_data["elixirs_used"],
            scrolls_read=p_data["scrolls_read"],
            attacks_made=p_data["attacks_made"],
            hits_taken=p_data["hits_taken"],
            tiles_traversed=p_data["tiles_traversed"]
        )

        # 2. Restore Backpack storage tracking array
        for item_json in p_data["backpack"]:
            player.backpack.items.append(Item(**item_json))

        # Restore currently equipped weapon object if it exists
        if p_data["current_weapon"]:
            player.current_weapon = Item(**p_data["current_weapon"])

        # Re-attach temporary active elixir durations
        from domain.models.characters import ActiveElixir
        for ex_json in p_data["active_elixirs"]:
            player.active_elixirs.append(ActiveElixir(**ex_json))

        # 3. Regenerate base physical level blueprint layout geometry
        # Manually reconstruct the exact rooms saved on disk
        regenerated_level.rooms = []
        for r_data in meta.get("rooms", []):
            room = Room(
                id=r_data.get("id", 0),
                top_left=Position(r_data["x"], r_data["y"]),
                width=r_data["width"],
                height=r_data["height"]
            )
            room.is_maze = r_data.get("is_maze", False)
            regenerated_level.rooms.append(room)

        # Manually reconstruct the exact corridors saved on disk
        regenerated_level.corridors = []
        for c_data in meta.get("corridors", []):
            corridor_path = [Position(pt["x"], pt["y"]) for pt in c_data["path"]]
            # Build your corridor instance (or append to path if your object uses standard lists)
            corridor = Corridor(path=corridor_path)
            regenerated_level.corridors.append(corridor)
        # Restore the exact exit staircase tile location
        if meta.get("exit_x") is not None and meta.get("exit_y") is not None:
            regenerated_level.exit_position = Position(meta["exit_x"], meta["exit_y"])

        # 4. Clear and restore items map and enemy trackers exactly as they were
        regenerated_level.items_map = {}
        for item_node in meta["items_map"]:
            pos = Position(item_node["x"], item_node["y"])
            it = Item(**item_node["item"])
            regenerated_level.items_map[pos] = it

        regenerated_level.enemies_list.clear()
        for en_node in snapshot["level_metadata"]["enemies"]:
            enemy = Enemy(
                type=en_node["type"],
                health=en_node["health"],
                max_health=en_node["max_health"],
                dexterity=en_node["dexterity"],
                strength=en_node["strength"],
                position=Position(en_node["x"], en_node["y"]),
                hostility=en_node["hostility"],
                color_char=en_node["color_char"],
                is_invisible=en_node["is_invisible"],
                ogre_resting=en_node["ogre_resting"],
                had_been_attacked=en_node["had_been_attacked"],
                current_room_id=en_node["current_room_id"]
            )
            regenerated_level.enemies_list.append(enemy)

        # 5. Build your active GameSession container
        session = cls(player=player, current_level=regenerated_level, level_generator=generator)
        session.score = snapshot["score"]
        session.player.position = Position(p_data["x"], p_data["y"])

        # Restore the explored visibility map layout
        session.visibility.discovered_tiles.clear()
        if "discovered_tiles" in snapshot:
            for tile_coord in snapshot["discovered_tiles"]:
                session.visibility.discovered_tiles.add(Position(tile_coord["x"], tile_coord["y"]))

        # Bind infrastructure trackers
        from data.storage import ScoreStorage
        session.storage_engine = ScoreStorage
        session.high_scores = ScoreStorage.load_scores()

        # Recalculate immediate line of sight updates centered on the loaded tile
        from domain.services.fov import FOVEngine
        FOVEngine.calculate_visibility(session.player.position, regenerated_level, session.visibility)

        return session
