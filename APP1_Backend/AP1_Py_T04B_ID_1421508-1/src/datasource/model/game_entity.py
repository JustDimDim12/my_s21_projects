from datetime import datetime
from sqlalchemy import String, DateTime, func
from sqlalchemy.orm import Mapped, mapped_column, relationship
from datasource.model.board_entity import BoardEntity
from datasource.model.base import Base

class GameEntity(Base):
    __tablename__ = 'games'

    uuid: Mapped[str] = mapped_column(String(36), primary_key=True)
    state: Mapped[str] = mapped_column(String(32), nullable=False)
    user_uuid: Mapped[str] = mapped_column(String(36), nullable=False)
    opponent_uuid: Mapped[str | None] = mapped_column(String(36), nullable=True)
    current_player_uuid: Mapped[str | None] = mapped_column(String(36), nullable=True)
    winner_uuid: Mapped[str | None] = mapped_column(String(36), nullable=True)
    player_mark: Mapped[str] = mapped_column(String(1), nullable=False)
    opponent_mark: Mapped[str] = mapped_column(String(1), nullable=False)

    created_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now(), nullable=False)

    board: Mapped[BoardEntity] = relationship(
        "BoardEntity",
        uselist = False,
        cascade = "all, delete-orphan",
        lazy = "joined",
    )