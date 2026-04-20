#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 25
#define COLS 80
#define MIN_DELAY 20
#define MAX_DELAY 1000
#define STEP_DELAY 20

static inline int idx(int rows, int cols, int r, int c);
static char *create_board(int rows, int cols);
static void destroy_board(char *b);
static void read_seed(char *b, int rows, int cols);
static void show_board(const char *b, int rows, int cols);
static int neighbors(const char *b, int rows, int cols, int r, int c);
static void step(const char *cur, char *next, int rows, int cols);

int main(void) {
    char *a = create_board(ROWS, COLS);
    char *b = create_board(ROWS, COLS);
    if (!a || !b) {
        destroy_board(a);
        destroy_board(b);
        return 1;
    }

    read_seed(a, ROWS, COLS);

    if (freopen("/dev/tty", "r", stdin) == NULL) {
    }

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    int delay = 200;
    while (1) {
        show_board(a, ROWS, COLS);

        int ch = getch();
        if (ch == ' ') break;
        if (ch == 'A' || ch == 'a') delay = (delay > MIN_DELAY) ? delay - STEP_DELAY : delay;
        if (ch == 'Z' || ch == 'z') delay = (delay < MAX_DELAY) ? delay + STEP_DELAY : delay;

        step(a, b, ROWS, COLS);
        char *tmp = a;
        a = b;
        b = tmp;
        napms(delay);
    }

    endwin();
    destroy_board(a);
    destroy_board(b);
    return 0;
}

static inline int idx(int rows, int cols, int r, int c) {
    r = (r + rows) % rows;
    c = (c + cols) % cols;
    return r * cols + c;
}

static char *create_board(int rows, int cols) { return calloc(rows * cols, 1); }

static void destroy_board(char *b) { free(b); }

static void read_seed(char *b, int rows, int cols) {
    int r, c;
    while (scanf("%d %d", &r, &c) == 2)
        if (r >= 0 && r < rows && c >= 0 && c < cols) b[idx(rows, cols, r, c)] = 1;
}

static void show_board(const char *b, int rows, int cols) {
    for (int r = 0; r < rows; ++r) {
        move(r, 0);
        for (int c = 0; c < cols; ++c) addch(b[idx(rows, cols, r, c)] ? 'O' : '.');
    }
    refresh();
}

static int neighbors(const char *b, int rows, int cols, int r, int c) {
    int n = 0;
    for (int dr = -1; dr <= 1; ++dr)
        for (int dc = -1; dc <= 1; ++dc)
            if (dr || dc) n += b[idx(rows, cols, r + dr, c + dc)];
    return n;
}

static void step(const char *cur, char *next, int rows, int cols) {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            int n = neighbors(cur, rows, cols, r, c);
            char alive = cur[idx(rows, cols, r, c)];
            next[idx(rows, cols, r, c)] = (n == 3 || (alive && n == 2));
        }
}