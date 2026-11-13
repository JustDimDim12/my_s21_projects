from flask import Flask
from domain.service.game_service import GameService
from datasource.repository.game_repository import GameRepository
from web.module.game_module import create_game_blueprint


def register_routes(app: Flask, service: GameService, repository: GameRepository) -> None:
    app.register_blueprint(create_game_blueprint(service, repository))