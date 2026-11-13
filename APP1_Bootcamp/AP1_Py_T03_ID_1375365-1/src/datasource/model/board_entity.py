from dataclasses import dataclass
from typing import List


@dataclass
class BoardEntity:
    cells: List[List[int]]