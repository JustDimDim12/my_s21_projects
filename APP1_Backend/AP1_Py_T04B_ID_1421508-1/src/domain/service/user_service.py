from uuid import UUID
from domain.model.user import User


class UserService:

    def register(self, login: str, password: str) -> User | None:
        raise NotImplementedError

    def authenticate(self, login: str, password: str) -> UUID | None:
        raise NotImplementedError

    def get_by_uuid(self, user_uuid: UUID) -> User | None:
        raise NotImplementedError