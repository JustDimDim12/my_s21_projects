from datetime import datetime
from sqlalchemy import String, DateTime, func
from sqlalchemy.orm import Mapped, mapped_column
from dataclasses import dataclass
from datasource.model.base import Base

class UserEntity(Base):
    __tablename__ = "users"

    uuid: Mapped[str] = mapped_column(String(36), primary_key=True)
    login: Mapped[str] = mapped_column(String(64), nullable=False, unique=True, index=True)
    password_hash: Mapped[str] = mapped_column(String(255), nullable=False)
    created_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), server_default=func.now(), nullable=False)