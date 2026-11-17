import os
from contextlib import contextmanager

from datasource.model import game_entity
from datasource.model import user_entity
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker, Session

from datasource.model.base import Base

DATABASE_URL = os.getenv(
    'DATABASE_URL',
    "postgresql+psycopg2://postgres:postgres@localhost:5433/tictactoe"
)

engine = create_engine(
    DATABASE_URL,
    pool_pre_ping=True,
    echo=False,
)

SessionLocal = sessionmaker(bind=engine, autoflush=False, expire_on_commit=False)

def init_db() -> None:
    Base.metadata.create_all(bind=engine)

@contextmanager
def get_session() -> Session:
    session = SessionLocal()
    try:
        yield session
        session.commit()
    except Exception:
        session.rollback()
        raise
    finally:
        session.close()