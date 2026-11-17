from uuid import UUID

from domain.model.user import User
from datasource.model.user_entity import UserEntity


class UserMapper:

    @staticmethod
    def to_entity(user: User) -> UserEntity:
        return UserEntity(
            uuid=str(user.uuid),
            login=user.login,
            password_hash=user.password_hash
        )

    @staticmethod
    def to_domain(entity: UserEntity) -> User:
        return User(
            uuid=UUID(entity.uuid),
            login=entity.login,
            password_hash=entity.password_hash
        )