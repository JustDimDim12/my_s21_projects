from uuid import UUID
from domain.model.game import Game


class GameService:

    def get_next_move(self, game: Game) -> Game:
        raise NotImplementedError

    def validate_board(self, game: Game) -> bool:
        raise NotImplementedError

    def is_game_over(self, game: Game) -> bool:
        raise NotImplementedError

    def compute_status(self, game: Game) -> str:
        raise NotImplementedError