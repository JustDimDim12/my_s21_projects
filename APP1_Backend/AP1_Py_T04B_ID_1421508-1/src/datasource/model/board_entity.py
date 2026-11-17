from sqlalchemy import String, ForeignKey
from sqlalchemy.dialects.postgresql import ARRAY, INTEGER
from sqlalchemy.orm import Mapped, mapped_column
from datasource.model.base import Base

class BoardEntity(Base):
    __tablename__ = "board"

    game_uuid: Mapped[str] = mapped_column(String(36), ForeignKey("games.uuid", ondelete="CASCADE"), primary_key=True)
    cells: Mapped[list[int]] = mapped_column(ARRAY(INTEGER), nullable=False)

    def to_matrix(self) -> list[list[int]]:
        flat = list(self.cells)
        return [flat[i:i + 3] for i in range(0, 9, 3)]

    @classmethod
    def from_matrix(cls, game_uuid: str, matrix: list[list[int]]) -> "BoardEntity":
        flat = [c for row in matrix for c in row]
        return cls(game_uuid=game_uuid, cells=flat)