from dataclasses import dataclass
from uuid import UUID


@dataclass
class UserModel:
    uuid: UUID
    login: str

    def to_json(self) -> dict:
        return {"uuid": str(self.uuid), "login": self.login}