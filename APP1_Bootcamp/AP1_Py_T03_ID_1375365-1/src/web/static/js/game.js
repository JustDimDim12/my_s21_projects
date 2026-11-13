(function () {
    const CELL_SYMBOLS = {
        1: 'X',
        '-1': 'O',
    };

    const CELL_CLASSES = {
        1: 'x-mark',
        '-1': 'o-mark',
    };

    let currentGameUuid = null;
    let currentBoard = null;
    let gameActive = false;

    const boardEl = document.getElementById('board');
    const statusEl = document.getElementById('status');
    const newGameBtn = document.getElementById('new-game-btn');
    const cells = document.querySelectorAll('.cell');

    function setStatus(message, type) {
        statusEl.textContent = message;
        statusEl.className = 'status';
        if (type) {
            statusEl.classList.add(type);
        }
    }

    function setLoading(isLoading) {
        if (isLoading) {
            statusEl.innerHTML = '<span class="spinner"></span> Thinking...';
            statusEl.className = 'status';
        }
    }

    function clearBoard() {
        cells.forEach(cell => {
            cell.innerHTML = '';
            cell.className = 'cell';
            cell.dataset.value = '0';
        });
    }

    function renderBoard(board) {
        clearBoard();
        if (!board) return;

        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                const value = board[i][j];
                const index = i * 3 + j;
                const cell = cells[index];
                cell.dataset.value = String(value);

                if (value !== 0) {
                    const mark = document.createElement('span');
                    mark.className = CELL_CLASSES[String(value)] || '';
                    mark.textContent = CELL_SYMBOLS[String(value)] || '';
                    cell.appendChild(mark);
                    cell.classList.add('taken');
                }
            }
        }
    }

    function getUuidFromPath() {
        const match = window.location.pathname.match(/^\/game\/([a-f0-9-]+)$/i);
        return match ? match[1] : null;
    }

    async function loadGame(uuid) {
        setLoading(true);
        try {
            const response = await fetch(`/api/game/${uuid}`);
            if (!response.ok) {
                throw new Error('Game not found');
            }
            const data = await response.json();
            currentGameUuid = data.uuid;
            currentBoard = data.board;
            gameActive = true;
            renderBoard(currentBoard);
            setStatus('Your turn! Click an empty cell to place O');
        } catch (err) {
            setStatus('Error: ' + err.message, 'error');
            currentGameUuid = null;
            currentBoard = null;
            gameActive = false;
        }
    }

    async function createGame() {
        setLoading(true);
        currentGameUuid = null;
        currentBoard = null;
        gameActive = false;

        try {
            const response = await fetch('/game', { method: 'POST' });
            const data = await response.json();

            if (!response.ok) {
                throw new Error(data.error || 'Failed to create game');
            }

            currentGameUuid = data.uuid;
            currentBoard = data.board;
            gameActive = true;
            renderBoard(currentBoard);
            history.replaceState(null, '', `/game/${data.uuid}`);
            setStatus('Your turn! Click an empty cell to place O');
        } catch (err) {
            setStatus('Error: ' + err.message, 'error');
        }
    }

    async function makeMove(row, col) {
        if (!gameActive || !currentGameUuid || !currentBoard) return;
        if (currentBoard[row][col] !== 0) return;

        setLoading(true);

        const newBoard = currentBoard.map(r => [...r]);
        newBoard[row][col] = -1;

        try {
            const response = await fetch(`/game/${currentGameUuid}`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ board: newBoard }),
            });
            const data = await response.json();

            if (!response.ok) {
                throw new Error(data.error || 'Invalid move');
            }

            if (data.status === 'playing') {
                currentBoard = data.board;
                renderBoard(currentBoard);
                setStatus('Your turn! Click an empty cell to place O');
            } else {
                window.location.href = `/game/${currentGameUuid}`;
            }
        } catch (err) {
            setStatus('Error: ' + err.message, 'error');
            gameActive = true;
        }
    }

    cells.forEach(cell => {
        cell.addEventListener('click', function () {
            if (!gameActive) return;
            const row = parseInt(this.dataset.row);
            const col = parseInt(this.dataset.col);
            makeMove(row, col);
        });
    });

    newGameBtn.addEventListener('click', createGame);

    const uuidFromPath = getUuidFromPath();
    if (uuidFromPath) {
        loadGame(uuidFromPath);
    } else {
        createGame();
    }
})();
