# main.py
import curses
from presentation.inventoryController import InventoryController
from domain import Character, Position, DungeonGenerator, GameSession, DifficultyBalancer
from presentation.views import GameView
from data.storage import ScoreStorage


def main(stdscr):
    # 1. Initialize the rendering interface view wrapper
    view = GameView(stdscr)
    generator = DungeonGenerator()
    inventory_controller = InventoryController(view)

    # 2. Check for an active saved session state on disk
    saved_snapshot = ScoreStorage.load_session_state()
    session = None
    game_log = []

    if saved_snapshot is not None:
        stdscr.clear()
        stdscr.addstr(2, 2, "=== ACTIVE SAVE FILE DETECTED ===", curses.A_BOLD)
        stdscr.addstr(4, 2, "Press [R] to Resume your last session")
        stdscr.addstr(5, 2, "Press [N] to start a New clean run")
        stdscr.refresh()

        while True:
            ch = stdscr.getch()
            if ch in [ord('r'), ord('R')]:
                # Build snapshot and explicitly inject the storage engine class reference
                session = GameSession.load_from_snapshot(saved_snapshot, generator)
                session.storage_engine = ScoreStorage
                game_log.append("Welcome back! Your saved session has been restored.")
                break
            elif ch in [ord('n'), ord('N')]:
                ScoreStorage.clear_save_file()
                break

    # 3. Create a fresh clean session if no save was loaded
    if session is None:
        #  Build the starting player hero character model
        player_character = Character(
            max_health=30,
            current_health=30,
            dexterity=12,
            strength=10,
            position=Position(x=10, y=5)  # Fallback start spot; generator re-positions this later
        )
        # 4. Generate the initial floor blueprint and hand it to the session
        session = GameSession(player=player_character, level_generator=generator)
        session.high_scores = ScoreStorage.load_scores()

        floor_one = generator.generate_level(depth=1)
        # Plop the player character safely inside a valid inner room tile
        if floor_one.rooms:
            start_room = floor_one.starting_room
            player_character.position = Position(
                x=start_room.top_left.x + 2,
                y=start_room.top_left.y + 2
            )

        session.descend_level(floor_one)
        # 5. Initialize the sliding message tracker log panel
        game_log.append("Welcome to the Dungeon! Use WASD or Arrow Keys to step.")

    # 3. Spin up the centralized domain loop coordinator
    # session = GameSession(player=player_character)
    # session.high_scores = ScoreStorage.load_scores()

    # session = GameSession(player=player_character, level_generator=generator)
    # session.high_scores = ScoreStorage.load_scores()
    # floor_one = generator.generate_level(depth=1)
    # # session.descend_level(floor_one)
    #
    #
    # if floor_one.rooms:
    #     start_room = floor_one.starting_room
    #     player_character.position = Position(
    #         x=start_room.top_left.x + 2,
    #         y=start_room.top_left.y + 2
    #     )
    #
    # session.descend_level(floor_one)

    # game_log = ["Welcome back to the Dungeon! Use WASD or Arrow Keys to step."]

    # 6. Run the turn-based execution loop
    while session.is_active:
        view.render_game_state(session, game_log)
        # key = view.get_key()
        key = view.screen.getch()  # Get key directly from screen matrix context

        # Pause and capture the destination target requested by user input
        target_pos = view.capture_movement_vector(key, session.player.position, game_log)

        # HANDLE THE Q / SHIFT+Q EXIT TRIGGER
        if target_pos == Position(-1, -1):
            # Save our deep domain data structure attributes into flat JSON strings
            ScoreStorage.save_session_state(session.to_serialized_dict())
            session.is_active = False  # Safely breaks the execution loop condition
            continue  # Skip normal physics, combat, and enemy step loops completely

        # -handler-controller for inventory
        if inventory_controller.process_input(key, session, game_log):
            continue

        if target_pos == session.current_level.exit_position:
            # 1. Compute dynamic multiplier offset using top-level import
            dda_score = DifficultyBalancer.calculate_adjustment_factor(session.player)

            # 2. Fire the full-screen visual color banner to block execution
            view.draw_dda_transition_overlay(dda_score)

            # 3. Call your completed session domain progression method
            session.process_turn_actions(target_pos, game_log)
            continue

        if target_pos != session.player.position:
            session.process_turn_actions(target_pos, game_log)
            continue

        # # --- Выход ---
        # if key == ord('q'):
        #     session.end_session()

    # Post-game screen block: Draw the terminal one final time to display the final message
    view.render_game_state(session, game_log)
    ScoreStorage.save_scores(session.high_scores)  # Write out the leaderboard table to disk

    # Trigger our new fullscreen statistics leaderboard screen viewer
    # Gives players visual access to their career metrics matrix histories
    view.render_leaderboard(session.high_scores)

    stdscr.getch()


if __name__ == "__main__":
    # The wrapper safely executes setup and automatically runs the teardown on close
    curses.wrapper(main)
