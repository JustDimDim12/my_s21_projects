from domain.model.board import Board
from domain.model.game import Game
from web.model.game_model import GameModel


class WebGameMapper:
    @staticmethod
    def to_domain(model: GameModel) -> Game:
        return Game(uuid=model.uuid, board=Board([row[:] for row in model.board]))

    @staticmethod
    def to_web(game: Game) -> GameModel:
        return GameModel(
            uuid=game.uuid,
            board=[row[:] for row in game.board.cells],
            status=game.status,
        )