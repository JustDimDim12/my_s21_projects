from uuid import UUID
from domain.model.game import Game, GameState, Mark, GameMode
from domain.model.board import Board
from domain.model.game import Error


class GameService:

    def create_game(self, user_uuid: UUID, mode: GameMode, mark: Mark) -> Game:
        raise NotImplementedError

    def get_available_games(self, user_uuid: UUID) -> list[Game]:
        raise NotImplementedError

    def get_my_games(self, user_uuid: UUID) -> list[Game]:
        raise NotImplementedError

    def join_game(self, game_uuid: UUID, user_uuid: UUID) -> Game | Error:
        raise NotImplementedError

    def play(self, game_uuid: UUID, user_uuid: UUID, board: Board) -> Game | Error:
        raise NotImplementedError

    def get_next_move(self, game: Game) -> Game:
        raise NotImplementedError

    def validate_board(self, board: Board, player_mark: Mark) -> bool:
        raise NotImplementedError

    def validate_marks(self, player_mark: Mark, opponent_mark: Mark) -> bool:
        raise NotImplementedError

    def is_game_over(self, game: Game) -> bool:
        raise NotImplementedError

    def compute_state(self, game: Game) -> tuple[GameState, UUID | None]:
        raise NotImplementedError

    def apply_state(self, game: Game) -> Game:
        raise NotImplementedError

    def leave_game(self, game_uuid: UUID, user_uuid: UUID) -> bool:
        raise NotImplementedError