/* basic.h */

#ifndef BASIC_H
#define BASIC_H

/* Define const */
typedef int Status;
#define	MAX_HEIGHT	 41
#define	MAX_WIDTH	101
#define	MIN_HEIGHT	  5
#define	MIN_WIDTH	  7
#define MIN_SCR_W	  0
#define MIN_SCR_H	  0
#define SCRSIZE_W	150
#define SCRSIZE_H	 45
#define MAX_SCR_W	SCRSIZE_W-1
#define MAX_SCR_H	SCRSIZE_H-1
#define T_INTERVAL	  500000
#define	TRUE 		  1
#define	FALSE		  0
#define	OK			  1
#define	ERROR		  0
#define	INFEASIBLE	 -1
#define	OVERFLOW	 -2
#define STACK_INIT_SIZE 100
#define INCREMENT 	 10
#define CLS		system("clear")
#define PAUSE	getchar()

/* Define struct about maze */
typedef enum {
	GPLAY = 0,			// First shown screen
	GMAP = 1,			// Just show map for debugging
	GAUTOSOLVE = 2,		// Normal playing mode
	GHIGHSCORE = 3,		// Game terminated
	GHELP = 4,
	GEXIT = 5
} Gamemode;

typedef enum {
	DOWN = 1,
	RIGHT = 2,
	UP = 3,
	LEFT = 4,
} Direction;

typedef enum {
	SPACE = 0,
	WALL = 1,
	EXIT = 2,
	WALKED = 3,
	BLOCKED = 4,
//	PERSON = 5
} Blocktype;

typedef struct {
	int x;
	int y;
} Pos;

typedef struct {
	int height;
	int width;
	char data[MAX_HEIGHT][MAX_WIDTH];
} Map;

typedef struct {
	Pos pos;
	Direction direc;
} Person;

typedef Pos Cursor;


/* Define struct of stack */

typedef Person ElemType;

typedef struct{
	ElemType *base;
	ElemType *top;
	int stacksize;
} Stack, *stack_ptr;

#endif