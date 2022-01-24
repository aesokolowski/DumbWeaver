// A.E. Sokolowski Jan 2022 NY, NY, USA
// Choices.h

#ifndef Choices_h
#define Choices_h

struct Choices {
    char *chosen_color,
	 *chosen_bg_color,
	 *chosen_tx_color;
};

struct Choices choices_constructor(char *);
//void handle_clr_chg(struct Choices *, char, char *); maybe future?
void free_choices(struct Choices *);

#endif /* Choices_h */

