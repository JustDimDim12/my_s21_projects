from domain.model.board import Board
from domain.model.game import Game
from datasource.model.board_entity import BoardEntity
from datasource.model.game_entity import GameEntity


class GameMapper:
    @staticmethod
    def to_entity(game: Game) -> GameEntity:
        return GameEntity(
            uuid=game.uuid,
            board=BoardEntity([row[:] for row in game.board.cells]),
            status=game.status,
        )

    @staticmethod
    def to_domain(entity: GameEntity) -> Game:
        return Game(
            uuid=entity.uuid,
            board=Board([row[:] for row in entity.board.cells]),
            status=entity.status,
        )