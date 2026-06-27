# presentation/inventoryController
from domain.models.item import use_consumable_item


class InventoryController:
    def __init__(self, view):
        self.view = view

    def process_input(self, key, session, game_log):
        if key in [ord('h'), ord('H')]:
            self._handle_weapon(session, game_log)
            return True
        if key in [ord('j'), ord('J')]:
            self._handle_consumable(session, game_log, 'food', 'food')
            return True
        if key in [ord('k'), ord('K')]:
            self._handle_consumable(session, game_log, 'elixir', 'elixir')
            return True
        if key in [ord('e'), ord('E')]:
            self._handle_consumable(session, game_log, 'scroll', 'scroll')
            return True
        return False

    # handler into menu
    def _select_from_menu(self, items, item_type, allow_unequip):

        if not items:
            self.view.draw_item_menu(items, item_type, allow_unequip)
            self.view.screen.getch()
            return -1

        self.view.draw_item_menu(items, item_type, allow_unequip)

        while True:
            key = self.view.screen.getch()
            if key == 27:  # ESC
                return -1
            if key == ord('0'):
                return -2 if allow_unequip else -1
            if ord('1') <= key <= ord('9'):
                idx = key - ord('1')
                if 0 <= idx < len(items):
                    return idx

    def _handle_weapon(self, session, game_log):
        # 1. Filter all weapons currently in the backpack
        weapons = [i for i in session.player.backpack.items if i.type == 'weapon']

        # 2. Get the player's menu selection choice
        choice = self._select_from_menu(weapons, 'weapon', allow_unequip=True)

        if choice == -2:
            # Tell the session to handle unequipping choice '0'
            message = session.unequip_current_weapon_to_backpack()
            game_log.append(message)

        elif choice >= 0:
            # Tell the session to handle equipping choice '1'-'9'
            selected_weapon = weapons[choice]
            message = session.equip_weapon_from_backpack(selected_weapon)
            game_log.append(message)

    def _handle_consumable(self, session, game_log, item_type, menu_type):
        items = [i for i in session.player.backpack.items if i.type == item_type]
        choice = self._select_from_menu(items, menu_type, allow_unequip=False)
        if choice >= 0:
            selected = items[choice]
            msg = use_consumable_item(session.player, selected)
            game_log.append(msg)
            session.player.backpack.remove_item(selected)
