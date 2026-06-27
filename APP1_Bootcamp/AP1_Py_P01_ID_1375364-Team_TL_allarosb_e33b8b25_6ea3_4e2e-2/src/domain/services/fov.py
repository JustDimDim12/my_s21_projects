# domain/services/fov.py
from domain.models.map import Position, Level, Room
from domain.models.visibility import VisibilityMap


class FOVEngine:
    @staticmethod
    def calculate_visibility(player_pos: Position, level: Level, visibility: VisibilityMap) -> None:
        """Computes line of sight and updates the shared visibility tracking record."""
        current_room = None
        for room in level.rooms:
            if not room.is_maze:
                if room.top_left.x <= player_pos.x <= room.top_left.x + room.width - 1 and \
                        room.top_left.y <= player_pos.y <= room.top_left.y + room.height - 1:
                    current_room = room
                    break

        if current_room:
            for y in range(current_room.top_left.y, current_room.top_left.y + current_room.height):
                for x in range(current_room.top_left.x, current_room.top_left.x + current_room.width):
                    visibility.discovered_tiles.add(Position(x, y))  # Writes to registry
            return

        radius = 4
        for target_y in range(player_pos.y - radius, player_pos.y + radius + 1):
            for target_x in range(player_pos.x - radius, player_pos.x + radius + 1):
                if (target_x - player_pos.x) ** 2 + (target_y - player_pos.y) ** 2 <= radius ** 2:
                    FOVEngine._trace_bresenham_ray(player_pos, Position(target_x, target_y), level, visibility)

    @staticmethod
    def _trace_bresenham_ray(start: Position, end: Position, level: Level, visibility: VisibilityMap) -> None:
        x1, y1 = start.x, start.y
        x2, y2 = end.x, end.y
        dx = abs(x2 - x1);
        dy = abs(y2 - y1)
        sx = 1 if x1 < x2 else -1;
        sy = 1 if y1 < y2 else -1
        err = dx - dy

        while True:
            current_pos = Position(x1, y1)
            visibility.discovered_tiles.add(current_pos)  # Writes to registry

            if FOVEngine._is_solid_wall_border(current_pos, level):
                break
            if x1 == x2 and y1 == y2:
                break
            e2 = 2 * err
            if e2 > -dy: err -= dy; x1 += sx
            if e2 < dx: err += dx; y1 += sy

    @staticmethod
    def _is_solid_wall_border(pos: Position, level: Level) -> bool:
        for room in level.rooms:
            if not room.is_maze:
                on_x_border = (pos.x == room.top_left.x or pos.x == room.top_left.x + room.width - 1)
                on_y_border = (pos.y == room.top_left.y or pos.y == room.top_left.y + room.height - 1)
                inside_x = room.top_left.x <= pos.x <= room.top_left.x + room.width - 1
                inside_y = room.top_left.y <= pos.y <= room.top_left.y + room.height - 1
                if (on_x_border and inside_y) or (on_y_border and inside_x):
                    return True
        return False
