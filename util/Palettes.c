// A.E. Sokolowski Jan 2022 NY, NY, USA
// Palettes.c

#include <stdlib.h>
#include <string.h>

#include "../include/constants/cl.h"
#include "../include/constants/cn.h"
#include "../include/util/Palettes.h"

struct Palettes palettes_constructor(char *palette_name)
{
    struct Palettes palettes;

    palettes.palette_name = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color1sel = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color1unsel = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color2sel = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color2unsel = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color3sel = malloc(sizeof(char) * cn.COLOR_BUFF);
    palettes.color3unsel = malloc(sizeof(char) * cn.COLOR_BUFF);

    init_palette(&palettes, palette_name);

    return palettes;
}

void init_palette(struct Palettes *palettes, char *palette_name)
{
    strncpy(palettes->palette_name, palette_name, cn.COLOR_BUFF);	
    if (strncmp(palette_name, cl.BG_PAL, cn.COLOR_BUFF) == 0) {
        strncpy(palettes->color1sel, cl.BLUE_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color1unsel, cl.BLUE_UNSEL, cn.COLOR_BUFF);
        strncpy(palettes->color2sel, cl.GREEN_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color2unsel, cl.GREEN_UNSEL, cn.COLOR_BUFF);
        strncpy(palettes->color3sel, cl.RED_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color3unsel, cl.RED_UNSEL, cn.COLOR_BUFF);
    } else if (strncmp(palette_name, cl.TX_PAL, cn.COLOR_BUFF) == 0) {
        strncpy(palettes->color1sel, cl.SALMON_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color1unsel, cl.SALMON_UNSEL, cn.COLOR_BUFF);
        strncpy(palettes->color2sel, cl.THISTLE_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color2unsel, cl.THISTLE_UNSEL, cn.COLOR_BUFF);
        strncpy(palettes->color3sel, cl.TOMATO_SEL, cn.COLOR_BUFF);
        strncpy(palettes->color3unsel, cl.TOMATO_UNSEL, cn.COLOR_BUFF);
    }
}

void free_palettes(struct Palettes *palettes)
{
    free(palettes->palette_name);
    free(palettes->color1sel);
    free(palettes->color1unsel);
    free(palettes->color2sel);
    free(palettes->color2unsel);
    free(palettes->color3sel);
    free(palettes->color3unsel);
}

