import math
from uuid import UUID, uuid4
from domain.model.board import Board
from domain.model.game import Game, GameState, Mark, GameMode, Error, PLAYER, COMPUTER, EMPTY
from domain.service.game_service import GameService
from datasource.repository.game_repository import GameRepository

WIN_LINES = [
    (0, 1, 2), (3, 4, 5), (6, 7, 8),
    (0, 3, 6), (1, 4, 7), (2, 5, 8),
    (0, 4, 8), (2, 4, 6),
]


class GameServiceImpl(GameService):

    def __init__(self, repository: GameRepository):
        self._repository = repository

    def create_game(self, user_uuid: UUID, mode: GameMode, mark: Mark) -> Game:
        if mode == GameMode.PLAYER:
            return Game(
                uuid=uuid4(),
                board=Board([[0] * 3 for _ in range(3)]),
                state=GameState.WAIT,
                user_uuid=user_uuid,
                opponent_uuid=None,
                player_mark=mark,
                opponent_mark=mark.another_mark(),
                current_player_uuid=None,
                winner_uuid=None,
            )

        if mark == Mark.X:
            return Game(
                uuid=uuid4(),
                board=Board([[0] * 3 for _ in range(3)]),
                state=GameState.TURN,
                user_uuid=user_uuid,
                opponent_uuid=None,
                player_mark=mark,
                opponent_mark=mark.another_mark(),
                current_player_uuid=user_uuid,
                winner_uuid=None,
            )

        game = Game(
            uuid=uuid4(),
            board=Board([[0] * 3 for _ in range(3)]),
            state=GameState.TURN,
            user_uuid=user_uuid,
            opponent_uuid=None,
            player_mark=mark,
            opponent_mark=mark.another_mark(),
            current_player_uuid=None,
            winner_uuid=None,
        )
        game = self.get_next_move(game)
        game = self.apply_state(game)
        return game

    def get_available_games(self, user_uuid: UUID) -> list[Game]:
        return self._repository.find_available(user_uuid)

    def get_my_games(self, user_uuid: UUID) -> list[Game]:
        return self._repository.find_by_creator(user_uuid)

    def join_game(self, game_uuid: UUID, user_uuid: UUID) -> Game | Error:
        game = self._repository.get(game_uuid)
        if game is None:
            return Error.e404

        if game.state != GameState.WAIT or game.opponent_uuid is not None or game.user_uuid == user_uuid:
            return Error.e400

        if game.player_mark == Mark.X:
            current_player_uuid = game.user_uuid
        else:
            current_player_uuid = user_uuid

        return Game(
            uuid=game_uuid,
            board=game.board,
            state=GameState.TURN,
            user_uuid=game.user_uuid,
            opponent_uuid=user_uuid,
            player_mark=game.player_mark,
            opponent_mark=game.opponent_mark,
            current_player_uuid=current_player_uuid,
            winner_uuid=None,
        )

    def play(self, game_uuid: UUID, user_uuid: UUID, board: Board) -> Game | Error:
        game = self._repository.get(game_uuid)
        if game is None:
            return Error.e404
        if game.state != GameState.TURN:
            return Error.e400
        if game.current_player_uuid != user_uuid:
            return Error.e403

        if not self.validate_board(board, game.player_mark):
            return Error.e400

        game.board = board
        game = self.apply_state(game)

        if game.state == GameState.TURN:
            if game.opponent_uuid is None:
                game = self.get_next_move(game)
                game = self.apply_state(game)
            else:
                if user_uuid == game.user_uuid:
                    game.current_player_uuid = game.opponent_uuid
                else:
                    game.current_player_uuid = game.user_uuid

        return game


    def get_next_move(self, game: Game) -> Game:
        flat = [c for row in game.board.cells for c in row]
        best_score, best_move = -math.inf, None
        for i in range(9):
            if flat[i] == EMPTY:
                flat[i] = COMPUTER
                score = self._minimax(flat, 0, False)
                flat[i] = EMPTY
                if score > best_score:
                    best_score, best_move = score, i
        if best_move is not None:
            flat[best_move] = COMPUTER
        new_board = Board([flat[i:i + 3] for i in range(0, 9, 3)])
        game.board = new_board
        return game

    def _minimax(self, flat, depth, is_max):
        w = self._winner(flat)
        if w == COMPUTER: return 10 - depth
        if w == PLAYER:   return depth - 10
        if EMPTY not in flat: return 0
        if is_max:
            best = -math.inf
            for i in range(9):
                if flat[i] == EMPTY:
                    flat[i] = COMPUTER
                    best = max(best, self._minimax(flat, depth + 1, False))
                    flat[i] = EMPTY
            return best
        best = math.inf
        for i in range(9):
            if flat[i] == EMPTY:
                flat[i] = PLAYER
                best = min(best, self._minimax(flat, depth + 1, True))
                flat[i] = EMPTY
        return best

    def _winner(self, flat):
        for a, b, c in WIN_LINES:
            if flat[a] != EMPTY and flat[a] == flat[b] == flat[c]:
                return flat[a]
        return None

    def validate_board(self, board: Board, player_mark: Mark) -> bool:
        flat = [c for row in board.cells for c in row]
        if len(flat) != 9:
            return False
        if any(c not in (EMPTY, PLAYER, COMPUTER) for c in flat):
            return False
        players = flat.count(PLAYER)
        computers = flat.count(COMPUTER)

        if player_mark == Mark.X:
            return computers <= players <= computers + 1
        else:
            return players <= computers <= players + 1

    def validate_marks(self, player_mark: Mark, opponent_mark: Mark) -> bool:
        if not isinstance(player_mark, Mark) or not isinstance(opponent_mark, Mark):
            return False
        return player_mark != opponent_mark

    def is_game_over(self, game: Game) -> bool:
        return game.state in (GameState.DRAW, GameState.WIN)

    def compute_state(self, game: Game) -> tuple[GameState, UUID | None]:
        flat = [c for row in game.board.cells for c in row]
        w = self._winner(flat)

        if w == PLAYER:
            return (GameState.WIN, game.user_uuid)
        if w == COMPUTER:
            return (GameState.WIN, game.opponent_uuid)

        if EMPTY not in flat:
            return (GameState.DRAW, None)

        if game.opponent_uuid is None:
            current = game.user_uuid
        else:
            players = flat.count(PLAYER)
            computers = flat.count(COMPUTER)

            if players == computers:
                current = (
                    game.user_uuid
                    if game.player_mark == Mark.X
                    else game.opponent_uuid
                )
            else:
                current = (
                    game.opponent_uuid
                    if game.player_mark == Mark.X
                    else game.user_uuid
                )

        return (GameState.TURN, current)

    def apply_state(self, game: Game) -> Game:
        if game.state == GameState.WAIT:
            return game

        state, uuid = self.compute_state(game)
        game.state = state
        if state == GameState.WIN:
            game.winner_uuid = uuid
            game.current_player_uuid = None
        elif state == GameState.TURN:
            game.current_player_uuid = uuid
            game.winner_uuid = None
        else:
            game.winner_uuid = None
            game.current_player_uuid = None
        return game

    def leave_game(self, game_uuid: UUID, user_uuid: UUID) -> bool:
        game = self._repository.get(game_uuid)

        if game is None:
            return False

        is_opponent = game.opponent_uuid == user_uuid
        is_creator_after_game = (
                game.user_uuid == user_uuid
                and game.state in (GameState.WIN, GameState.DRAW)
        )

        if not is_opponent and not is_creator_after_game:
            return False

        return self._repository.delete(game_uuid)