from dataclasses import dataclass
from uuid import UUID

from domain.model.board import Board

EMPTY = 0
COMPUTER = 1
PLAYER = -1


@dataclass
class Game:
    uuid: UUID
    board: Board
    status: str = "playing"