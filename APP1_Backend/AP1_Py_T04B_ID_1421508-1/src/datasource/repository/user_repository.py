from uuid import UUID
from domain.model.user import User


class UserRepository:

    def save(self, user: User) -> None:
        raise NotImplementedError

    def get_by_uuid(self, user_uuid: UUID) -> User | None:
        raise NotImplementedError

    def get_by_login(self, login: str) -> User | None:
        raise NotImplementedError

    def exists_by_login(self, login: str) -> bool:
        raise NotImplementedError