from domain.model.user import User
from web.model.user_model import UserModel


class WebUserMapper:

    @staticmethod
    def to_web(user: User) -> UserModel:
        return UserModel(
            uuid=user.uuid,
            login=user.login,
        )