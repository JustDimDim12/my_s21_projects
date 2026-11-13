import math
from domain.model.board import Board
from domain.model.game import Game, PLAYER, COMPUTER, EMPTY
from domain.service.game_service import GameService

WIN_LINES = [
    (0, 1, 2), (3, 4, 5), (6, 7, 8),
    (0, 3, 6), (1, 4, 7), (2, 5, 8),
    (0, 4, 8), (2, 4, 6),
]


class GameServiceImpl(GameService):

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
        return Game(uuid=game.uuid, board=new_board)

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

    def validate_board(self, game: Game) -> bool:
        flat = [c for row in game.board.cells for c in row]
        if len(flat) != 9: return False
        if any(c not in (EMPTY, PLAYER, COMPUTER) for c in flat): return False
        players = flat.count(PLAYER)
        computers = flat.count(COMPUTER)
        return computers <= players <= computers + 1

    def is_game_over(self, game: Game) -> bool:
        flat = [c for row in game.board.cells for c in row]
        return self._winner(flat) is not None or EMPTY not in flat

    def compute_status(self, game: Game) -> str:
        flat = [c for row in game.board.cells for c in row]
        w = self._winner(flat)
        if w == PLAYER:   return "user_wins"
        if w == COMPUTER: return "computer_wins"
        if EMPTY not in flat: return "draw"
        return "playing"