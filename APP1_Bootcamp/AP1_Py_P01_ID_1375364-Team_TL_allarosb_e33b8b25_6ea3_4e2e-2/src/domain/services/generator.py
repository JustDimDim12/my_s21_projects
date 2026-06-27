# domain/services/generator.py
import random
from typing import Tuple, List
from domain import Position, Room, Level, Corridor, Enemy, Item


class DungeonGenerator:
    """Generates procedural 3x3 layout dungeon floors for Rogue."""

    def __init__(self, screen_width: int = 80, screen_height: int = 24):
        self.width = screen_width
        self.height = screen_height

        # Calculate sector bounds for the 3x3 grid layout
        self.sector_width = screen_width // 3  # ~26 characters wide
        self.sector_height = (screen_height - 2) // 3  # ~7 rows high (leaves room for UI)

    def _get_sector_offsets(self, sector_id: int) -> Tuple[int, int]:
        """Calculates the top-left (x, y) coordinates of a given sector ID (0-8)."""
        row = sector_id // 3
        col = sector_id % 3

        start_x = col * self.sector_width
        start_y = row * self.sector_height + 1  # offset down slightly for top stats UI
        return start_x, start_y

    def _get_random_point_in_room(self, room: Room) -> Position:
        """Returns a random valid floor coordinate strictly inside a room's inner walls."""
        # Add +1 and subtract -2 to avoid spawning elements directly on top of walls
        x = random.randint(room.top_left.x + 1, room.top_left.x + room.width - 2)
        y = random.randint(room.top_left.y + 1, room.top_left.y + room.height - 2)
        return Position(x, y)

    def generate_level(self, depth: int, dda_factor: float = 0.0) -> Level:
        """Creates a brand new level blueprint filled with randomized rooms."""
        level = Level(depth=depth, width=self.width, height=self.height)

        # Build the 3x3 layout rooms
        real_rooms: List[Room] = []
        for sector_id in range(9):
            start_x, start_y = self._get_sector_offsets(sector_id)

            # Always force at least 3 rooms to ensure map generation connectivity
            is_forced_room = sector_id in [0, 4, 8]
            sector_type = "room"

            if sector_type == "room":
                # Determine randomized room sizing that fits nicely inside the sector box
                # Min size: 4x4. Max size scales down slightly to leave padding between walls
                max_w = self.sector_width - 4
                max_h = self.sector_height - 3

                room_w = random.randint(5, max(5, max_w))
                room_h = random.randint(4, max(4, max_h))

                # Randomly place the room inside its allocated sector boundaries
                pad_x = random.randint(1, max(1, self.sector_width - room_w - 2))
                pad_y = random.randint(1, max(1, self.sector_height - room_h - 2))

                # Construct and attach the room
                new_room = Room(id=sector_id, top_left=Position(start_x + pad_x, start_y + pad_y), width=room_w,
                                height=room_h)
                level.rooms.append(new_room)
                real_rooms.append(new_room)

        # 2. Select separate rooms safely for Player spawn vs Level Exit
        # Shuffling guarantees we don't accidentally choose the same sector box
        random.shuffle(real_rooms)
        starting_room = real_rooms[0]
        exit_room = real_rooms[-1] if len(real_rooms) > 1 else real_rooms[0]

        level.starting_room = starting_room

        # 3. Position the Exit Staircase
        corridor_positions = set()
        for corridor in level.corridors:
            for pos in corridor.path:
                corridor_positions.add(pos)

        cardinal_offsets = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        attempts = 0
        chosen_exit = None

        while attempts < 50:
            candidate = self._get_random_point_in_room(exit_room)
            is_next_to_corridor = False

            # Check if any cardinal neighbor borders a corridor tile
            for dx, dy in cardinal_offsets:
                neighbor = Position(candidate.x + dx, candidate.y + dy)
                if neighbor in corridor_positions:
                    is_next_to_corridor = True
                    break

            if not is_next_to_corridor:
                chosen_exit = candidate
                break

            attempts += 1

        # Fallback security layout default if exit room is highly compressed
        if chosen_exit is None:
            chosen_exit = self._get_random_point_in_room(exit_room)

        level.exit_position = chosen_exit

        # 4. Populate Non-Starting Rooms with Enemies & Items (Task 2 Scaling Mechanics)
        # Deep floors = more enemies, fewer items, harder attributes
        base_enemy_chance = min(0.9, 0.3 + (depth * 0.03))  # increases with floor depth
        base_item_chance = max(0.2, 0.7 - (depth * 0.02))  # decreases with floor depth

        if dda_factor > 0:
            # Player is playing exceptionally well -> Spike enemies, starve equipment drops
            enemy_spawn_chance = min(0.95, base_enemy_chance + (dda_factor * 0.15))
            item_spawn_chance = max(0.05, base_item_chance - (dda_factor * 0.10))
            stat_scalar = 1.0 + (dda_factor * 0.25)  # Enemies get up to 25% stat boosts
        else:
            # Player is struggling -> Lower threat, drop abundant rescue packages
            enemy_spawn_chance = max(0.10, base_enemy_chance + (dda_factor * 0.20))
            item_spawn_chance = min(0.90, base_item_chance - (dda_factor * 0.25))
            # If dda_factor hits -1.0, enemies lose up to 50% of their scaling stats
            stat_scalar = max(0.50, 1.0 + (dda_factor * 0.50))

        occupied_points = {level.exit_position}

        for room in real_rooms:
            if room.id == starting_room.id:
                continue  # Starting room is free of enemies

            # Try spawning an enemy in this room
            if random.random() < enemy_spawn_chance:

                # check point
                spawn_pos = self._get_spawn_point(occupied_points, room)

                if spawn_pos is None:
                    continue

                # Base scaling stats based on level depth
                # Inject DDA stat scalar directly into base attribute boosts
                hp_boost = int((depth * 3) * stat_scalar)
                str_boost = int((depth // 2) * stat_scalar)
                dex_boost = int((depth // 3) * stat_scalar)

                # Ensure that on severe rescue floors (dda_factor < -0.7), enemy scaling
                # strength damage modifications can never exceed a safe flat cap.
                if dda_factor < -0.7:
                    str_boost = min(2, str_boost)  # Hard ceiling on high-tier attack multipliers
                    hp_boost = min(10, hp_boost)  # Keep monster health management thin

                # Choose an enemy archetype randomly
                # enemy_type = random.choice(["Mimic"])
                enemy_type = random.choice(["Zombie", "Vampire", "Ghost", "Ogre", "Snake Mage", "Mimic"])

                # Match core attribute spreads Task 2
                if enemy_type == "Zombie":
                    enemy = Enemy(
                        type="Zombie", health=18 + hp_boost, max_health=18 + hp_boost,
                        dexterity=4 + dex_boost, strength=6 + str_boost,
                        position=spawn_pos, hostility=4, color_char="z", current_room_id=room.id
                    )
                elif enemy_type == "Vampire":
                    enemy = Enemy(
                        type="Vampire", health=14 + hp_boost, max_health=14 + hp_boost,
                        dexterity=8 + dex_boost, strength=4 + str_boost,
                        position=spawn_pos, hostility=6, color_char="v", current_room_id=room.id
                    )
                elif enemy_type == "Ghost":
                    enemy = Enemy(
                        type="Ghost", health=8 + hp_boost, max_health=8 + hp_boost,
                        dexterity=9 + dex_boost, strength=2 + str_boost,
                        position=spawn_pos, hostility=3, color_char="g", current_room_id=room.id
                    )
                elif enemy_type == "Ogre":
                    enemy = Enemy(
                        type="Ogre", health=25 + hp_boost, max_health=25 + hp_boost,
                        dexterity=3 + dex_boost, strength=9 + str_boost,
                        position=spawn_pos, hostility=5, color_char="o", current_room_id=room.id
                    )
                elif enemy_type == "Snake Mage":
                    enemy = Enemy(
                        type="Snake Mage", health=12 + hp_boost, max_health=12 + hp_boost,
                        dexterity=10 + dex_boost, strength=3 + str_boost,
                        position=spawn_pos, hostility=7, color_char="s", current_room_id=room.id
                    )
                elif enemy_type == "Mimic":
                    enemy = Enemy(
                        type="Mimic", health=25 + hp_boost, max_health=25 + hp_boost,
                        dexterity=10 + dex_boost, strength=2 + str_boost, position=spawn_pos,
                        hostility=2, color_char="m", current_room_id=room.id, is_mimic=True,
                        is_awake=False, mimic_symbol=random.choice(['%', '?', '!', ')', '*'])
                    )

                level.enemies_list.append(enemy)
                occupied_points.add(spawn_pos)

            # Try spawning an item in this room
            if random.random() < item_spawn_chance:

                item_pos = self._get_spawn_point(occupied_points, room)

                if item_pos is None:
                    continue

                # Ensure we aren't stacking items directly on top of an enemy spawn
                if any(e.position == item_pos for e in level.enemies_list):
                    continue

                if dda_factor < -0.4:
                    # Player is critically hurting! Skew choices to force-feed healing supplies
                    item_type = random.choices(["food", "elixir", "scroll", "weapon"], weights=[60, 20, 10, 10])[0]
                else:
                    # Standard rolled weights we configured earlier
                    item_type = random.choices(["food", "elixir", "scroll", "weapon"], weights=[35, 25, 15, 25])[0]

                if item_type == "food":
                    subtypes = ["Basic Ration", "Tasty Ration", "Lembas Bread"]
                    chosen_base = random.choice(subtypes)
                    food_subtype = f"Floor {depth} {chosen_base}"
                    hp_gain = 5 + (depth * 2)  # Deeper food restores more HP to face harder hazards
                    new_item = Item(type="food", subtype=food_subtype, health=hp_gain)

                elif item_type == "elixir":
                    # Choose exactly one target attribute loop to modify
                    stat_target = random.choice(["max_health", "dexterity", "strength"])
                    stat_mult = max(1, depth // 4)
                    # Assign values based on the rolled stat target
                    h_boost = (5 * stat_mult) if stat_target == "max_health" else 0
                    d_boost = (2 * stat_mult) if stat_target == "dexterity" else 0
                    s_boost = (3 * stat_mult) if stat_target == "strength" else 0

                    # Format dynamic subtype labels (e.g., "Floor 3 Elixir of Might")
                    label_map = {"max_health": "Vitality", "dexterity": "Reflexes", "strength": "Might"}
                    elixir_subtype = f"Floor {depth} Elixir of {label_map[stat_target]}"

                    new_item = Item(
                        type="elixir",
                        subtype=elixir_subtype,
                        health=0,
                        max_health=h_boost,
                        dexterity=d_boost,
                        strength=s_boost
                    )

                elif item_type == "scroll":
                    # Choose exactly one target attribute loop to modify
                    # If the player's max health is under 15, force the target
                    if hasattr(level, "starting_player_max_hp") and level.starting_player_max_hp < 15:
                        stat_target = "max_health"
                    else:
                        stat_target = random.choice(["max_health", "dexterity", "strength"])
                    stat_mult = max(1, depth // 4)

                    # 2. Assign values based on the rolled stat target
                    h_boost = (4 * stat_mult) if stat_target == "max_health" else 0
                    d_boost = (1 * stat_mult) if stat_target == "dexterity" else 0
                    s_boost = (2 * stat_mult) if stat_target == "strength" else 0

                    # 3. Format dynamic subtype labels (e.g., "Floor 5 Scroll of Power")
                    label_map = {"max_health": "Tome of Vitality", "dexterity": "Scripture of Reflexes",
                                 "strength": "Glyph of Power"}
                    scroll_subtype = f"Floor {depth} {label_map[stat_target]}"

                    new_item = Item(
                        type="scroll",
                        subtype=scroll_subtype,
                        health=0,
                        max_health=h_boost,
                        dexterity=d_boost,
                        strength=s_boost
                    )

                elif item_type == "weapon":
                    # List of weapons available: (Base Weapon Name, Base Damage Value)
                    weapons_pool = [
                        ("Rusty Dagger", 2),
                        ("Shortsword", 4),
                        ("Mace", 6),
                        ("Broadsword", 9),
                        ("Halberd", 12),
                        ("Executioner Blade", 16)
                    ]
                    # 1. Tier Locking: Advanced base weapons unlock on deeper floors
                    # Floors 1-2: Rusty Daggers & Shortswords. Floor 12+: Executioner Blades.
                    max_pool_index = min(len(weapons_pool), (depth // 3) + 2)
                    available_weapons = weapons_pool[:max_pool_index]
                    base_name, base_dmg = random.choice(available_weapons)

                    # 2. Enchantment Scaling: Roll dynamic prefixes (+1, +2) scaling directly with depth
                    enchantment = random.randint(0, depth // 5)
                    ench_label = f" +{enchantment}" if enchantment > 0 else ""

                    # 3. Object Compilation: Map final damage stat right into the model's strength field
                    new_item = Item(
                        type="weapon",
                        subtype=f"{base_name}{ench_label}",
                        strength=base_dmg + enchantment
                    )

                level.items_map[item_pos] = new_item
                occupied_points.add(item_pos)

        self._connect_all_rooms(level)

        return level

    def _create_corridor_path(self, start_pos: Position, end_pos: Position) -> Corridor:
        """
        Generates step-by-step coordinates linking two points on the grid.
        Carves an L-shaped path (horizontal then vertical) to ensure walkability.
        """
        path_positions = []

        # 1. Carve horizontally from start_x to end_x
        step_x = 1 if end_pos.x >= start_pos.x else -1
        for x in range(start_pos.x, end_pos.x + step_x, step_x):
            path_positions.append(Position(x, start_pos.y))

        # 2. Carve vertically from start_y to end_y
        step_y = 1 if end_pos.y >= start_pos.y else -1
        # Start from start_y + step_y since the corner turning pixel is already carved
        for y in range(start_pos.y + step_y, end_pos.y + step_y, step_y):
            path_positions.append(Position(end_pos.x, y))

        return Corridor(path=path_positions)

    def _connect_all_rooms(self, level: Level) -> None:
        """
        Builds a guaranteed spanning graph linking neighboring rooms together.
        Ensures the complete 3x3 layout contains zero isolated segments.
        """
        # Define a list of sector ID pairs that form a continuous snake path through the 3x3 grid
        # Connecting: 0-1-2-5-4-3-6-7-8
        connections = [(0, 1), (1, 2), (2, 5), (5, 4), (4, 3), (3, 6), (6, 7), (7, 8)]

        for start_id, end_id in connections:
            # Find the generated rooms belonging to these sectors
            room_a = next((r for r in level.rooms if r.id == start_id), None)
            room_b = next((r for r in level.rooms if r.id == end_id), None)

            if room_a and room_b:
                # Grab the center point coordinates of each room to connect them cleanly
                center_a = Position(room_a.top_left.x + room_a.width // 2, room_a.top_left.y + room_a.height // 2)
                center_b = Position(room_b.top_left.x + room_b.width // 2, room_b.top_left.y + room_b.height // 2)

                # Generate geometry path and append directly to the level corridors tracker
                new_corridor = self._create_corridor_path(center_a, center_b)
                level.corridors.append(new_corridor)

    def _get_spawn_point(self, occupied_points: set, room: Room) -> Position | None:
        spawn_attempts = 50
        attempts = 0
        point = self._get_random_point_in_room(room)

        while point in occupied_points and attempts < spawn_attempts:
            point = self._get_random_point_in_room(room)
            attempts += 1

        if attempts == spawn_attempts:
            return None
        else:
            return point