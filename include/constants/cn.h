#ifndef cn_h
#define cn_h

struct constants {
    int REQ_BUFF,
        HEAD_BUFF,
	BODY_BUFF,
	COLOR_BUFF;

    int WIN_H,
	WIN_W;

    int BS_KEY;

    char *OKAY;
};

extern const struct constants cn;

#endif /* cn_h */

