from uuid import UUID

from domain.model.game import Game
from datasource.mapper.game_mapper import GameMapper
from datasource.repository.game_repository import GameRepository
from datasource.storage.game_storage import GameStorage


class GameRepositoryImpl(GameRepository):
    def __init__(self, storage: GameStorage) -> None:
        self._storage = storage

    def save(self, game: Game) -> None:
        self._storage.save(GameMapper.to_entity(game))

    def get(self, game_uuid: UUID) -> Game | None:
        entity = self._storage.get(game_uuid)
        return GameMapper.to_domain(entity) if entity else None