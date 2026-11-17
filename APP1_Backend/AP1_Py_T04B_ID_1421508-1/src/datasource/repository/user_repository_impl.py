from uuid import UUID

from sqlalchemy import select

from domain.model.user import User
from datasource.database import get_session
from datasource.mapper.user_mapper import UserMapper
from datasource.model.user_entity import UserEntity
from datasource.repository.user_repository import UserRepository


class UserRepositoryImpl(UserRepository):

    def save(self, user: User) -> None:
        entity = UserMapper.to_entity(user)

        with get_session() as session:
            session.merge(entity)

    def get_by_uuid(self, user_uuid: UUID) -> User | None:
        with get_session() as session:
            stmt = select(UserEntity).where(UserEntity.uuid == str(user_uuid))
            entity = session.execute(stmt).scalar_one_or_none()

            if entity is None:
                return None

            return UserMapper.to_domain(entity)

    def get_by_login(self, login: str) -> User | None:
        with get_session() as session:
            stmt = select(UserEntity).where(UserEntity.login == login)
            entity = session.execute(stmt).scalar_one_or_none()

            if entity is None:
                return None

            return UserMapper.to_domain(entity)

    def exists_by_login(self, login: str) -> bool:
        with get_session() as session:
            stmt = (select(UserEntity.uuid).where(UserEntity.login == login).limit(1))
            return session.execute(stmt).scalar_one_or_none() is not None