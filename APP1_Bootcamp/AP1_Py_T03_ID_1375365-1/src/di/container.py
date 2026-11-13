from domain.service.game_service import GameService
from domain.service.game_service_impl import GameServiceImpl
from datasource.repository.game_repository import GameRepository
from datasource.repository.game_repository_impl import GameRepositoryImpl
from datasource.storage.game_storage import GameStorage


class Container:
    def __init__(self) -> None:
        self._storage = GameStorage()
        self._repository = GameRepositoryImpl(self._storage)
        self._service = GameServiceImpl()

    @property
    def storage(self) -> GameStorage:        return self._storage

    @property
    def repository(self) -> GameRepository:  return self._repository

    @property
    def service(self) -> GameService:        return self._service