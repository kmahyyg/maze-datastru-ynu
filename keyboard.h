/* keyboard.h */

#ifndef KEYBOARD_H
#define KEYBOARD_H

/* Functions */
// void init_keyboard(void);
// void close_keyboard(void);
// int kbhit(void);
// int readch(void);

typedef enum {
	KBD_ESC, KBD_NUM_0, KBD_NUM_1, KBD_NUM_2, KBD_NUM_3, KBD_NUM_4, KBD_NUM_5, KBD_NUM_6, KBD_NUM_7, KBD_NUM_8, KBD_NUM_9,
	KBD_A, KBD_B, KBD_C, KBD_D, KBD_E, KBD_F, KBD_G, KBD_H, KBD_I, KBD_J, KBD_K, KBD_L, KBD_M, KBD_N, KBD_O, KBD_P, KBD_Q, 
	KBD_R, KBD_S, KBD_T, KBD_U, KBD_V, KBD_W, KBD_X, KBD_Y, KBD_Z, KBD_SPACE, KBD_BACKSPACE, KBD_TAB, KBD_PLUS, 
	KBD_MINUS, KBD_EQUAL, KBD_UPDOT, KBD_OPSQBRKT, KBD_CLSSQBRKT, KBD_ENTER, KBD_SEMICOLON, KBD_SINGLEQUOTE, KBD_SHARP,
	KBD_COMMA, KBD_DOT, KBD_SLASH, KBD_BACKSLASH, KBD_ARR_UP, KBD_ARR_DOWN, KBD_ARR_RIGHT, KBD_ARR_LEFT, KBD_PGUP, 
	KBD_PGDN, UNKNOWN
} Key;

int getch(void);
Key hitkey(void);
#endif