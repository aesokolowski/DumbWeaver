// A.E. Sokolowski Jan 2022 NY, NY, USA
// Screen.c

#include <ncurses.h>

#include "../include/constants/bd.h"

#include "../include/util/Screen.h"

struct Screen screen_constructor(int height, int width)
{
    struct Screen screen;

    initscr();
    cbreak();
    noecho();

    screen.height = height;
    screen.width = width;

    recalc_scr(&screen);
    refresh_scr(&screen);

    return screen;
};

void recalc_scr(struct Screen *screen)
{
    getmaxyx(stdscr, screen->y, screen->x);

    screen->win = newwin(screen->height,
            screen->width,
	    screen->y / 2 - screen->height / 2,
	    screen->x / 2 - screen->width / 2);
}

void refresh_scr(struct Screen *screen)
{
    wborder(screen->win, bd.LEFT, bd.RIGHT, bd.TOP, bd.BOTTOM, bd.TOP_LEFT,
            bd.TOP_RIGHT, bd.BOTTOM_LEFT, bd.BOTTOM_RIGHT);
    refresh();
    wrefresh(screen->win);
}

void kill_scr(struct Screen *screen)
{
    screen->win = NULL;
    screen->height = 0;
    screen->width = 0;
    screen->y = 0;
    screen->x = 0;
    endwin();
}

