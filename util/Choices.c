// A.E. Sokolowski Jan 2022 NY, NY, USA
// Choices.c

#include <stdlib.h>
#include <string.h>

#include "../include/constants/cl.h"
#include "../include/constants/cn.h"
#include "../include/util/Choices.h"

struct Choices choices_constructor(char *initial_clr)
{
    struct Choices choices;

    choices.chosen_color = malloc(sizeof(char) * cn.COLOR_BUFF);
    choices.chosen_bg_color = malloc(sizeof(char) * cn.COLOR_BUFF);
    choices.chosen_tx_color = malloc(sizeof(char) * cn.COLOR_BUFF);

    strncpy(choices.chosen_color, initial_clr, cn.COLOR_BUFF);
    strncpy(choices.chosen_bg_color, cl.BLUE_CSS, cn.COLOR_BUFF);
    strncpy(choices.chosen_tx_color, cl.SALMON_CSS, cn.COLOR_BUFF);

    return choices;
}

void free_choices(struct Choices *choices)
{
    free(choices->chosen_color);
    free(choices->chosen_bg_color);
    free(choices->chosen_tx_color);
}
