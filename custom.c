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

#include "include/util/Choices.h"
#include "include/util/Screen.h"
#include "include/util/Server.h"

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
    char *headline_input = malloc(sizeof(char) * cn.BODY_BUFF);

    time_t rawtime;
    struct tm *timeinfo;

    char choice;

    struct Screen screen;
    struct Choices choices = choices_constructor(cl.BLUE_SEL);
    screen = screen_constructor(cn.WIN_H, cn.WIN_W, &choices);

    do {
        recalc_scr(&screen);
        print_menu(&screen, cl.BG_PAL);
        refresh_scr(&screen);
        choice = getch();

	// putting extraction into Choices on hold because the case stuff seems annoying
	// IDEA: in Palettes add a string i.e. "bgr" for cl.BG_PAL and "stm"for cl.TX_PAL
	switch (choice)
	{
            case 'b':
		strncpy(choices.chosen_color, cl.BLUE_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_bg_color, cl.BLUE_CSS, cn.COLOR_BUFF);
	        break;
	    case 'g':
	        strncpy(choices.chosen_color, cl.GREEN_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_bg_color, cl.GREEN_CSS, cn.COLOR_BUFF);
		break;
	    case 'r':
		strncpy(choices.chosen_color, cl.RED_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_bg_color, cl.RED_CSS, cn.COLOR_BUFF);
	    default:
		break;
        }
    } while (choice != 'o');

    choice = 's';
    strncpy(choices.chosen_color, cl.SALMON_SEL, cn.COLOR_BUFF);

    do {
	recalc_scr(&screen);
	print_menu(&screen, cl.TX_PAL);
	refresh_scr(&screen);
	choice = getch();

        switch (choice)
	{
            case 's':
	        strncpy(choices.chosen_color, cl.SALMON_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_tx_color, cl.SALMON_CSS, cn.COLOR_BUFF);
		break;
	    case 't':
		strncpy(choices.chosen_color, cl.THISTLE_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_tx_color, cl.THISTLE_CSS, cn.COLOR_BUFF);
		break;
	    case 'm':
		strncpy(choices.chosen_color, cl.TOMATO_SEL, cn.COLOR_BUFF);
		strncpy(choices.chosen_tx_color, cl.TOMATO_CSS, cn.COLOR_BUFF);
		break;
	    default:
		break;
        }
    } while (choice != 'o');

    clear();

    // NOTES: need to figure out how to not backup too far but I'll worry about that after
    // basic functionality is established
    strncpy(headline_input, "", 2);
    mvprintw(0, 0, "type a headline and press ENTER when you're done: ");
    do {
        choice = getch();
	if (choice == cn.BS_KEY) {
            int y, x;
	    int len = strlen(headline_input);

            if (len > 0) {
    	        getyx(stdscr, y, x);
	        --x;
	        move(y, x);
	        delch();
                headline_input[len - 1] = '\0';
	    }
	} else {
	    char *ch_str = malloc(sizeof(char) * 2);

	    snprintf(ch_str, 2, "%c", choice);
	    printw(ch_str);
	    headline_input[strlen(headline_input)] = choice;
	    free(ch_str);
	}

	refresh();
    } while (choice != '\n');

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // change sprintf's to snprintf's
    sprintf(body, templ.RESP_BODY, choices.chosen_bg_color, choices.chosen_tx_color, headline_input);
    sprintf(header, templ.RESP_HEAD, asctime(timeinfo), strlen(body));
    strncpy(response, header, cn.HEAD_BUFF);
    strncat(response, body, cn.BODY_BUFF);

    free_choices(&choices);
    free(header);
    free(body);
    free(headline_input);

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

