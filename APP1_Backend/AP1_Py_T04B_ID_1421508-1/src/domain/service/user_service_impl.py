from uuid import uuid4, UUID
from werkzeug.security import generate_password_hash, check_password_hash

from domain.model.user import User
from domain.service.user_service import UserService
from datasource.repository.user_repository import UserRepository


class UserServiceImpl(UserService):

    def __init__(self, repository: UserRepository) -> None:
        self._repository = repository

    def register(self, login: str, password: str) -> User | None:
        if not login or not password:
            return None
        if len(login) < 3 or len(password) < 6:
            return None

        if self._repository.exists_by_login(login):
            return None

        password_hash = generate_password_hash(password)

        new_user = User(
            uuid=uuid4(),
            login=login,
            password_hash=password_hash,
        )

        self._repository.save(new_user)

        return new_user

    def authenticate(self, login: str, password: str) -> UUID | None:
        if not login or not password:
            return None

        user = self._repository.get_by_login(login)
        if user is None:
            return None
        if not check_password_hash(user.password_hash, password):
            return None

        return user.uuid

    def get_by_uuid(self, user_uuid: UUID) -> User | None:
        return self._repository.get_by_uuid(user_uuid)

