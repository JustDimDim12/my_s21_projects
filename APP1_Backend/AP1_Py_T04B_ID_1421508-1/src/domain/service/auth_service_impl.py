import base64
import binascii
from uuid import UUID

from domain.service.auth_service import AuthService
from domain.service.user_service import UserService
from web.model.signup_request import SignUpRequest


class AuthServiceImpl(AuthService):

    def __init__(self, service: UserService) -> None:
        self._user_service = service

    def register(self, request: SignUpRequest) -> bool:
        user = self._user_service.register(request.login, request.password)
        return user is not None

    def authorize(self, auth_header: str) -> UUID | None:
        if not auth_header:
            return None

        try:
            decoded_bytes = base64.b64decode(auth_header, validate=True)
            decode = decoded_bytes.decode("utf-8")
        except (binascii.Error, UnicodeDecodeError, ValueError):
            return None

        login, sep, password = decode.partition(":")
        if not sep:
            return None

        if not login or not password:
            return None

        return self._user_service.authenticate(login, password)