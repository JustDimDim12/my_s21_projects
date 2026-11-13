# domain/models/visibility.py
from dataclasses import dataclass, field
from typing import Set
from domain.models.map import Position


@dataclass
class VisibilityMap:
    """A clean, isolated container tracking player exploration telemetry."""
    discovered_tiles: Set[Position] = field(default_factory=set)
