from dataclasses import dataclass
from typing import List
from uuid import UUID


@dataclass
class BoardModel:
    cells: List[List[int]]


@dataclass
class GameModel:
    uuid: UUID
    board: List[List[int]]
    status: str = "playing"

    def to_json(self) -> dict:
        return {
            "uuid": str(self.uuid),
            "board": self.board,
            "status": self.status,
        }