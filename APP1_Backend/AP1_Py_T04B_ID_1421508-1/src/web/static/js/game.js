(function () {
    "use strict";

    const AUTH_KEY = "auth";
    const SYMBOLS = { 1: "X", "-1": "O" };

    let currentGame = null;
    let myUuid = null;
    let pollInterval = null;

    // ==================== DOM ====================

    const authScreen = document.getElementById("auth-screen");
    const lobbyScreen = document.getElementById("lobby-screen");
    const gameScreen = document.getElementById("game-screen");

    const authError = document.getElementById("auth-error");
    const gamesList = document.getElementById("games-list");
    const myGamesList = document.getElementById("my-games-list");
    const myMarkEl = document.getElementById("my-mark");
    const statusEl = document.getElementById("status");
    const cells = document.querySelectorAll(".cell");

    // ==================== AUTH ====================

    function getAuth() {
        return localStorage.getItem(AUTH_KEY);
    }

    function setAuth(login, password) {
        localStorage.setItem(
            AUTH_KEY,
            btoa(`${login}:${password}`)
        );
    }

    function clearAuth() {
        localStorage.removeItem(AUTH_KEY);
    }

    function showScreen(name) {
        authScreen.classList.add("hidden");
        lobbyScreen.classList.add("hidden");
        gameScreen.classList.add("hidden");

        if (name === "auth") {
            authScreen.classList.remove("hidden");
        } else if (name === "lobby") {
            lobbyScreen.classList.remove("hidden");
        } else if (name === "game") {
            gameScreen.classList.remove("hidden");
        }
    }

    function showAuthError(message) {
        authError.textContent = message;
        authError.classList.remove("hidden");
    }

    function hideAuthError() {
        authError.textContent = "";
        authError.classList.add("hidden");
    }

    async function authFetch(url, options = {}) {
        const auth = getAuth();

        if (!auth) {
            showScreen("auth");
            throw new Error("Not authenticated");
        }

        options.headers = Object.assign({}, options.headers, {
            "Authorization": auth
        });

        const response = await fetch(url, options);

        if (response.status === 401) {
            clearAuth();
            showScreen("auth");
            throw new Error("Session expired");
        }

        return response;
    }

    // ==================== AUTH ACTIONS ====================

    async function signup(login, password) {
        const response = await fetch("/signup", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ login, password })
        });

        if (response.status === 201) {
            await doLogin(login, password);
        } else {
            const data = await response.json().catch(() => ({}));
            showAuthError(data.error || "Signup failed");
        }
    }

    async function doLogin(login, password) {
        const encoded = btoa(`${login}:${password}`);

        const response = await fetch("/login", {
            method: "POST",
            headers: {
                "Authorization": encoded
            }
        });

        if (response.status === 200) {
            setAuth(login, password);

            const data = await response.json();

            myUuid = data.uuid;
            localStorage.setItem("login", login);

            hideAuthError();
            await goToLobby();
        } else {
            showAuthError("Invalid login or password");
        }
    }

    function logout() {
        stopPolling();
        clearAuth();

        localStorage.removeItem("login");

        myUuid = null;
        currentGame = null;

        showScreen("auth");
    }

    // ==================== LOBBY ====================

    async function goToLobby() {
        const login = localStorage.getItem("login");
        const helloEl = document.getElementById("hello-user");

        if (helloEl && login) {
            helloEl.textContent = `Hello, ${login}`;
        }

        showScreen("lobby");
        await Promise.all([
            loadAvailableGames(),
            loadMyGames()
        ]);
    }

    async function loadAvailableGames() {
        gamesList.innerHTML = '<p class="subtitle">Loading...</p>';

        try {
            const response = await authFetch("/games");
            const games = await response.json();

            if (!response.ok) {
                throw new Error(games.error || "Failed to load games");
            }

            renderGames(games);
        } catch (error) {
            gamesList.textContent = error.message;
        }
    }

    async function loadMyGames() {
        myGamesList.innerHTML = '<p class="subtitle">Loading...</p>';

        try {
            const response = await authFetch("/my-games");
            const games = await response.json();

            if (!response.ok) {
                throw new Error(games.error || "Failed to load your games");
            }

            renderMyGames(games);
        } catch (error) {
            myGamesList.textContent = error.message;
        }
    }

    function renderMyGames(games) {
        myGamesList.innerHTML = "";

        if (!games || games.length === 0) {
            myGamesList.innerHTML =
                '<p class="subtitle">You haven\'t created any games yet.</p>';
            return;
        }

        games.forEach(game => {
            const item = document.createElement("div");
            item.className = "game-item";

            const description = document.createElement("span");
            description.textContent =
                `Game ${game.uuid.slice(0, 8)}... (${game.state})`;

            const openButton = document.createElement("button");
            openButton.className = "btn-new btn-small";
            openButton.textContent = "Open";
            openButton.type = "button";

            openButton.addEventListener("click", () => {
                openGame(game.uuid);
            });

            item.appendChild(description);
            item.appendChild(openButton);

            myGamesList.appendChild(item);
        });
    }

    function renderGames(games) {
        gamesList.innerHTML = "";

        if (!games || games.length === 0) {
            gamesList.innerHTML =
                '<p class="subtitle">No available games. Create one or wait.</p>';
            return;
        }

        games.forEach(game => {
            const item = document.createElement("div");
            item.className = "game-item";

            const description = document.createElement("span");
            description.textContent =
                `Game ${game.uuid.slice(0, 8)}... (creator: ${game.player_mark})`;

            const joinButton = document.createElement("button");
            joinButton.className = "btn-new btn-small";
            joinButton.textContent = "Join";
            joinButton.type = "button";

            joinButton.addEventListener("click", () => {
                joinGame(game.uuid);
            });

            item.appendChild(description);
            item.appendChild(joinButton);
            gamesList.appendChild(item);
        });
    }

    async function openGame(gameUuid) {
        try {
            const response = await authFetch(`/api/game/${gameUuid}`);
            const data = await response.json();

            if (!response.ok) {
                throw new Error(data.error || "Failed to open game");
            }

            currentGame = data;

            stopPolling();
            showGameScreen();
        } catch (error) {
            alert(error.message);
        }
    }

    function getSelectedMark() {
        const radio = document.querySelector('input[name="mark"]:checked');
        return radio ? radio.value : "X";
    }

    // ==================== CREATE / JOIN GAME ====================

    async function createGame(mode) {
        const mark = getSelectedMark();

        try {
            const response = await authFetch("/game", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify({ mode, mark })
            });

            const data = await response.json();

            if (response.status === 201) {
                currentGame = data;

                stopPolling();
                showGameScreen();
            } else {
                alert(data.error || "Failed to create game");
            }
        } catch (error) {
            alert(error.message);
        }
    }

    async function joinGame(gameUuid) {
        try {
            const response = await authFetch(`/game/${gameUuid}/join`, {
                method: "POST"
            });

            const data = await response.json();

            if (response.status === 200) {
                currentGame = data;

                stopPolling();
                showGameScreen();
            } else {
                alert(data.error || "Failed to join game");
            }
        } catch (error) {
            alert(error.message);
        }
    }

    // ==================== GAME SCREEN ====================

    function showGameScreen() {
        showScreen("game");

        updateMyMark(currentGame);

        renderBoard(currentGame.board, currentGame);

        document.getElementById("game-uuid").textContent =
            `Game: ${currentGame.uuid}`;

        startPolling();
    }

    function startPolling() {
        stopPolling();

        pollInterval = setInterval(async () => {
            if (!currentGame) {
                return;
            }

            try {
                const response = await authFetch(
                    `/api/game/${currentGame.uuid}`
                );

                if (response.status === 404) {
                    const wasCreator =
                        currentGame.user_uuid === myUuid;

                    stopPolling();
                    currentGame = null;

                    await goToLobby();

                    if (wasCreator) {
                        alert(
                            "Your opponent left. The game has been closed and deleted."
                        );
                    }

                    return;
                }

                if (response.status !== 200) {
                    return;
                }

                const data = await response.json();

                const hasChanged =
                    data.state !== currentGame.state ||
                    data.current_player_uuid !== currentGame.current_player_uuid ||
                    data.winner_uuid !== currentGame.winner_uuid ||
                    data.player_mark !== currentGame.player_mark ||
                    data.opponent_mark !== currentGame.opponent_mark ||
                    JSON.stringify(data.board) !==
                        JSON.stringify(currentGame.board);

                if (hasChanged) {
                    currentGame = data;
                    renderBoard(currentGame.board, currentGame);
                }
            } catch (error) {
                console.log("[poll] error:", error.message);
            }
        }, 2000);
    }

    function stopPolling() {
        if (pollInterval) {
            clearInterval(pollInterval);
            pollInterval = null;
        }
    }

    // ==================== GAME LOGIC ====================

    function isMyTurn(game) {
        return game.current_player_uuid === myUuid;
    }

    function amICreator(game) {
        return game.user_uuid === myUuid;
    }

    function updateMyMark(game) {
        if (!game) return;

        myMarkEl.textContent = amICreator(game)
            ? game.player_mark
            : game.opponent_mark;
    }

    function myBoardValue(game) {
        return amICreator(game) ? -1 : 1;
    }

    function renderBoard(board, game) {
        updateMyMark(game);
        cells.forEach(cell => {
            cell.innerHTML = "";
            cell.className = "cell";
        });

        for (let row = 0; row < 3; row++) {
            for (let col = 0; col < 3; col++) {
                const value = board[row][col];
                const cell = cells[row * 3 + col];

                if (value !== 0) {
                    const symbol = value === -1
                        ? game.player_mark
                        : game.opponent_mark;

                    const span = document.createElement("span");

                    span.className =
                        symbol === "X" ? "x-mark" : "o-mark";

                    span.textContent = symbol;

                    cell.appendChild(span);
                    cell.classList.add("taken");
                }
            }
        }

        document.getElementById("game-uuid").textContent =
            `Game: ${game.uuid}`;

        updateStatus(game);
    }

    async function makeMove(row, col) {
        if (!currentGame || currentGame.state !== "player_turn") {
            return;
        }

        if (!isMyTurn(currentGame)) {
            return;
        }

        if (currentGame.board[row][col] !== 0) {
            return;
        }

        const value = myBoardValue(currentGame);

        const newBoard = currentGame.board.map(
            boardRow => [...boardRow]
        );

        newBoard[row][col] = value;

        try {
            const response = await authFetch(
                `/game/${currentGame.uuid}`,
                {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json"
                    },
                    body: JSON.stringify({ board: newBoard })
                }
            );

            const data = await response.json();

            if (response.status === 200) {
                currentGame = data;
                renderBoard(currentGame.board, currentGame);
            } else {
                alert(data.error || "Invalid move");
            }
        } catch (error) {
            alert(error.message);
        }
    }

    function updateStatus(game) {
        if (game.state === "player_wins") {
            const isMe = game.winner_uuid === myUuid;

            statusEl.textContent = isMe
                ? "You win!"
                : "Opponent wins!";

            statusEl.className = "status success";
            cells.forEach(cell => cell.classList.add("game-over"));

            return;
        }

        if (game.state === "draw") {
            statusEl.textContent = "Draw!";
            statusEl.className = "status warning";

            cells.forEach(cell => cell.classList.add("game-over"));

            return;
        }

        if (game.state === "waiting_for_players") {
            statusEl.textContent = "Waiting for opponent to join...";
            statusEl.className = "status warning";
            return;
        }

        if (isMyTurn(game)) {
            statusEl.textContent = "Your turn";
        } else {
            statusEl.textContent = "Waiting for opponent...";
        }

        statusEl.className = "status";
    }

    // ==================== INITIALIZATION ====================

    async function init() {
        const auth = getAuth();

        if (!auth) {
            showScreen("auth");
            return;
        }

        try {
            const response = await fetch("/login", {
                method: "POST",
                headers: {
                    "Authorization": auth
                }
            });

            if (response.status === 200) {
                const data = await response.json();

                myUuid = data.uuid;

                if (!localStorage.getItem("login")) {
                    const decoded = atob(auth);
                    const login = decoded.split(":")[0];

                    localStorage.setItem("login", login);
                }

                await goToLobby();
            } else {
                clearAuth();
                showScreen("auth");
            }
        } catch (error) {
            clearAuth();
            showScreen("auth");
        }
    }

    // ==================== EVENT LISTENERS ====================

    document.getElementById("tab-login").addEventListener("click", () => {
        document.getElementById("tab-login").classList.add("active");
        document.getElementById("tab-signup").classList.remove("active");

        document.getElementById("login-form").classList.remove("hidden");
        document.getElementById("signup-form").classList.add("hidden");

        hideAuthError();
    });

    document.getElementById("tab-signup").addEventListener("click", () => {
        document.getElementById("tab-signup").classList.add("active");
        document.getElementById("tab-login").classList.remove("active");

        document.getElementById("signup-form").classList.remove("hidden");
        document.getElementById("login-form").classList.add("hidden");

        hideAuthError();
    });

    document.getElementById("login-form").addEventListener(
        "submit",
        async event => {
            event.preventDefault();

            const login = document.getElementById("login-login").value.trim();
            const password = document.getElementById("login-password").value;

            if (!login || !password) {
                showAuthError("Enter login and password");
                return;
            }

            try {
                await doLogin(login, password);
            } catch (error) {
                showAuthError("Login failed");
            }
        }
    );

    document.getElementById("signup-form").addEventListener(
        "submit",
        async event => {
            event.preventDefault();

            const login = document.getElementById("signup-login").value.trim();
            const password = document.getElementById("signup-password").value;

            if (login.length < 3) {
                showAuthError("Login must be at least 3 chars");
                return;
            }

            if (password.length < 6) {
                showAuthError("Password must be at least 6 chars");
                return;
            }

            try {
                await signup(login, password);
            } catch (error) {
                showAuthError("Signup failed");
            }
        }
    );

    document.getElementById("new-vs-computer").addEventListener(
        "click",
        () => createGame("computer")
    );

    document.getElementById("new-vs-player").addEventListener(
        "click",
        () => createGame("player")
    );

    document.getElementById("new-vs-computer2").addEventListener(
        "click",
        () => createGame("computer")
    );

    document.getElementById("new-vs-player2").addEventListener(
        "click",
        () => createGame("player")
    );

    document.getElementById("refresh-games").addEventListener(
    "click",
    async () => {
        await Promise.all([
            loadAvailableGames(),
            loadMyGames()
        ]);
    }
);

    document.getElementById("logout-btn").addEventListener(
        "click",
        logout
    );

    document.getElementById("logout-btn2").addEventListener(
        "click",
        logout
    );

    document.getElementById("back-to-lobby").addEventListener(
        "click",
        async () => {
            if (!currentGame) {
                await goToLobby();
                return;
            }

            try {
                const response = await authFetch(
                    `/game/${currentGame.uuid}/leave`,
                    { method: "POST" }
                );

                if (response.status !== 200 && response.status !== 404) {
                    const data = await response.json();
                    alert(data.error || "Failed to leave game");
                    return;
                }

                stopPolling();
                currentGame = null;
                await goToLobby();

            } catch (error) {
                alert(error.message);
            }
        }
    );

    cells.forEach(cell => {
        cell.addEventListener("click", () => {
            if (cell.classList.contains("taken")) {
                return;
            }

            const row = Number.parseInt(cell.dataset.row, 10);
            const col = Number.parseInt(cell.dataset.col, 10);

            makeMove(row, col);
        });
    });

    init();
})();