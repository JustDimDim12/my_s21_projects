from uuid import UUID
from domain.model.game import Game


class GameRepository:

    def save(self, game: Game) -> None:
        raise NotImplementedError

    def get(self, game_uuid: UUID) -> Game | None:
        raise NotImplementedError

    def find_available(self, exclude_user_uuid: UUID) -> list[Game]:
        raise NotImplementedError

    def find_by_creator(self, user_uuid: UUID) -> list[Game]:
        raise NotImplementedError

    def delete(self, game_uuid: UUID) -> bool:
        raise NotImplementedError