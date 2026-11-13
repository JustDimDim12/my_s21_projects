# domain/services/combat.py
import random
from domain.models.characters import Character, Enemy


class CombatEngine:
    @staticmethod
    def resolve_player_attack(player: Character, enemy: Enemy) -> str:
        """Handles the hero player attacking a monster."""
        # 1. Vampire Variant Rule: The very first attack against a vampire always misses.
        if enemy.type == "Vampire" and not enemy.had_been_attacked:
            enemy.had_been_attacked = True
            return "You swing, but the Vampire evades your very first strike cleanly!"

        enemy.had_been_attacked = True

        # 2. Hit Check Formula (Dependent on Dexterity values)
        hit_chance = 0.4 + (player.effective_dexterity - enemy.dexterity) * 0.05
        hit_chance = max(0.05, min(0.95, hit_chance))  # Safety caps (5% to 95%)

        if random.random() > hit_chance:
            return f"You swing wildly at the {enemy.type} and miss."

        # 3. Damage Calculation (Attacker strength + weapon modifiers)
        damage = player.effective_strength + random.randint(0, 3)
        enemy.health -= damage

        # If the target is an Ogre, being attacked prepares it to counter-attack
        if enemy.type == "Ogre":
            enemy.ogre_resting = False

        if enemy.health <= 0:
            # Calculate dynamic gold reward based on monster difficulty values
            base_loot = enemy.hostility + enemy.strength + enemy.dexterity + (enemy.max_health // 2)
            gold_drop = random.randint(max(1, base_loot // 2), base_loot)
            player.treasure_collected += gold_drop
            return f"You smash the {enemy.type} for {damage} damage and defeat it! (+{gold_drop} Gold)"

        return f"You hit the {enemy.type} for {damage} damage."

    @staticmethod
    def resolve_enemy_attack(enemy: Enemy, player: Character) -> str:
        """Handles an enemy attacking the hero player."""
        # 1. Ogre Rule: Rests for one turn after every attack
        if enemy.type == "Ogre" and enemy.ogre_resting:
            enemy.ogre_resting = False  # Finishes resting this turn
            return "The Ogre is recovering its balance and skips its attack."

        # 2. Hit Check Formula
        hit_chance = 0.4 + (enemy.dexterity - player.effective_dexterity) * 0.05
        hit_chance = max(0.05, min(0.95, hit_chance))

        if random.random() > hit_chance:
            return f"The {enemy.type} lunges at you but misses."

        # 3. Damage Calculation
        damage = max(1, enemy.strength + random.randint(-1, 2))
        player.current_health -= damage

        log_msg = f"The {enemy.type} hits you for {damage} damage."

        # 4. Special Variable Attack Effects
        if enemy.type == "Vampire":
            # Steals some of the player's maximum health on a successful attack
            drain = max(1, damage // 2)
            player.max_health = max(1, player.max_health - drain)
            player.current_health = min(player.current_health, player.effective_max_health)
            log_msg += f" It drains {drain} points from your Max Health!"

        elif enemy.type == "Snake Mage":
            # Successful attack has a chance to put the player to sleep
            if random.random() < 0.35:
                player.sleep_turns = 2
                log_msg += " You feel intensely drowsy and fall fast asleep!"

        # If an Ogre successfully swings, it must trigger its rest state flag
        if enemy.type == "Ogre":
            enemy.ogre_resting = True

        return log_msg
