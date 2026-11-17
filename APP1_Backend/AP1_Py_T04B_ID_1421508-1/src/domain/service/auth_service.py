from uuid import UUID
from web.model.signup_request import SignUpRequest


class AuthService:

    def register(self, request: SignUpRequest) -> bool:
        raise NotImplementedError

    def authorize(self, auth_header: str) -> UUID | None:
        raise NotImplementedError
