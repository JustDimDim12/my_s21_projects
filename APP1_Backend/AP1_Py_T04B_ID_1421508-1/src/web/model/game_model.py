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
    state: str
    user_uuid: UUID
    opponent_uuid: UUID | None
    current_player_uuid: UUID | None
    winner_uuid: UUID | None
    player_mark: str
    opponent_mark: str

    def to_json(self) -> dict:
        return {
            "uuid": str(self.uuid),
            "board": self.board,
            "state": self.state,
            "user_uuid": str(self.user_uuid),
            "opponent_uuid": str(self.opponent_uuid) if self.opponent_uuid else None,
            "current_player_uuid": str(self.current_player_uuid) if self.current_player_uuid else None,
            "winner_uuid": str(self.winner_uuid) if self.winner_uuid else None,
            "player_mark": self.player_mark,
            "opponent_mark": self.opponent_mark,
        }