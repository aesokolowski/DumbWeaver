// A.E. Sokolowski Jan 2022 NY, NY, USA
// Screen.h

#ifndef Screen_h
#define Screen_h

#include <ncurses.h>

struct Screen
{
    WINDOW *win;
    struct Choices *choices;

    int height,
	width,
	y,
	x;
};

struct Screen screen_constructor(int, int, struct Choices *);

void recalc_scr(struct Screen *);
void refresh_scr(struct Screen *);
void print_menu(struct Screen *, char *);
void kill_scr(struct Screen *);
void opt_hl(WINDOW *, char *);

#endif /* Screen_h */

