from dataclasses import dataclass
from typing import List


@dataclass
class Board:
    cells: List[List[int]]

    def size(self) -> int:
        return len(self.cells)

    def copy(self) -> "Board":
        return Board(cells=[row[:] for row in self.cells])