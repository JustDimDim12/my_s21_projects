# data/storage.py
import json
import os
from typing import List, Dict, Any


class ScoreStorage:
    """Handles saving and loading the high score table to persistent storage."""

    FILE_PATH = "high_scores.json"
    SAVE_FILE_PATH = "save_game.json"  # Secondary pathway for live run snapshots

    @classmethod
    def save_scores(cls, scores: List[Dict[str, int]]) -> None:
        """Serializes the leaderboard list into a local JSON text file."""
        try:
            with open(cls.FILE_PATH, "w", encoding="utf-8") as f:
                # json.dump cleanly converts Python lists/dicts to a file format
                json.dump(scores, f, indent=4)
        except IOError:
            pass  # Suppress storage write failures gracefully

    @classmethod
    def load_scores(cls) -> List[Dict[str, int]]:
        """Reads and deserializes the leaderboard file from disk."""
        if not os.path.exists(cls.FILE_PATH):
            return []  # Return a clean empty list if the game has never been run before

        try:
            with open(cls.FILE_PATH, "r", encoding="utf-8") as f:
                scores = json.load(f)
                # Task 2 Safety Rule: Always double check everything remains sorted by gold descending
                scores.sort(key=lambda run: run.get("treasure", 0), reverse=True)
                return scores
        except (IOError, json.JSONDecodeError):
            return []  # Fallback to an empty array if the file becomes corrupted

    @classmethod
    def load_session_state(cls) -> Dict[str, Any] | None:
        """Reads and parses the active game session file if it exists."""
        if not os.path.exists(cls.SAVE_FILE_PATH):
            return None
        try:
            with open(cls.SAVE_FILE_PATH, "r", encoding="utf-8") as f:
                return json.load(f)
        except (IOError, json.JSONDecodeError):
            return None

    @classmethod
    def save_session_state(cls, state_data: Dict[str, Any]) -> None:
        """
        Serializes and writes the complete active game session snapshot to disk.
        Fulfills Task 5 save telemetry requirements.
        """
        try:
            with open(cls.SAVE_FILE_PATH, "w", encoding="utf-8") as f:
                json.dump(state_data, f, indent=4)
        except IOError:
            pass

    @classmethod
    def clear_save_file(cls) -> None:
        """Deletes the active session file upon run completion or player death."""
        if os.path.exists(cls.SAVE_FILE_PATH):
            try:
                os.remove(cls.SAVE_FILE_PATH)
            except OSError:
                pass
