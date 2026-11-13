from dataclasses import dataclass
from uuid import UUID
from datasource.model.board_entity import BoardEntity


@dataclass
class GameEntity:
    uuid: UUID
    board: BoardEntity
    status: str = "playing"