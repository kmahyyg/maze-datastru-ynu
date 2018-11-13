/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include "graphic.h"
#include "maze.h"
#include "keyboard.h"
#include "basic.h"
#include "time.h"

/* Windows Handle */
Gamemode chooseWindow();
void showMapWindow();
void playWindow();
void autoSolveWindow();
void highScoreWindow();
void helpWindow();
void exitWindow();

/* Define tart print point cursor */
Cursor start_cur = {0,0};

int main(){
	Gamemode mode;
	while (1){
		mode = chooseWindow();
		if (mode == GPLAY)
			playWindow();
		else if (mode == GMAP)
			showMapWindow();
		else if (mode == GAUTOSOLVE)
			autoSolveWindow();
		else if (mode == GHIGHSCORE)
			highScoreWindow();
		else if (mode == GHELP)
			helpWindow();
		else
			exitWindow();
	}

	return 0;
}

Gamemode chooseWindow(){
	CLS;
	Gamemode md = GPLAY;
	Key key;
	drawFrame();
	Cursor cur_a = {58,11};	// Define draw cursor a
	Cursor cur_b = {93,14};	// Define draw cursor b
	cur_a.x = 58; cur_a.y = 11;
	cur_b.x = 93; cur_b.y = 14;
	drawRectangle(cur_a, cur_b, '*');
	Cursor cur_op = {SCRSIZE_W/2,SCRSIZE_H/2-10};	// Define draw operation cursor 
	gotoAndPrintCenter(cur_op, "Maze Game");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "Version 1.1");
	cur_op.x -= 8;
	cur_op.y += 8;
	gotoAndPrintOption(cur_op, "Start Game");
	cur_op.y += 2;
	gotoAndPrintOption(cur_op, "Print Maze Map");
	cur_op.y += 2;
	gotoAndPrintOption(cur_op, "Auto Play Maze");
	cur_op.y += 2;
	gotoAndPrintOption(cur_op, "High Score");
	cur_op.y += 2;
	gotoAndPrintOption(cur_op, "Help");
	cur_op.y += 2;
	gotoAndPrintOption(cur_op, "Exit");
	cur_op.x -= 2;
	cur_op.y -= 10;
	gotoCursor(cur_op);
	// Option Part
	while (1){
		key = hitkey();
		if (key == KBD_ESC || key == KBD_Q){
			CLS;
			printf("Forcely quit.\n\n");
			exit(ERROR);
		}
		else if (key == KBD_ARR_UP){
			if (md == GPLAY){
				md+=6;
				cur_op.y+=12;
			}
			md--;
			cur_op.y -= 2;
			gotoCursor(cur_op);
		} else if (key == KBD_ARR_DOWN){
			if (md == GEXIT){
				md -= 6;
				cur_op.y -= 12;
			}
			md++;
			cur_op.y += 2;
			gotoCursor(cur_op);
		} else if (key == KBD_ENTER)
			return md;
		else
			continue;
	}
	return md;
}

void showMapWindow(){
	int x, y, i, isBreak = 0, isRedraw = 1, isQuit = 0;
	Map map;
	Key key;
	Cursor cur_a;	// Define draw cursor a
	while (1){
		if (isQuit == 1) break;
		isBreak = 0;
		CLS;
		drawFrame();
		Cursor cur_b = {1,MAX_SCR_H-2};	// Define draw cursor b
		gotoCursor(cur_b);
		for (i = 0; i < SCRSIZE_W - 2; i++)
			printf("_");
		cur_b.y++;
		gotoCursor(cur_b);
		cur_a = cur_b;
		// Input height
		while (1){
			gotoAndPrint(cur_a," >Input height: ");
			cur_b.x = 17;
			gotoCursor(cur_b);
			scanf("%d",&x);
			gotoCursor(cur_b);
			if (x < MIN_HEIGHT){
				gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input height)");
				hitkey(); hitkey();
				gotoAndPrint(cur_b, "                                                                              ");
				continue;
			} else if (x > MAX_HEIGHT-2){
				gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input height)");
				hitkey(); hitkey();
				gotoAndPrint(cur_b, "                                                                              ");
				continue;
			} else
				break;
		}
		gotoAndPrint(cur_b, "                                                                              ");
		// Input width
		while (1){
			gotoAndPrint(cur_a," >Input width: ");
			cur_b.x = 16;
			gotoCursor(cur_b);
			scanf("%d",&y);
			gotoCursor(cur_b);
			if (y < MIN_WIDTH){
				gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input width)");
				hitkey(); hitkey();
				gotoAndPrint(cur_b, "                                                                              ");
				continue;
			} else if (y > MAX_WIDTH-2){
				gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input width)");
				hitkey(); hitkey();
				gotoAndPrint(cur_b, "                                                                              ");
				continue;
			} else
				break;
		}
		if (x % 2 == 0) x--;
		if (y % 2 == 0) y--;
		start_cur.y = (SCRSIZE_H - 2 - x)/2;
		start_cur.x = (SCRSIZE_W - 4 - y)/2;
		gotoAndPrint(cur_a, " >Press n to show anothor random map, r to re-input width and height, q to quit.");
		// Show map
		while(1){
			if (isBreak == 1||isQuit == 1) break;
			if (isRedraw == 1){
				createMap(&map, (x-1)/2,(y-1)/2);
				printMap(&map);
				eraseMap(&map);
				isRedraw = 0;
			}
			gotoCursor(cur_a);
			key = hitkey();
			if (key == KBD_ENTER || key == KBD_N || key == KBD_ARR_DOWN || key == KBD_ARR_RIGHT)
				isRedraw = 1;
			else if (key == KBD_Q || key == KBD_ESC)
				isQuit = 1;
			else if (key == KBD_I || key == KBD_R)
				isBreak = 1;
			else
				continue;
		}
	}
	CLS;
}

void playWindow(){
	int x, y, i, isQuit = 0, isWin = 0;
	Map map;
	Key key;
	Cursor cur_a;	// Define draw cursor a
	CLS;
	drawFrame();
	Cursor cur_b = {1,MAX_SCR_H-2};	// Define draw cursor b
	gotoCursor(cur_b);
	for (i = 0; i < SCRSIZE_W - 2; i++)
		printf("_");
	cur_b.y++;
	gotoCursor(cur_b);
	cur_a = cur_b;
	// Input height
	while (1){
		gotoAndPrint(cur_a," >Input height: ");
		cur_b.x = 17;
		gotoCursor(cur_b);
		scanf("%d",&x);
		gotoCursor(cur_b);
		if (x < MIN_HEIGHT){
			gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input height)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else if (x > MAX_HEIGHT-2){
			gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input height)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else
			break;
	}
	gotoAndPrint(cur_b, "                                                                              ");
	// Input width
	while (1){
		gotoAndPrint(cur_a," >Input width: ");
		cur_b.x = 16;
		gotoCursor(cur_b);
		scanf("%d",&y);
		gotoCursor(cur_b);
		if (y < MIN_WIDTH){
			gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input width)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else if (y > MAX_WIDTH-2){
			gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input width)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else
			break;
	}
	if (x % 2 == 0) x--;
	if (y % 2 == 0) y--;
	start_cur.y = (SCRSIZE_H - 2 - x)/2;
	start_cur.x = (SCRSIZE_W - 4 - y)/2;
	createMap(&map, (x-1)/2,(y-1)/2);
	printMap(&map);
	gotoAndPrint(cur_a, " >Press r to restart and q to quit.");
	// play control
	Person person;
	person.pos.x = 1;
	person.pos.y = 1;
	printPerson(&person);
	// time_t start_t = time(0);
	clock_t start_t = clock();
	while (1){
		key = hitkey();
		if (key == KBD_Q)
			break;
		else if (key >= KBD_ARR_UP && key <= KBD_ARR_LEFT){
			erasePerson(&person);
			if (isMovable(&map, &person, key))
				if (key == KBD_ARR_UP)
					person.pos.y--;
				else if (key == KBD_ARR_DOWN)
					person.pos.y++;
				else if (key == KBD_ARR_LEFT)
					person.pos.x--;
				else if (key == KBD_ARR_RIGHT)
					person.pos.x++;
			printPerson(&person);
		}else if (key == KBD_R){
			erasePerson(&person);
			person.pos.x = 1;
			person.pos.y = 1;
			printPerson(&person);
			start_t = clock();
		}
		if (isReachExit(&map, &person)){
			isWin = 1;
			break;
		}
	}
	clock_t end_t = clock();
	eraseMap(&map);
	gotoAndPrint(cur_a, "                                                                                      ");
	if(isWin){
		gotoCursor(cur_a);
		printf(" > Conguatulations !!! You have finished it in %g seconds.", (double)(end_t - start_t)/1000);
		gotoCursor(cur_a);
	}
	else
		gotoAndPrint(cur_a, " > Failed... You quit the game.");
	gotoCursor(cur_a);
	while(1){
		key = hitkey();
			if (key == KBD_Q || key == KBD_ENTER || key == KBD_ESC)
				break;
	}
}

void autoSolveWindow(){
		int x, y, i, isQuit = 0, isWin = 0;
	Map map;
	Key key;
	Cursor cur_a;	// Define draw cursor a
	CLS;
	drawFrame();
	Cursor cur_b = {1,MAX_SCR_H-2};	// Define draw cursor b
	gotoCursor(cur_b);
	for (i = 0; i < SCRSIZE_W - 2; i++)
		printf("_");
	cur_b.y++;
	gotoCursor(cur_b);
	cur_a = cur_b;
	// Input height
	while (1){
		gotoAndPrint(cur_a," >Input height: ");
		cur_b.x = 17;
		gotoCursor(cur_b);
		scanf("%d",&x);
		gotoCursor(cur_b);
		if (x < MIN_HEIGHT){
			gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input height)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else if (x > MAX_HEIGHT-2){
			gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input height)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else
			break;
	}
	gotoAndPrint(cur_b, "                                                                              ");
	// Input width
	while (1){
		gotoAndPrint(cur_a," >Input width: ");
		cur_b.x = 16;
		gotoCursor(cur_b);
		scanf("%d",&y);
		gotoCursor(cur_b);
		if (y < MIN_WIDTH){
			gotoAndPrint(cur_a," >This value is too small. (Press any key to re-input width)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else if (y > MAX_WIDTH-2){
			gotoAndPrint(cur_a," >This value is too large. (Press any key to re-input width)");
			hitkey(); hitkey();
			gotoAndPrint(cur_b, "                                                                              ");
			continue;
		} else
			break;
	}
	if (x % 2 == 0) x--;
	if (y % 2 == 0) y--;
	start_cur.y = (SCRSIZE_H - 2 - x)/2;
	start_cur.x = (SCRSIZE_W - 4 - y)/2;
	createMap(&map, (x-1)/2,(y-1)/2);
	printMap(&map);
	gotoAndPrint(cur_a, " > Please watch ...");
	Person person;
	person.pos.x = 1;
	person.pos.y = 1;
	autoSolveMaze(&map, &person);
	gotoCursor(cur_a);
	while(1){
		key = hitkey();
			if (key == KBD_Q || key == KBD_ENTER || key == KBD_ESC)
				break;
	}
	eraseMap(&map);
	CLS;
}

void highScoreWindow(){
	Key key;
	CLS;
	drawFrame();
	Cursor cur = {SCRSIZE_W/2, SCRSIZE_H/2};
	gotoAndPrintCenter(cur, "This funtion is under developing, Sorry.");
	cur.y += 2;
	gotoAndPrintCenter(cur, "Press ENTER to quit.");
	cur.y += 2;
	gotoCursor(cur);
	while(1){
		key = hitkey();
			if (key == KBD_Q || key == KBD_ENTER || key == KBD_ESC)
				break;
	}

}

void helpWindow(){
	CLS;
	Key key;
	drawFrame();
	Cursor cur_a = {58,11};	// Define draw cursor a
	Cursor cur_b = {93,14};	// Define draw cursor b
	cur_a.x = 58; cur_a.y = 11;
	cur_b.x = 93; cur_b.y = 14;
	drawRectangle(cur_a, cur_b, '*');
	Cursor cur_op = {SCRSIZE_W/2,SCRSIZE_H/2-10};	// Define draw operation cursor 
	gotoAndPrintCenter(cur_op, "Maze Game");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "Version 1.2");
	cur_op.y += 8;
	gotoAndPrintCenter(cur_op, "This is a test version.");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "And there are many bugs.");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "If you find some please contact:");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "i@kmahyyg.xyz");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "Thanks for your playing.");
	cur_op.y += 2;
	gotoAndPrintCenter(cur_op, "Press ENTER to quit.");
	cur_op.y += 2;
	gotoCursor(cur_op);
	while(1){
		key = hitkey();
			if (key == KBD_Q || key == KBD_ENTER || key == KBD_ESC)
				break;
	}
}

void exitWindow(){
	CLS;
	exit(0);
}



