from uuid import UUID

from domain.model.board import Board
from domain.model.game import Game, Mark, GameState
from datasource.model.board_entity import BoardEntity
from datasource.model.game_entity import GameEntity


class GameMapper:
    @staticmethod
    def to_entity(game: Game) -> GameEntity:
        return GameEntity(
            uuid=str(game.uuid),
            state=game.state.value,
            board=BoardEntity.from_matrix(
                game_uuid=str(game.uuid),
                matrix=game.board.cells,
            ),
            user_uuid=str(game.user_uuid),
            opponent_uuid=str(game.opponent_uuid) if game.opponent_uuid else None,
            current_player_uuid=str(game.current_player_uuid) if game.current_player_uuid else None,
            winner_uuid=str(game.winner_uuid) if game.winner_uuid else None,
            player_mark=game.player_mark.value,
            opponent_mark=game.opponent_mark.value,
        )

    @staticmethod
    def to_domain(entity: GameEntity) -> Game:
        if entity.board is not None:
            matrix = entity.board.to_matrix()
        else:
            matrix = [[0,0,0], [0,0,0], [0,0,0]]

        return Game(
            uuid=UUID(entity.uuid),
            board=Board(cells=matrix),
            state=GameState(entity.state),
            user_uuid=UUID(entity.user_uuid),
            opponent_uuid=UUID(entity.opponent_uuid) if entity.opponent_uuid else None,
            current_player_uuid=UUID(entity.current_player_uuid) if entity.current_player_uuid else None,
            winner_uuid=UUID(entity.winner_uuid) if entity.winner_uuid else None,
            player_mark=Mark(entity.player_mark),
            opponent_mark=Mark(entity.opponent_mark),
        )