# domain/services/difficulty_balancer.py
from domain.models.characters import Character


class DifficultyBalancer:
    """Domain Service responsible for calculating Dynamic Difficulty Adjustment (DDA)."""

    @staticmethod
    def calculate_adjustment_factor(player: Character) -> float:
        """
        Analyzes historical runtime metrics to compute a balance offset.
        Returns a float between -1.0 (very easy adjustments) and 1.0 (very hard adjustments).
        """
        # Health Ratio (Struggling if frequently running low)
        hp_ratio = player.current_health / max(1, player.effective_max_health)

        # Kill to Hit Ratio (Efficiency of clearing rooms vs taking damage)
        # Avoid division by zero bugs
        safe_hits = max(1, player.hits_taken)
        combat_efficiency = player.enemies_defeated / safe_hits

        # Safe Exploration Speed
        # High traversals with low hits taken means the player is breezing past elements safely
        exploration_safety = player.tiles_traversed / safe_hits

        # If the character's health drops below 40% (e.g., 12/30 HP or 20/60 HP)
        # and they are taking heavy damage, immediately flag an emergency rescue state.
        if hp_ratio <= 0.40 or player.current_health <= 20:
            # If they are soaking tons of hits relative to kills, force an immediate absolute fallback floor
            if combat_efficiency < 1.0:
                return -1.0  # Force maximum difficulty drop (-1.0 means full rescue scaling)

        # Define scoring parameters
        score = 0.0

        # Adjust score based on health state
        if hp_ratio < 0.35:
            score -= 0.5  # Player is struggling and frequently near death
        elif hp_ratio > 0.85:
            score += 0.3  # Player has abundant surplus resources

        # Adjust score based on combat performance
        if combat_efficiency > 2.0:
            score += 0.4  # Killing machine: effortlessly slicing enemies without taking damage
        elif combat_efficiency < 0.5:
            score -= 0.3  # Struggling to confirm kills relative to damage absorbed

        # Adjust score based on map maneuvering efficiency
        if exploration_safety > 15.0:
            score += 0.3  # Safely exploring huge areas without friction

        # Bound the final balance factor stringently between -1.0 and 1.0
        return max(-1.0, min(1.0, score))
