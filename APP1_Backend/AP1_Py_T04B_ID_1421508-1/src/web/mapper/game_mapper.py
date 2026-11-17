from domain.model.board import Board
from domain.model.game import Game, Mark, GameState
from web.model.game_model import GameModel


class WebGameMapper:
    @staticmethod
    def to_domain(model: GameModel) -> Game:
        return Game(
            uuid=model.uuid,
            board=Board([row[:] for row in model.board]),
            state=GameState(model.state),
            user_uuid=model.user_uuid,
            opponent_uuid=model.opponent_uuid,
            current_player_uuid=model.current_player_uuid,
            winner_uuid=model.winner_uuid,
            player_mark=Mark(model.player_mark),
            opponent_mark=Mark(model.opponent_mark),
        )

    @staticmethod
    def to_web(game: Game) -> GameModel:
        return GameModel(
            uuid=game.uuid,
            board=[row[:] for row in game.board.cells],
            state=game.state.value,
            user_uuid=game.user_uuid,
            opponent_uuid=game.opponent_uuid,
            current_player_uuid=game.current_player_uuid,
            winner_uuid=game.winner_uuid,
            player_mark=game.player_mark.value,
            opponent_mark=game.opponent_mark.value,
        )