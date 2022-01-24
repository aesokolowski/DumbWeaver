// A.E. Sokolowski Jan 2022 NY, NY, USA
// Screen.h

#ifndef Screen_h
#define Screen_h

#include <ncurses.h>

struct Screen
{
    WINDOW *win;
    int height,
	width,
	y,
	x;
};

struct Screen screen_constructor(int, int);

void recalc_scr(struct Screen *);
void refresh_scr(struct Screen *);
void kill_scr(struct Screen *);

#endif /* Screen_h */
