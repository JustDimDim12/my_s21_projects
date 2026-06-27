# presentation/views.py
import curses
from domain.models.map import Level, Room, Position
from domain.services.session import GameSession


class GameView:
    """Handles terminal screen initialization and rendering logic using curses."""

    def __init__(self, stdscr):
        """Initializes the view wrapper with the main screen context."""
        self.screen = stdscr
        self._setup_curses_environment()

    def _setup_curses_environment(self) -> None:
        """Configures specific terminal options required for standard Rogue."""
        curses.curs_set(0)  # Hide the flashing text cursor completely
        self.screen.nodelay(False)  # Make getch() pause and wait for keyboard presses
        self.screen.keypad(True)  # Enable capturing arrow keys and function keys
        curses.noecho()  # Stop typed letters from leaking onto the grid

        # Initialize Curses Color Palette pairs
        # COLOR_BLACK instead of -1 to prevent initialization crashes
        if curses.has_colors():
            curses.start_color()
            # Arguments: PairID, Foreground Color, Background Color (Standard Black)
            curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK)  # Zombie (z)
            curses.init_pair(2, curses.COLOR_RED, curses.COLOR_BLACK)  # Vampire (v)
            curses.init_pair(3, curses.COLOR_YELLOW, curses.COLOR_BLACK)  # Ogre (o)
            curses.init_pair(4, curses.COLOR_WHITE, curses.COLOR_BLACK)

    def _safe_addch(self, y: int, x: int, char: str) -> None:
        """Safely draws a character to the screen only if it falls inside window boundaries."""
        max_y, max_x = self.screen.getmaxyx()
        # Prevent drawing on the bottom-right corner pixel to avoid terminal scrolling crashes
        if y == max_y - 1 and x == max_x - 1:
            return
        if 0 <= y < max_y and 0 <= x < max_x:
            try:
                self.screen.addch(y, x, char)
            except curses.error:
                pass  # Suppress any underlying character edge tracking edge cases safely

    def _safe_addch_with_color(self, y: int, x: int, char: str, attr: int) -> None:
        """Safely draws a color-attributed character to the screen inside boundaries."""
        max_y, max_x = self.screen.getmaxyx()
        if y == max_y - 1 and x == max_x - 1:
            return
        if 0 <= y < max_y and 0 <= x < max_x:
            try:
                self.screen.addch(y, x, char, attr)
            except curses.error:
                pass

    def get_key(self) -> int:
        return self.screen.getch()

    # draw item menu
    def draw_item_menu(self, items, item_type, allow_unequip):
        self.screen.clear()
        titles = {
            'weapon': 'Choose a weapon',
            'food': 'Choose food',
            'elixir': 'Choose an elixir',
            'scroll': 'Choose a scroll'
        }
        title = titles.get(item_type, 'Items')
        self.screen.addstr(0, 2, f"=== {title} ===")

        if not items:
            self.screen.addstr(2, 4, "No items of this type.")
            self.screen.refresh()
            return

        for idx, item in enumerate(items):
            desc = item.subtype
            if item_type == 'food':
                desc += f" (restore +{item.health} HP)"
            elif item_type in ('elixir', 'scroll'):
                bonuses = []
                if item.max_health:
                    bonuses.append(f"HP+{item.max_health}")
                if item.dexterity:
                    bonuses.append(f"Dex+{item.dexterity}")
                if item.strength:
                    bonuses.append(f"Str+{item.strength}")
                if bonuses:
                    desc += f" ({', '.join(bonuses)})"
            elif item_type == 'weapon':
                desc += f" (strength +{item.strength})"
            self.screen.addstr(idx + 2, 4, f"{idx + 1}. {desc}")

        if allow_unequip:
            self.screen.addstr(len(items) + 3, 4, "0. Unequip weapon")
        else:
            self.screen.addstr(len(items) + 3, 4, "0. Cancel")
        self.screen.addstr(len(items) + 5, 4, "ESC - exit")
        self.screen.refresh()

    def capture_movement_vector(self, key: int, current_pos: Position, game_log) -> Position:
        """
        Pauses and waits for a keyboard stroke input using curses.
        Maps inputs into a new calculated target Position vector grid.
        """
        # key = self.screen.getch()
        # 1. Catch the Save & Quit Hotkey (Shift + Q)
        if key in [ord('q'), ord('Q')]:
            game_log.append("Saving game progress... Goodbye!")
            return Position(-1, -1)  # Special exit signal token Sent Upstream

        # Translate key codes into spatial translation coordinates
        dx, dy = 0, 0
        if key in [curses.KEY_UP, ord('w'), ord('W')]:
            dy = -1
        elif key in [curses.KEY_DOWN, ord('s'), ord('S')]:
            dy = 1
        elif key in [curses.KEY_LEFT, ord('a'), ord('A')]:
            dx = -1
        elif key in [curses.KEY_RIGHT, ord('d'), ord('D')]:
            dx = 1

        return Position(current_pos.x + dx, current_pos.y + dy)

    def render_game_state(self, session: GameSession, game_log: list[str]) -> None:
        """
        Main presentation pass. Clears the canvas, updates the dungeon frame,
        injects characters/enemies/items, and displays HUD text panels.
        """
        self.screen.clear()
        level = session.current_level
        if not level:
            return

        # Fetch visibility tracking metadata references
        discovered = session.visibility.discovered_tiles
        player_pos = session.player.position

        # 1. Draw walkable corridors
        for corridor in level.corridors:
            for pos in corridor.path:
                if pos in discovered:
                    inside_any_room = any(not r.is_maze and (
                            r.top_left.x < pos.x < r.top_left.x + r.width - 1 and r.top_left.y < pos.y < r.top_left.y + r.height - 1)
                                          for r in level.rooms)
                    if not inside_any_room:
                        self._safe_addch(pos.y, pos.x, '#')
        # 2. Draw static room structures
        for room in level.rooms:
            if room.is_maze:
                pos = room.top_left
                if pos in discovered:
                    self._safe_addch(pos.y, pos.x, '#')
            else:
                # Rule: Check if the player is physically inside this specific room rectangle bounds
                player_is_inside = (
                        room.top_left.x <= player_pos.x <= room.top_left.x + room.width - 1 and
                        room.top_left.y <= player_pos.y <= room.top_left.y + room.height - 1
                )

                room_seen = False
                for y in range(room.top_left.y, room.top_left.y + room.height):
                    for x in range(room.top_left.x, room.top_left.x + room.width):
                        if Position(x, y) in discovered:
                            room_seen = True
                            break
                    if room_seen:
                        break

                # If the room was discovered, draw its borders
                if room_seen:
                    self._draw_room_borders(room)
                    # Floor interior dots are ONLY visible if the player is actively inside!
                    if player_is_inside:
                        self._fill_room_floor(room)

        # 3. Draw Stairs / Exit Position if it sits on a discovered coordinate square
        if level.exit_position and level.exit_position in discovered:
            self._safe_addch(level.exit_position.y, level.exit_position.x, '>')

        # 4. Draw Items if they are sitting on a discovered coordinate square
        for pos, item in level.items_map.items():
            if pos in discovered:
                # Rule: Hide items if they belong to a room the player has left
                if not self._is_position_visible_actor(pos, session, player_pos):
                    continue
                char_map = {"food": "%", "scroll": "?", "elixir": "!", "weapon": ")"}
                icon = char_map.get(item.type, "*")
                self._safe_addch(pos.y, pos.x, icon)

        # 5. Draw all active enemies
        for enemy in level.enemies_list:
            color_pair_id = 4
            if enemy.position in discovered:
                # Task 4 Fog Rule: Don't render enemies if they reside in unoccupied rooms!
                if not self._is_position_visible_actor(enemy.position, session, player_pos):
                    continue
                if enemy.type == "Ghost" and enemy.is_invisible:
                    continue

                if enemy.is_mimic and not enemy.is_awake:
                    self._safe_addch(enemy.position.y, enemy.position.x, enemy.mimic_symbol)
                    continue

                if enemy.type == "Zombie":
                    color_pair_id = 1
                elif enemy.type == "Vampire":
                    color_pair_id = 2
                elif enemy.type == "Ogre":
                    color_pair_id = 3
                # Pass the color pair attribute directly into curses addch helper
                self._safe_addch_with_color(
                    enemy.position.y,
                    enemy.position.x,
                    enemy.color_char,
                    curses.color_pair(color_pair_id)
                )

        # 6. Draw the player character symbol over everything else
        self._safe_addch(session.player.position.y, session.player.position.x, '@')

        # 7. Render the persistent HUD Status Bar (Task 2 Specifications)
        # Displays variables via your safe properties (e.g. effective_max_health)
        hud_text = (
            f"Level: {session.current_level.depth}  "
            f"HP: {session.player.current_health}/{session.player.effective_max_health}  "
            f"Str: {session.player.effective_strength}  "
            f"Dex: {session.player.effective_dexterity}  "
            f"Gold: {session.score}"
        )
        # Print status HUD row near the bottom window bounds
        max_y, _ = self.screen.getmaxyx()
        try:
            self.screen.addstr(max_y - 2, 2, hud_text)
        except curses.error:
            pass

        # 8. Render recent action messages
        if game_log:
            latest_msg = game_log[-1]  # Fetch the most recent combat log entry
            try:
                self.screen.addstr(0, 2, f"Log: {latest_msg}")
            except curses.error:
                pass

        self.screen.refresh()

    def _is_position_visible_actor(self, pos: Position, session: GameSession, player_pos: Position) -> bool:
        """Determines if actors/items should draw based on player proximity and room constraints."""
        discovered = session.visibility.discovered_tiles
        level = session.current_level
        if not level:
            return False

        if abs(pos.x - player_pos.x) <= 1 and abs(pos.y - player_pos.y) <= 1:
            return True

        # Enforce Room Visibility first: Shrunk padding isolates floor cells from corridor overlays
        for room in level.rooms:
            if not room.is_maze:
                if (
                        room.top_left.x + 1 <= pos.x < room.top_left.x + room.width - 1 and room.top_left.y + 1 <= pos.y < room.top_left.y + room.height - 1):
                    return (
                            room.top_left.x + 1 <= player_pos.x < room.top_left.x + room.width - 1 and room.top_left.y + 1 <= player_pos.y < room.top_left.y + room.height - 1)

        # Corridor Visibility fallback
        return any(pos in c.path for c in level.corridors) and pos in discovered

    def _draw_room_borders(self, room: Room) -> None:
        """Draws a box representing a room on the screen coordinate map using boundary protection."""
        # Draw horizontal floor/ceiling boundaries
        for x in range(room.top_left.x, room.top_left.x + room.width):
            self._safe_addch(room.top_left.y, x, '-')
            self._safe_addch(room.top_left.y + room.height - 1, x, '-')

        # Draw vertical wall boundaries
        for y in range(room.top_left.y, room.top_left.y + room.height):
            self._safe_addch(y, room.top_left.x, '|')
            self._safe_addch(y, room.top_left.x + room.width - 1, '|')

        # Draw the standard room corners as intersections
        self._safe_addch(room.top_left.y, room.top_left.x, '+')
        self._safe_addch(room.top_left.y, room.top_left.x + room.width - 1, '+')
        self._safe_addch(room.top_left.y + room.height - 1, room.top_left.x, '+')
        self._safe_addch(room.top_left.y + room.height - 1, room.top_left.x + room.width - 1, '+')

    def _fill_room_floor(self, room: Room) -> None:
        """Fills the inner floor area of a room with the classic dot character."""
        for y in range(room.top_left.y + 1, room.top_left.y + room.height - 1):
            for x in range(room.top_left.x + 1, room.top_left.x + room.width - 1):
                self._safe_addch(y, x, '.')

    def render_leaderboard(self, high_scores: list[dict]) -> None:
        """
        Renders a persistent high-score leaderboard matrix.
        Shows granular running metrics for all playthroughs.
        """
        self.screen.clear()
        max_y, max_x = self.screen.getmaxyx()

        self.screen.addstr(2, 2, "=== DUNGEON LEADERBOARD (ALL-TIME BEST RUNS) ===", curses.A_REVERSE)
        self.screen.addstr(4, 2, f"{'RANK':<6}{'GOLD':<8}{'DEPTH':<8}{'KILLS':<8}{'FOOD':<6}{'TILES':<8}",
                           curses.A_BOLD)
        self.screen.addstr(5, 2, "-" * 50)

        # Display up to the top 10 best runs from persistent data
        for i, run in enumerate(high_scores[:10]):
            rank = f"#{i + 1}"
            gold = run.get("treasure", 0)
            depth = run.get("depth", 1)
            kills = run.get("enemies_defeated", 0)
            food = run.get("food_consumed", 0)
            tiles = run.get("tiles_traversed", 0)

            row_text = f"{rank:<6}{gold:<8}{depth:<8}{kills:<8}{food:<6}{tiles:<8}"
            self.screen.addstr(6 + i, 2, row_text)

        self.screen.addstr(max_y - 2, 2, "Press any key to return to exit...")
        self.screen.refresh()
        self.screen.getch()

    def draw_dda_transition_overlay(self, dda_score: float) -> None:
        """Draws a bold, centered flash screen explaining the difficulty shift."""
        self.screen.clear()
        max_y, max_x = self.screen.getmaxyx()

        # Calculate screen center coordinates
        center_y = max_y // 2
        center_x = max_x // 2

        # 1. Select text styling and warning messages based on performance
        if dda_score > 0.3:
            msg_header = "⚠️  THE DUNGEON ADAPTS  ⚠️"
            msg_body = "The catacombs sense your dominance. Monsters grow bloodthirsty."
            # Use Red text (Pair ID 5 from your setup) or Bold text
            attr = curses.color_pair(5) | curses.A_BOLD
        elif dda_score < -0.3:
            msg_header = "✨  A REPRIEVE  ✨"
            msg_body = "The spirits take pity on your broken form. Hazards diminish."
            # Use Cyan text (Pair ID 10) or Reverse color text
            attr = curses.color_pair(10) | curses.A_BOLD
        else:
            msg_header = "💀  DESCENDING DEEPER  💀"
            msg_body = "You gather your courage and step into the shifting darkness."
            attr = curses.color_pair(4) | curses.A_BOLD

        # 2. Render centered text blocks
        try:
            self.screen.addstr(center_y - 2, center_x - (len(msg_header) // 2), msg_header, attr)
            self.screen.addstr(center_y, center_x - (len(msg_body) // 2), msg_body, curses.A_NORMAL)

            prompt = "[ Press any key to continue your descent ]"
            self.screen.addstr(center_y + 3, center_x - (len(prompt) // 2), prompt, curses.A_BLINK)
        except curses.error:
            pass

        self.screen.refresh()

        # 3. Halt execution. Force user interaction to acknowledge the screen
        self.screen.getch()
