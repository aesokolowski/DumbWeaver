// A.E. Sokolowski Jan 2022 NY, NY, USA
// Screen.c

#include <ncurses.h>
#include <string.h>

#include "../include/constants/bd.h"
#include "../include/constants/cl.h"
#include "../include/constants/cn.h"
#include "../include/constants/msg.h"

#include "../include/util/Choices.h"
#include "../include/util/Screen.h"

struct Screen screen_constructor(int height, int width, struct Choices *choices)
{
    struct Screen screen;

    initscr();
    cbreak();
    noecho();

    screen.height = height;
    screen.width = width;
    screen.choices = choices;

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

void print_menu(struct Screen *screen, char *palette)
{
    char *color1sel,
        *color1unsel,
	*color2sel,
	*color2unsel,
	*color3sel,
	*color3unsel;

    if (strncmp(palette, cl.BG_PAL, cn.COLOR_BUFF) == 0) {
        color1sel = cl.BLUE_SEL;
	color1unsel = cl.BLUE_UNSEL;
	color2sel = cl.GREEN_SEL;
	color2unsel = cl.GREEN_UNSEL;
	color3sel = cl.RED_SEL;
	color3unsel = cl.RED_UNSEL;
    }

    mvwprintw(screen->win, 4, 2, "%s", msg.WELCOME);
    mvwprintw(screen->win, 5, 2, "%s ", msg.COLOR);
    if (strncmp(screen->choices->chosen_color, color1sel, cn.COLOR_BUFF) == 0)
    {
        opt_hl(screen->win, color1sel);
    } else wprintw(screen->win, "%s ", color1unsel);
    if (strncmp(screen->choices->chosen_color, color2sel, cn.COLOR_BUFF) == 0)
    {
        opt_hl(screen->win, color2sel);
    } else wprintw(screen->win, "%s ", color2unsel);
    if (strncmp(screen->choices->chosen_color, color3sel, cn.COLOR_BUFF) == 0)
    {
        opt_hl(screen->win, color3sel);
    } else wprintw(screen->win, "%s ", color3unsel);
    mvwprintw(screen->win, 7, 2, "%s", cn.OKAY);
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

void opt_hl(WINDOW *win, char *str)
{
    wattron(win, A_REVERSE);
    wprintw(win, "%s", str);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
}

