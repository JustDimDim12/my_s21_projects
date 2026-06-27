# domain/models/characters.py
from dataclasses import dataclass, field
from typing import Optional, List
from domain.models.item import Item, Backpack
from domain.models.map import Position


@dataclass
class ActiveElixir:
    """Tracks a temporary stat boost from drinking an elixir."""
    attribute: str  # "strength", "dexterity", or "max_health"
    modifier: int  # The amount added
    duration: int  # How many turns are left


@dataclass
class Character:
    """Represents the hero player character and their progressive attributes."""
    max_health: int
    current_health: int
    dexterity: int
    strength: int
    position: Position = Position(0, 0)
    current_weapon: Optional[Item] = None
    backpack: Backpack = field(default_factory=Backpack)
    experience_points: int = 0
    level: int = 1
    sleep_turns: int = 0
    # health_turns: int = 0
    # Task 2 Progressive updates: tracked temporary active modifications
    active_elixirs: List[ActiveElixir] = field(default_factory=list)
    treasure_collected: int = 0
    # Task 4 Granular Run-time Statistics Tracking Matrix
    enemies_defeated: int = 0
    food_consumed: int = 0
    elixirs_used: int = 0
    scrolls_read: int = 0
    attacks_made: int = 0
    hits_taken: int = 0
    tiles_traversed: int = 0

    @property
    def effective_strength(self) -> int:
        """Base strength + weapon strength modifier + active elixir bonuses."""
        bonus = sum(e.modifier for e in self.active_elixirs if e.attribute == "strength")
        if self.current_weapon:
            bonus += self.current_weapon.strength
        return max(0, self.strength + bonus)

    @property
    def effective_dexterity(self) -> int:
        """Base dexterity + active elixir bonuses."""
        bonus = sum(e.modifier for e in self.active_elixirs if e.attribute == "dexterity")
        return max(0, self.dexterity + bonus)

    @property
    def effective_max_health(self) -> int:
        """Base max health + active elixir bonuses."""
        bonus = sum(e.modifier for e in self.active_elixirs if e.attribute == "max_health")
        return max(1, self.max_health + bonus)

    def tick_elixirs(self):
        """Ticks down elixir durations by 1 turn and manages health degradation."""
        health_boost_lost = 0
        still_active = []

        for elixir in self.active_elixirs:
            elixir.duration -= 1
            if elixir.duration <= 0:
                if elixir.attribute == "max_health":
                    health_boost_lost += elixir.modifier
            else:
                still_active.append(elixir)

        self.active_elixirs = still_active

        if health_boost_lost > 0:
            # If an elixir wears off and reduces max health, adjust current health down
            self.current_health -= health_boost_lost
            # Task 2 Rule: If current health hits 0 or below from expiry, reset to 1
            if self.current_health <= 0:
                self.current_health = 1

    def unequip_weapon(self, drop_on_ground: bool = False) -> Optional[Item]:
        """
        Unequips the current weapon.
        If drop_on_ground is True, it returns the weapon to be placed on the map.
        If False (selecting '0' for empty hands), it places it back in the backpack.
        """
        if not self.current_weapon:
            return None

        old_weapon = self.current_weapon
        self.current_weapon = None

        if drop_on_ground:
            # Return the weapon so the caller can drop it on a neighbor tile
            return old_weapon
        else:
            # Choice '0': Put back into backpack if space allows
            added = self.backpack.add_item(old_weapon)
            if not added:
                # If backpack is full, fallback to dropping it on the ground
                return old_weapon
            return None


@dataclass
class Enemy:
    """Represents hostile dungeon monsters that spawn on various levels."""
    type: str  # e.g., "Zombie", "Snake Mage", "Vampire"
    health: int
    max_health: int
    dexterity: int
    strength: int
    position: Position
    hostility: int  # The tile distance/range at which it chases the player
    color_char: str  # e.g., 'z', 'v', 'g', 'o', 's'
    is_invisible: bool = False
    ogre_resting: bool = False  # Special turn tracker for the Ogre
    had_been_attacked: bool = False  # Needed for Vampire's first-hit dodge rule
    current_room_id: Optional[int] = None  # Tracks which sector room borders own this monster
    # for mimic
    is_mimic: bool = False
    is_awake: bool = False
    mimic_symbol: str = ''
