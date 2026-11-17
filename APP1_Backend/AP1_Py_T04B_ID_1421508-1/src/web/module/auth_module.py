from flask import Blueprint, request, jsonify, g
from uuid import UUID

from domain.service.auth_service import AuthService
from web.model.signup_request import SignUpRequest
from domain.service.user_service import UserService
from web.mapper.user_mapper import WebUserMapper

def create_auth_blueprint(auth_service: AuthService, user_service: UserService) -> Blueprint:
    bp = Blueprint("auth", __name__)

    @bp.route("/signup", methods=["POST"])
    def signup():
        data = request.get_json(silent=True)
        if data is None:
            return jsonify({"error": "Request body must be JSON"}), 400

        login = data.get("login")
        password = data.get("password")
        if not isinstance(login, str) or not login:
            return jsonify({"error": "'login' is required and must be a non-empty string"}), 400
        if not isinstance(password, str) or not password:
            return jsonify({"error": "'password' is required and must be a non-empty string"}), 400

        req = SignUpRequest(login=login, password=password)
        success = auth_service.register(req)

        if not success:
            return jsonify({"error": "Login already taken or invalid data"}), 400

        return jsonify({"login": login}), 201

    @bp.route("/login", methods=["POST"])
    def login():
        auth_header = request.headers.get("Authorization")

        if not auth_header:
            return jsonify({"error": "Authorization header is missing"}), 401

        encoded = auth_header
        uuid = auth_service.authorize(encoded)

        if uuid is None:
            return jsonify({"error": "Invalid credentials"}), 401
        return jsonify({"uuid": str(uuid)}), 200

    @bp.route("/api/user/<uuid:user_uuid>", methods=["GET"])
    def get_user(user_uuid: UUID):
        user = user_service.get_by_uuid(user_uuid)
        if user is None:
            return jsonify({"error": "User not found"}), 404
        if user_uuid != g.user_uuid:
            return jsonify({"error": "Access denied"}), 403
        return jsonify(WebUserMapper.to_web(user).to_json()), 200

    return bp