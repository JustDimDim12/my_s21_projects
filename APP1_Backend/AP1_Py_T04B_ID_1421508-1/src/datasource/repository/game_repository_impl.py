from uuid import UUID

from sqlalchemy import select, delete

from domain.model.game import Game, GameState
from datasource.database import get_session
from datasource.mapper.game_mapper import GameMapper
from datasource.model.game_entity import GameEntity
from datasource.repository.game_repository import GameRepository


class GameRepositoryImpl(GameRepository):
    def save(self, game: Game) -> None:
        entity = GameMapper.to_entity(game)

        with get_session() as session:
            session.merge(entity)

    def get(self, game_uuid: UUID) -> Game | None:
        with get_session() as session:
            stmt = select(GameEntity).where(GameEntity.uuid == str(game_uuid))
            entity = session.execute(stmt).scalar_one_or_none()

            if entity is None:
                return None

            return GameMapper.to_domain(entity)

    def find_available(self, exclude_user_uuid: UUID) -> list[Game]:
        with (get_session() as session):
            stmt = (select(GameEntity)
                .where(
                    GameEntity.state == GameState.WAIT.value,
                    GameEntity.opponent_uuid.is_(None),
                    GameEntity.user_uuid != str(exclude_user_uuid)
                )
                .order_by(GameEntity.created_at.desc())
            )
            entities = session.execute(stmt).scalars().all()

            return [GameMapper.to_domain(e) for e in entities]

    def find_by_creator(self, user_uuid: UUID) -> list[Game]:
        with get_session() as session:
            stmt = (
                select(GameEntity)
                .where(GameEntity.user_uuid == str(user_uuid))
                .order_by(GameEntity.created_at.desc())
            )

            entities = session.execute(stmt).scalars().all()

            return [GameMapper.to_domain(e) for e in entities]

    def delete(self, game_uuid: UUID) -> bool:
        with get_session() as session:
            entity = session.get(GameEntity, str(game_uuid))

            if entity is None:
                return False

            session.delete(entity)
            return True