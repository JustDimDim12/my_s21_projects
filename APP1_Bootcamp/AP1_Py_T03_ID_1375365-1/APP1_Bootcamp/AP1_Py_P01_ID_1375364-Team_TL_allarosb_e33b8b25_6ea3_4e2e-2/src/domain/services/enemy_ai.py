# domain/services/enemy_ai.py
import random
from domain.models.map import Position, Level, Room
from domain.models.characters import Enemy, Character


class EnemyAIEngine:
    @staticmethod
    def process_enemy_turn(enemy: Enemy, player: Character, level: Level):
        """Processes a single turn of movement for an enemy."""
        # Calculate distance to player on the grid
        dx_total = player.position.x - enemy.position.x
        dy_total = player.position.y - enemy.position.y
        distance = abs(dx_total) + abs(dy_total)

        # Chase Behavior (Shortest path using adjacent tiles)
        if distance <= enemy.hostility:
            # Determine primary and secondary axis steps to close the gap
            step_x = 1 if dx_total > 0 else (-1 if dx_total < 0 else 0)
            step_y = 1 if dy_total > 0 else (-1 if dy_total < 0 else 0)

            primary_target = None
            secondary_target = None

            # Prioritise closing the larger gap first to smooth out movement vectors
            if abs(dx_total) >= abs(dy_total):
                if step_x != 0: primary_target = Position(enemy.position.x + step_x, enemy.position.y)
                if step_y != 0: secondary_target = Position(enemy.position.x, enemy.position.y + step_y)
            else:
                if step_y != 0: primary_target = Position(enemy.position.x, enemy.position.y + step_y)
                if step_x != 0: secondary_target = Position(enemy.position.x + step_x, enemy.position.y)

                # Try primary step direction
            if primary_target and EnemyAIEngine._is_walkable_tile(primary_target, level):
                if enemy.type == "Ghost": enemy.is_invisible = False
                enemy.position = primary_target
                return

            # If primary is blocked by a wall, try the secondary alternative step direction
            if secondary_target and EnemyAIEngine._is_walkable_tile(secondary_target, level):
                if enemy.type == "Ghost": enemy.is_invisible = False
                enemy.position = secondary_target
                return

        # If outside aggression range, drop back to custom room-bound patterns
        # 2. Room Bound Pattern Evaluation
        if enemy.type == "Ogre":
            # Lock the Ogre into a single direction and march it 2 tiles straight
            EnemyAIEngine._execute_ogre_double_march(enemy, level)
        else:
            EnemyAIEngine._execute_wandering(enemy, level)

    @staticmethod
    def _execute_ogre_double_march(enemy: Enemy, level: Level):
        """Forces the Ogre to select one axis and walk 2 steps straight without diagonal drift."""
        room = next((r for r in level.rooms if r.id == enemy.current_room_id), None)
        if not room:
            return

        # Pick a strict 1-axis vector (No diagonals possible)
        dx, dy = random.choice([(-1, 0), (1, 0), (0, -1), (0, 1)])

        # Step 1
        target1 = Position(enemy.position.x + dx, enemy.position.y + dy)
        if EnemyAIEngine._is_walkable_tile(target1, level):
            is_in_room1 = EnemyAIEngine._is_inside_room(target1, room)
            is_in_corr1 = any(target1 in corridor.path for corridor in level.corridors)

            # Ogre can use corridors or stay inside its birth room boundaries
            if is_in_room1 or is_in_corr1:
                enemy.position = target1

                # Step 2: Offset from target1, not enemy.position!
                target2 = Position(target1.x + dx, target1.y + dy)
                if EnemyAIEngine._is_walkable_tile(target2, level):
                    is_in_room2 = EnemyAIEngine._is_inside_room(target2, room)
                    is_in_corr2 = any(target2 in corridor.path for corridor in level.corridors)

                    # Handles small rooms: if step 2 hits a wall, it stops safely at step 1
                    if is_in_room2 or is_in_corr2:
                        enemy.position = target2

    @staticmethod
    def _execute_wandering(enemy: Enemy, level: Level):
        """Applies specialized unprovoked wandering profiles within room bounds."""
        # Find the room the monster spawned in
        room = next((r for r in level.rooms if r.id == enemy.current_room_id), None)
        if not room:
            return

        # 1. Ghost Special: 20% chance to teleport randomly within its room boundaries
        if enemy.type == "Ghost":
            if random.random() < 0.20:
                enemy.position = EnemyAIEngine._get_random_inner_tile(room)
            # 30% chance to blink into invisibility while wandering unprovoked
            if not enemy.had_been_attacked:
                enemy.is_invisible = (random.random() < 0.35)
            return

        # 2. Snake Mage Special: Diagonal steps only, constantly switching up choices
        if enemy.type == "Snake Mage":
            dx, dy = random.choice([(-1, -1), (1, -1), (-1, 1), (1, 1)])
        else:
            dx, dy = random.choice([(-1, 0), (1, 0), (0, -1), (0, 1)])

        target = Position(enemy.position.x + dx, enemy.position.y + dy)

        # A monster can step here if the tile is walkable on the map layout,
        # and it's either inside their room box OR part of a carved corridor path!
        if EnemyAIEngine._is_walkable_tile(target, level):
            is_in_room = EnemyAIEngine._is_inside_room(target, room)
            is_in_corridor = any(target in corridor.path for corridor in level.corridors)

            if is_in_room or is_in_corridor:
                enemy.position = target

        # 3. Standard Wandering Profile (Zombie, Vampire, Ogre default patterns)
        # Select standard adjacent cardinally aligned paths
        dx, dy = random.choice([(-1, 0), (1, 0), (0, -1), (0, 1)])
        target = Position(enemy.position.x + dx, enemy.position.y + dy)

        if EnemyAIEngine._is_inside_room(target, room):
            enemy.position = target

    @staticmethod
    def _is_inside_room(pos: Position, room: Room) -> bool:
        """Ensures a targeted position coordinate is strictly inside inner walls."""
        return (room.top_left.x < pos.x < room.top_left.x + room.width - 1 and
                room.top_left.y < pos.y < room.top_left.y + room.height - 1)

    @staticmethod
    def _get_random_inner_tile(room: Room) -> Position:
        """Generates an inner room coord avoiding wall layouts."""
        x = random.randint(room.top_left.x + 1, room.top_left.x + room.width - 2)
        y = random.randint(room.top_left.y + 1, room.top_left.y + room.height - 2)
        return Position(x, y)

    @staticmethod
    def _is_walkable_tile(pos: Position, level: Level) -> bool:
        """Helper inside AI engine to make sure monsters respect layout walls."""
        # 1. Check if it's inside any valid standard room or a maze room root tile
        for room in level.rooms:
            if room.is_maze and room.top_left == pos:
                return True
            elif not room.is_maze:
                inside_x = room.top_left.x < pos.x < room.top_left.x + room.width - 1
                inside_y = room.top_left.y < pos.y < room.top_left.y + room.height - 1
                if inside_x and inside_y:
                    return True

        # 2. Check if it is along a carved walkable corridor path
        for corridor in level.corridors:
            if pos in corridor.path:
                return True

        return False
