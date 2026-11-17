from uuid import UUID, uuid4
from flask import Blueprint, request, jsonify, render_template, g

from domain.model.board import Board
from domain.model.game import Game, Mark, GameMode, Error, GameState
from domain.service.game_service import GameService
from datasource.repository.game_repository import GameRepository
from web.mapper.game_mapper import WebGameMapper
from web.model.game_model import GameModel


def create_game_blueprint(service: GameService, repository: GameRepository) -> Blueprint:
    bp = Blueprint("game", __name__)

    @bp.route("/", methods=["GET"])
    def index():
        return render_template("index.html")

    @bp.route("/game/<uuid:game_uuid>", methods=["GET"])
    def game_page(game_uuid: UUID):
        game = repository.get(game_uuid)
        if game is None:
            return render_template("404.html", uuid=str(game_uuid)), 404
        state = service.compute_state(game)
        return render_template(
            "game.html",
            uuid=str(game.uuid),
            board=game.board.cells,
            state=state,
            player_mark=game.player_mark.value,
            opponent_mark=game.opponent_mark.value,
        )

    @bp.route("/game", methods=["POST"])
    def create_game():
        data = request.get_json(silent=True) or {}
        mode_str = data.get("mode", "computer")
        mark_str = data.get("mark")
        if mark_str is None:
            return jsonify({"error": "'mark' is required"}), 400
        try:
            mark = Mark(mark_str)
            mode = GameMode(mode_str)
        except ValueError as e:
            return jsonify({"error": f"Invalid mode or mark: {e}"}), 400
        game = service.create_game(g.user_uuid, mode, mark)
        repository.save(game)
        return jsonify(WebGameMapper.to_web(game).to_json()), 201

    @bp.route("/games", methods=["GET"])
    def get_available_games():
        games = service.get_available_games(g.user_uuid)
        return jsonify([WebGameMapper.to_web(game).to_json() for game in games]), 200

    @bp.route("/my-games", methods=["GET"])
    def get_my_games():
        games = service.get_my_games(g.user_uuid)
        return jsonify([
            WebGameMapper.to_web(game).to_json()
            for game in games
        ]), 200

    @bp.route("/api/game/<uuid:game_uuid>", methods=["GET"])
    def get_game(game_uuid: UUID):
        game = repository.get(game_uuid)
        if game is None:
            return jsonify({"error": "Game not found"}), 404
        if g.user_uuid not in (game.user_uuid, game.opponent_uuid):
            return jsonify({"error": "Access denied"}), 403
        game = service.apply_state(game)
        return jsonify(WebGameMapper.to_web(game).to_json()), 200

    @bp.route("/game/<uuid:game_uuid>/join", methods=["POST"])
    def join_game(game_uuid: UUID):
        game = service.join_game(game_uuid, g.user_uuid)
        if game == Error.e404:
            return jsonify({"error": "Game not found or not joinable"}), 404
        if game == Error.e400:
            return jsonify({"error": "Game connection failed"}), 400
        repository.save(game)
        return jsonify(WebGameMapper.to_web(game).to_json()), 200

    @bp.route("/game/<uuid:game_uuid>", methods=["POST"])
    def play(game_uuid: UUID):
        payload = request.get_json(silent=True) or {}
        board_cells = payload.get("board")
        if board_cells is None:
            return jsonify({"error": "'board' is required"}), 400

        try:
            board = Board(cells=board_cells)
        except (TypeError, ValueError):
            return jsonify({"error": "Invalid board format"}), 400

        result = service.play(game_uuid, g.user_uuid, board)
        if isinstance(result, Error):
            if result == Error.e404:
                return jsonify({"error": "Game not found"}), 404
            if result == Error.e403:
                return jsonify({"error": "Not your turn"}), 403
            return jsonify({"error": "Cannot play: invalid board or game state"}), 400

        repository.save(result)
        return jsonify(WebGameMapper.to_web(result).to_json()), 200

    @bp.route("/game/<uuid:game_uuid>/leave", methods=["POST"])
    def leave_game(game_uuid: UUID):
        game = repository.get(game_uuid)

        if game is None:
            return jsonify({"error": "Game not found"}), 404

        if g.user_uuid == game.user_uuid:
            if game.state in (GameState.WIN, GameState.DRAW):
                repository.delete(game_uuid)

            return jsonify({"success": True}), 200

        if g.user_uuid == game.opponent_uuid:
            repository.delete(game_uuid)
            return jsonify({"success": True}), 200

        return jsonify({"error": "You are not a player in this game"}), 403

    return bp