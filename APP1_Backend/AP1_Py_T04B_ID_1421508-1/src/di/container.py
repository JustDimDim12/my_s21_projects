from domain.service.game_service import GameService
from domain.service.game_service_impl import GameServiceImpl
from domain.service.user_service import UserService
from domain.service.user_service_impl import UserServiceImpl
from domain.service.auth_service import AuthService
from domain.service.auth_service_impl import AuthServiceImpl
from datasource.repository.game_repository import GameRepository
from datasource.repository.user_repository import UserRepository
from datasource.repository.game_repository_impl import GameRepositoryImpl
from datasource.repository.user_repository_impl import UserRepositoryImpl


class Container:
    def __init__(self) -> None:
        self._game_repository = GameRepositoryImpl()
        self._user_repository = UserRepositoryImpl()
        self._game_service = GameServiceImpl(self._game_repository)
        self._user_service = UserServiceImpl(self._user_repository)
        self._auth_service = AuthServiceImpl(self._user_service)

    @property
    def game_repository(self) -> GameRepository:
        return self._game_repository

    @property
    def game_service(self) -> GameService:
        return self._game_service

    @property
    def user_repository(self) -> UserRepository:
        return self._user_repository

    @property
    def user_service(self) -> UserService:
        return self._user_service

    @property
    def auth_service(self) -> AuthService:
        return self._auth_service