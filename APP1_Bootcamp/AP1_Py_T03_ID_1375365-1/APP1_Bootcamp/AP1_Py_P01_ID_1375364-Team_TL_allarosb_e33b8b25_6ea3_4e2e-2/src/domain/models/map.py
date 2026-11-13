# domain/models/map.py
from dataclasses import dataclass, field
from typing import List, Optional, Dict
from domain.models.item import Item


@dataclass(frozen=True)
class Position:
    """Immutable coordinate representation on the game grid."""
    x: int
    y: int


@dataclass
class Room:
    """Represents one of the 9 partition sectors in the 3x3 layout."""
    id: int  # Sector identifier (0 to 8)
    top_left: Position
    width: int
    height: int
    is_maze: bool = False  # True for winding corridor sectors


@dataclass
class Corridor:
    """Represents a connected path linking different rooms together."""
    path: List[Position] = field(default_factory=list)


@dataclass
class Level:
    """A complete single floor containing the rooms and corridors."""
    depth: int
    width: int = 80  # Standard terminal width
    height: int = 24  # Standard terminal height

    rooms: List[Room] = field(default_factory=list)
    corridors: List[Corridor] = field(default_factory=list)

    items_map: Dict[Position, "Item"] = field(default_factory=dict)
    enemies_list: List["Enemy"] = field(default_factory=list)
    exit_position: Optional[Position] = None
    starting_room: Optional[Room] = None

    def find_valid_neighbor_tile(self, center: Position) -> Position:
        """
        Scans all 8 neighboring tiles around the player to find an open spot for dropped items.
        Ensures items never clip into room border walls or outside corridors.
        """
        directions = [
            (-1, -1), (0, -1), (1, -1),
            (-1, 0), (1, 0),
            (-1, 1), (0, 1), (1, 1)
        ]

        for dx, dy in directions:
            neighbor = Position(center.x + dx, center.y + dy)

            # 1. Ensure it stays within terminal map boundaries
            if not (0 <= neighbor.x < self.width and 0 <= neighbor.y < self.height):
                continue

            # 2. Check that the tile doesn't already contain another item
            if neighbor in self.items_map:
                continue

            # 3. Verify it is a valid walkable floor tile (Not a wall)
            is_walkable = False

            # Check room interiors (shrunk by 1 tile on all edges to skip the wall borders)
            for room in self.rooms:
                if (room.top_left.x + 1 <= neighbor.x < room.top_left.x + room.width - 1 and
                        room.top_left.y + 1 <= neighbor.y < room.top_left.y + room.height - 1):
                    is_walkable = True
                    break

            # Check corridor paths (corridors are pure floor arrays, no padding needed)
            if not is_walkable:
                for corridor in self.corridors:
                    if neighbor in corridor.path:
                        is_walkable = True
                        break

            if is_walkable:
                return neighbor

        # Fallback to the player's exact spot if all neighbors are completely full or blocked
        return center
