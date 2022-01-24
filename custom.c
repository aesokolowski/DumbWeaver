// A.E. Sokolowski Jan 2022 NY, NY, USA
// custom.c
// basics for simple C server lifted from https://www.youtube.com/watch?v=gk6NL1pZi1M

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "include/custom.h"

#include "include/constants/cl.h"
#include "include/constants/cn.h"
#include "include/constants/msg.h"
#include "include/constants/templ.h"

#include "include/util/Screen.h"
#include "include/util/Server.h"

// TODO: move the ncurses session stuff into a different function, after it closes calls launch,
// most importantly, see how ncurses can handle user input and use that
// to change the content of the h1 so it always isn't about Zoe farting.

int main()
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);

    return 0;
}

void launch(struct Server *server)
{
    int address_length = sizeof(server->address);
    int new_socket;

    char *request = malloc(sizeof(char) * cn.REQ_BUFF);
    char *header = malloc(sizeof(char) * cn.HEAD_BUFF);
    char *body = malloc(sizeof(char) * cn.BODY_BUFF);
    char *response = malloc(sizeof(char) * cn.REQ_BUFF);
    char *chosen_color = malloc(sizeof(char) * cn.COLOR_BUFF);
    char *chosen_bg_clr = malloc(sizeof(char) * cn.COLOR_BUFF);
    char *chosen_tx_clr = malloc(sizeof(char) * cn.COLOR_BUFF);

    time_t rawtime;
    struct tm *timeinfo;

    char choice;

    struct Screen screen;

    strncpy(chosen_color, cl.BLUE_SEL, cn.COLOR_BUFF);
    strncpy(chosen_bg_clr, cl.BLUE_CSS, cn.COLOR_BUFF);
    strncpy(chosen_tx_clr, cl.SALMON_CSS, cn.COLOR_BUFF);

    screen = screen_constructor(cn.WIN_H, cn.WIN_W);

    do {
        recalc_scr(&screen);

	mvwprintw(screen.win, 4, 2, "%s", msg.WELCOME);
	mvwprintw(screen.win, 5, 2, "%s ", msg.COLOR);
	if (strncmp(chosen_color, cl.BLUE_SEL, cn.COLOR_BUFF) == 0)
	{
            opt_hl(screen.win, cl.BLUE_SEL); 
	} else wprintw(screen.win, "%s ", cl.BLUE_UNSEL);
	if (strncmp(chosen_color, cl.GREEN_SEL, cn.COLOR_BUFF) == 0)
	{
	    opt_hl(screen.win, cl.GREEN_SEL);
	} else wprintw(screen.win, "%s ", cl.GREEN_UNSEL);
	if (strncmp(chosen_color, cl.RED_SEL, cn.COLOR_BUFF) == 0)
	{
            opt_hl(screen.win, cl.RED_SEL);
	} else wprintw(screen.win, "%s ", cl.RED_UNSEL);
	mvwprintw(screen.win, 7, 2, "%s", cn.OKAY);

        refresh_scr(&screen);
        choice = getch();

	switch (choice)
	{
            case 'b':
		strncpy(chosen_color, cl.BLUE_SEL, cn.COLOR_BUFF);
		strncpy(chosen_bg_clr, cl.BLUE_CSS, cn.COLOR_BUFF);
	        break;
	    case 'g':
	        strncpy(chosen_color, cl.GREEN_SEL, cn.COLOR_BUFF);
		strncpy(chosen_bg_clr, cl.GREEN_CSS, cn.COLOR_BUFF);
		break;
	    case 'r':
		strncpy(chosen_color, cl.RED_SEL, cn.COLOR_BUFF);
		strncpy(chosen_bg_clr, cl.RED_CSS, cn.COLOR_BUFF);
	    default:
		break;
        }

	if (choice != 'o') clear();
    } while (choice != 'o');

    choice = 's';
    strncpy(chosen_color, cl.SALMON_SEL, cn.COLOR_BUFF);

    do {
	mvwprintw(screen.win, 5, 2, "%s ", msg.TEXT);
	if (strncmp(chosen_color, cl.SALMON_SEL, cn.COLOR_BUFF) == 0)
	{
            opt_hl(screen.win, cl.SALMON_SEL); 
	} else wprintw(screen.win, "%s ", cl.SALMON_UNSEL);
	if (strncmp(chosen_color, cl.THISTLE_SEL, cn.COLOR_BUFF) == 0)
	{
	    opt_hl(screen.win, cl.THISTLE_SEL);
	} else wprintw(screen.win, "%s ", cl.THISTLE_UNSEL);
	if (strncmp(chosen_color, cl.TOMATO_SEL, cn.COLOR_BUFF) == 0)
	{
            opt_hl(screen.win, cl.TOMATO_SEL);
	} else wprintw(screen.win, "%s ", cl.TOMATO_UNSEL);
	mvwprintw(screen.win, 7, 2, "%s", cn.OKAY);

	wrefresh(screen.win);
	choice = getch();

        switch (choice)
	{
            case 's':
	        strncpy(chosen_color, cl.SALMON_SEL, cn.COLOR_BUFF);
		strncpy(chosen_tx_clr, cl.SALMON_CSS, cn.COLOR_BUFF);
		break;
	    case 't':
		strncpy(chosen_color, cl.THISTLE_SEL, cn.COLOR_BUFF);
		strncpy(chosen_tx_clr, cl.THISTLE_CSS, cn.COLOR_BUFF);
		break;
	    case 'm':
		strncpy(chosen_color, cl.TOMATO_SEL, cn.COLOR_BUFF);
		strncpy(chosen_tx_clr, cl.TOMATO_CSS, cn.COLOR_BUFF);
		break;
	    default:
		break;
        }
    } while (choice != 'o');

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    sprintf(body, templ.RESP_BODY, chosen_bg_clr, chosen_tx_clr);
    sprintf(header, templ.RESP_HEAD, asctime(timeinfo), strlen(body));
    strncpy(response, header, cn.HEAD_BUFF);
    strncat(response, body, cn.BODY_BUFF);

    free(chosen_color);
    free(chosen_bg_clr);
    free(header);
    free(body);

    kill_scr(&screen);

    while (1)
    {
        printf("...tippity-tapping our toes and whistling...\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
	read(new_socket, request, cn.REQ_BUFF);
        printf("%s\n", request);
	write(new_socket, response, strlen(response));
        close(new_socket);
    }

    free(request);
    free(response);
}

void opt_hl(WINDOW *win, char *str)
{
    wattron(win, A_REVERSE);
    wprintw(win, "%s", str);
    wattroff(win, A_REVERSE);
    wprintw(win, " ");
}

