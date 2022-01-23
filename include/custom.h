#ifndef custom_h
#define custom_h

#include <ncurses.h>

#include "Server.h"

void launch(struct Server *); //  launch(server)
void opt_hl(WINDOW *, char *); // option highlight(win, str)

#endif /* custom */

