from dataclasses import dataclass
from uuid import UUID
from enum import Enum

from domain.model.board import Board

EMPTY = 0
COMPUTER = 1
PLAYER = -1

class Error(Enum):
    e400 = 400
    e403 = 403
    e404 = 404

class GameMode(Enum):
    COMPUTER = "computer"
    PLAYER = "player"

class Mark(Enum):
    X = "X"
    O = "O"

    def another_mark(self) -> "Mark":
        return Mark.O if self == Mark.X else Mark.X

class GameState(Enum):
    WAIT = "waiting_for_players"
    TURN = "player_turn"
    DRAW = "draw"
    WIN = "player_wins"

@dataclass
class Game:
    uuid: UUID
    board: Board
    state: GameState

    user_uuid: UUID
    opponent_uuid: UUID| None
    player_mark: Mark
    opponent_mark: Mark
    current_player_uuid: UUID | None
    winner_uuid: UUID | None