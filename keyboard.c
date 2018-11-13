/* keyboard.c */

#include <stdio.h>
#include <termios.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "keyboard.h"

int getch(){
	int c = 0;
	struct termios org_opts, new_opts;
	int res = 0;
	/* store old */
	res = tcgetattr(STDIN_FILENO, &org_opts);
	assert(res == 0);
	/* set new terminal parms */
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL );
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c = getchar();
	/* restore old */
	res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert (res == 0);
	return c;
}

Key hitkey(){
	char key;
	key = getch();
	if (key > 96 && key <= 122)
		return KBD_A + key - 97;
	else if (key > 64 && key <= 90)
		return KBD_A + key - 65;
	else if (key >= 48 && key < 58)
		return KBD_NUM_0 + key - 48;
	else if (key == 9)
		return KBD_TAB;
	else if (key == 10)
		return KBD_ENTER;
	else if (key == 32)
		return KBD_SPACE;
	else if (key == 127)
		return KBD_BACKSPACE;
	else if (key == 43)
		return KBD_PLUS;
	else if (key == 45)
		return KBD_MINUS;
	else if (key == 61)
		return KBD_EQUAL;
	else if (key == 96)
		return KBD_UPDOT;
	else if (key == 91)
		return KBD_OPSQBRKT;
	else if (key == 93)
		return KBD_CLSSQBRKT;
	else if (key == 59)
		return KBD_SEMICOLON;
	else if (key == 39)
		return KBD_SINGLEQUOTE;
	else if (key == 92)
		return KBD_SHARP;
	else if (key == 44)
		return KBD_COMMA;
	else if (key == 46)
		return KBD_DOT;
	else if (key == 47)
		return KBD_SLASH;
	else if (key == 60)
		return KBD_BACKSLASH;
	else if (key == 27){
		key = getch();
		if (key == 91){
			key = getch();
			if (key == 53){
				if ((key = getch()) == 126)
					return KBD_PGUP;
				else
					return UNKNOWN;
			}
			else if (key == 54)
				if ((key = getch()) == 126)
					return KBD_PGDN;
				else
					return UNKNOWN;
			else if (key > 64 && key < 69)
				return KBD_ARR_UP + key - 65;
			else
				return UNKNOWN;
		} else if (key == 27)
			return KBD_ESC;
		else 
			return UNKNOWN;
	}
	else
		return UNKNOWN;
}