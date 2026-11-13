from uuid import UUID, uuid4
from flask import Blueprint, request, jsonify, render_template, abort

from domain.model.board import Board
from domain.model.game import Game
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
        status = service.compute_status(game)
        return render_template(
            "game.html",
            uuid=str(game.uuid),
            board=game.board.cells,
            status=status,
        )

    @bp.route("/game", methods=["POST"])
    def create_game():
        game = Game(uuid=uuid4(), board=Board([[0, 0, 0], [0, 0, 0], [0, 0, 0]]))
        repository.save(game)
        return jsonify(WebGameMapper.to_web(game).to_json()), 201

    @bp.route("/api/game/<uuid:game_uuid>", methods=["GET"])
    def get_game(game_uuid: UUID):
        game = repository.get(game_uuid)
        if game is None:
            return jsonify({"error": "Game not found"}), 404
        game.status = service.compute_status(game)
        return jsonify(WebGameMapper.to_web(game).to_json()), 200

    @bp.route("/game/<uuid:game_uuid>", methods=["POST"])
    def play(game_uuid: UUID):
        saved = repository.get(game_uuid)
        if saved is None:
            return jsonify({"error": "Game not found"}), 404

        payload = request.get_json(silent=True) or {}
        try:
            board_cells = payload["board"]
            incoming = GameModel(uuid=game_uuid, board=board_cells)
        except (KeyError, TypeError):
            return jsonify({"error": "Invalid payload: 'board' (3x3) required"}), 400

        domain_game = WebGameMapper.to_domain(incoming)

        if not service.validate_board(domain_game):
            return jsonify({"error": "Invalid board: previous moves were changed"}), 400
        repository.save(domain_game)

        status = service.compute_status(domain_game)
        if status != "playing":
            domain_game.status = status
            repository.save(domain_game)
            return jsonify(WebGameMapper.to_web(domain_game).to_json()), 200

        updated = service.get_next_move(domain_game)
        updated.status = service.compute_status(updated)
        repository.save(updated)
        return jsonify(WebGameMapper.to_web(updated).to_json()), 200

    return bp