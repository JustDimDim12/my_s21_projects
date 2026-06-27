# domain/models/item.py
from dataclasses import dataclass, field  # class designed to store data
from typing import List  # For Type Hinting.


@dataclass
class Item:
    """Represents any collectable item, potion, scroll, weapon, or treasure."""
    type: str  # e.g., "scroll", "weapon", "food", "treasure"
    subtype: str  # e.g., "healing elixir", "iron sword"
    health: int = 0  # HP restoration value (food)
    max_health: int = 0  # Max HP boost value (elixirs)
    dexterity: int = 0  # Dexterity stat alteration
    strength: int = 0  # Strength adjustment (or base damage for weapons)
    value: int = 0  # Gold piece / score value (treasure)


@dataclass
class Backpack:
    """Manages the items carried by a character up to a fixed capacity."""
    items: List[Item] = field(default_factory=list)
    capacity: int = 26  # Emulates 'a' through 'z' inventory slots

    def get_count_by_type(self, item_type: str) -> int:
        """Counts how many items of a specific type are currently in the backpack."""
        if item_type == "treasure":
            # Treasure stacks in a single slot, checking its existence counts as 1 if present
            return 1 if any(i.type == "treasure" for i in self.items) else 0

        # Count individual items for non-treasure types
        return sum(1 for i in self.items if i.type == item_type)

    def add_item(self, item: Item) -> bool:
        """Adds an item, if space is available. Returns True if successful."""
        # Treasure stacks in a single slot
        if item.type == "treasure":
            for existing_item in self.items:
                if existing_item.type == "treasure":
                    existing_item.value += item.value
                    return True
            # If no treasure exists yet, fall through to check slot capacity

        # Limit of up to 9 items per distinct type
        if item.type != "treasure":
            if self.get_count_by_type(item.type) >= 9:
                return False  # Denied: Too many items of this type

        # General physical inventory slot limit check
        if len(self.items) < self.capacity:
            self.items.append(item)
            return True

    def remove_item(self, item: Item) -> bool:
        """Removes an item from the backpack. Returns True if successful."""
        if item in self.items:
            self.items.remove(item)
            return True
        return False


def use_consumable_item(player, item: Item) -> str:
    """Consumes scrolls, food, or elixirs and applies matching attribute alterations."""
    if item.type == "food":
        player.current_health = min(player.effective_max_health, player.current_health + item.health)
        return f"Eat {item.subtype}. You feel refreshed."

    elif item.type == "scroll":
        # Scrolls permanently increase statistics
        if item.max_health > 0:
            player.max_health += item.max_health
            player.current_health += item.max_health
            return f"Read {item.subtype}. Your Max HP permanently increased by +{item.max_health}!"

        elif item.dexterity > 0:
            player.dexterity += item.dexterity
            return f"Read {item.subtype}. Your Dexterity permanently increased by +{item.dexterity}!"

        elif item.strength > 0:
            player.strength += item.strength
            return f"Read {item.subtype}. Your Strength permanently increased by +{item.strength}!"

    elif item.type == "elixir":
        # Elixirs temporarily increase one attribute
        from domain.models.characters import ActiveElixir

        if item.max_health > 0:
            # Add boost to tracking list, duration: 15 turns
            player.active_elixirs.append(ActiveElixir("max_health", item.max_health, 15))
            player.current_health += item.max_health
            return f"Quaffed {item.subtype}. You feel a sudden surge of vitality! (Max HP +{item.max_health})"

        elif item.dexterity > 0:
            player.active_elixirs.append(ActiveElixir("dexterity", item.dexterity, 15))
            return f"Quaffed {item.subtype}. Your reflexes sharpen instantly! (Dexterity +{item.dexterity})"

        elif item.strength > 0:
            player.active_elixirs.append(ActiveElixir("strength", item.strength, 15))
            return f"Quaffed {item.subtype}. A surge of power flows through you! (Strength +{item.strength})"

    return "Nothing happens."
