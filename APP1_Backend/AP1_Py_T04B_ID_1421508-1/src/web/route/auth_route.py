from flask import Flask
from domain.service.auth_service import AuthService
from domain.service.user_service import UserService
from web.module.auth_module import create_auth_blueprint

def register_auth_routes(app: Flask, auth_service: AuthService, user_service: UserService) -> None:
    app.register_blueprint(create_auth_blueprint(auth_service, user_service))