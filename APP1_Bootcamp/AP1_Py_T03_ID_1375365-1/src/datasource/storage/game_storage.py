from typing import Dict, Optional
from uuid import UUID
from threading import RLock

from datasource.model.game_entity import GameEntity


class GameStorage:

    def __init__(self) -> None:
        self._games: Dict[UUID, GameEntity] = {}
        self._lock = RLock()

    def save(self, game: GameEntity) -> None:
        with self._lock:
            self._games[game.uuid] = game

    def get(self, game_uuid: UUID) -> Optional[GameEntity]:
        with self._lock:
            return self._games.get(game_uuid)

    def exists(self, game_uuid: UUID) -> bool:
        with self._lock:
            return game_uuid in self._games