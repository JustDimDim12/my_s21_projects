from flask import Flask

from di.container import Container
from datasource.database import init_db
from web.authenticator.user_authenticator import UserAuthenticator
from web.route.game_route import register_routes
from web.route.auth_route import register_auth_routes


def create_app() -> Flask:
    app = Flask(__name__,
                template_folder="web/templates",
                static_folder="web/static")

    init_db()
    container = Container()
    register_routes(app, container.game_service, container.game_repository)
    register_auth_routes(app, container.auth_service, container.user_service)
    UserAuthenticator(app, container.auth_service)
    return app


if __name__ == "__main__":
    create_app().run()