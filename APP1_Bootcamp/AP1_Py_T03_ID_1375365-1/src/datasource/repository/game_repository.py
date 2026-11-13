from uuid import UUID
from domain.model.game import Game


class GameRepository:

    def save(self, game: Game) -> None:
        raise NotImplementedError

    def get(self, game_uuid: UUID) -> Game | None:
        raise NotImplementedError