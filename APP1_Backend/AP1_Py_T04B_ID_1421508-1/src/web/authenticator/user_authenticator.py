from flask import Flask, request, jsonify, g

from domain.service.auth_service import AuthService

PUBLIC_ENDPOINTS = frozenset({
    "auth.signup",
    "auth.login",
    "game.index",
    "game.game_page",
    "static",
})

class UserAuthenticator:
    def __init__(self, app: Flask, auth_service: AuthService) -> None:
        self._app = app
        self._auth_service = auth_service
        app.before_request(self._check_auth)

    def _check_auth(self):
        if request.endpoint in PUBLIC_ENDPOINTS or request.endpoint is None:
            return None

        auth_header = request.headers.get('Authorization')
        if not auth_header:
            return jsonify({"error": "Authorization required"}), 401

        user_uuid = self._auth_service.authorize(auth_header)
        if user_uuid is None:
            return jsonify({"error": "Invalid credentials"}), 401

        g.user_uuid = user_uuid
        return None