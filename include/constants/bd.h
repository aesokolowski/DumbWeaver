// A.E. Sokolowski Jan 2022 NY, NY, USA
// bd.h

#ifndef bd_h
#define bd_h

struct borders {
    char LEFT,
	 RIGHT,
	 TOP,
	 BOTTOM;

    char TOP_LEFT,
	 TOP_RIGHT,
	 BOTTOM_LEFT,
	 BOTTOM_RIGHT;
};

extern const struct borders bd;

#endif /* bd_h */

