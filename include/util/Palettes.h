// A.E. Sokolowski Jan 2022 NY, NY, USA
// Palettes.h

#ifndef Palettes_h
#define Palettes_h

struct Palettes {
    char *palette_name;

    char *color1sel,
	 *color1unsel,
	 *color2sel,
	 *color2unsel,
         *color3sel,
	 *color3unsel;
};

struct Palettes palettes_constructor(char *);
void init_palette(struct Palettes *, char *);
void free_palettes(struct Palettes *);

#endif /* Palettes_h */

