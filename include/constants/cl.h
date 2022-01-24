// A.E. Sokolowski Jan 2022 NY, NY

#ifndef cl_h
#define cl_h

struct colors {
    char *BLUE_SEL,
	 *BLUE_UNSEL,
	 *GREEN_SEL,
	 *GREEN_UNSEL,
	 *RED_SEL,
	 *RED_UNSEL;

    char *SALMON_SEL,
	 *SALMON_UNSEL,
	 *THISTLE_SEL,
	 *THISTLE_UNSEL,
	 *TOMATO_SEL,
	 *TOMATO_UNSEL;

    char *BLUE_CSS,
	 *GREEN_CSS,
	 *RED_CSS,
	 *SALMON_CSS,
	 *THISTLE_CSS,
	 *TOMATO_CSS;

    char *BG_PAL,
	 *TX_PAL;
};

extern const struct colors cl;

#endif /* cl_h */

