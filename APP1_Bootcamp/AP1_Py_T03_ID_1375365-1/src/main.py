from flask import Flask
from di.container import Container
from web.route.game_route import register_routes


def create_app() -> Flask:
    app = Flask(__name__,
                template_folder="web/templates",
                static_folder="web/static")
    container = Container()
    register_routes(app, container.service, container.repository)
    return app


if __name__ == "__main__":
    create_app().run(debug=True)