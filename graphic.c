/* graphic.c */

#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gotoCursor(Cursor cur){
	printf("%c[%d;%df",0x1B, cur.y + 1, cur.x + 1);
}

void gotoAndPrint(Cursor cur, char *src){
	gotoCursor(cur);
	printf("%s",src);
	gotoCursor(cur);
}

void gotoAndPrintCenter(Cursor cur, char *src){
	int len = strlen(src);
	cur.x -= len/2;
	gotoCursor(cur);
	printf("%s",src);
	cur.x += len ;
	gotoCursor(cur);
}

void gotoAndPrintOption(Cursor cur, char *src){
	gotoCursor(cur);
	printf("%s",src);
	cur.x -= 2 ;
	gotoCursor(cur);
}


void gotoAndDrawByMap(Cursor cur, Map *map){
	
	
}

void drawRectangle(Cursor start, Cursor end, char ch){
	int i, y = start.y;
	gotoCursor(start);
	for (i = start.x; i <= end.x; i++)
		printf("%c",ch);
	for (i = start.y; i < end.y; i++){
		start.y++;
		gotoCursor(start);
		printf("%c",ch);
	}
	end.y = y;
	start.y++;
	for (i = y; i < start.y; i++){
		end.y++;
		gotoCursor(end);
		printf("%c",ch);
	}
	gotoCursor(start);
	for (i = start.x; i <= end.x; i++)
		printf("%c",ch);
}

void drawFrame(){
	Cursor start = {0,0};
	Cursor end = {MAX_SCR_W,MAX_SCR_H};
	int i, y = start.y;
	gotoCursor(start);
	for (i = start.x; i < end.x; i++)
		printf("%c",'-');
	printf("+");
	gotoAndPrint(start,"+");
	for (i = start.y; i < end.y; i++){
		start.y++;
		gotoCursor(start);
		printf("%c",'|');
	}
	end.y = y;
	start.y++;
	for (i = y; i < start.y; i++){
		end.y++;
		gotoCursor(end);
		printf("%c",'|');
	}
	gotoCursor(start);
	for (i = start.x; i < end.x; i++)
		printf("%c",'-');
	printf("+");
	gotoAndPrint(start,"+");
}

void printMap(Map *map){
	int i, j;
	Cursor cur;
	extern Cursor start_cur;
	for(i=0;i < map->height;i++){
		for(j=0;j < map->width;j++){
			cur.x = j + start_cur.x;
			cur.y = i + start_cur.y;
			if (map->data[j][i] == SPACE)
				gotoAndPrint(cur, " ");
			else if(map->data[j][i] == WALKED)
				gotoAndPrint(cur, " ");
			else if(map->data[j][i] == BLOCKED)
				gotoAndPrint(cur, " ");
			else if(map->data[j][i] == EXIT)
				gotoAndPrint(cur, "*");
			else
				gotoAndPrint(cur, "#");
		}
			
	}
}

void printPerson(Person *person){
	extern Cursor start_cur;
	Cursor cur = {person->pos.x + start_cur.x, person->pos.y + start_cur.y};
	gotoCursor(cur);
	printf("0");
	gotoCursor(cur);
}

void erasePerson(Person *person){
	extern Cursor start_cur;
	Cursor cur = {person->pos.x + start_cur.x, person->pos.y + start_cur.y};
	gotoCursor(cur);
	printf(" ");
	gotoCursor(cur);
}

void movePerson(Person *person, int key){
	if (key == 65)
		person->pos.y--;	// UP
	else if(key == 66)
		person->pos.y++;	// DOWN
	else if(key == 68)
		person->pos.x--;	// LEFT
	else if(key == 67)
		person->pos.x++;	// RIGHT
	gotoCursor(person->pos);
	printf("0");
	gotoCursor(person->pos);
}

int isMovable(Map *map, Person *person, Key key){
	if (key == KBD_ARR_UP)
		return person->pos.y == 0 ? 0 : map->data[person->pos.x][person->pos.y - 1] == WALL ? 0 : 1;
	else if(key == KBD_ARR_DOWN)
		return person->pos.y == MAX_SCR_H ? 0 : map->data[person->pos.x][person->pos.y + 1] == WALL ? 0 : 1;
	else if(key == KBD_ARR_LEFT)
		return person->pos.x == 0 ? 0 : map->data[person->pos.x - 1][person->pos.y] == WALL ? 0 : 1;
	else if(key == KBD_ARR_RIGHT)
		return person->pos.x == MAX_SCR_W ? 0 : map->data[person->pos.x + 1][person->pos.y] == WALL ? 0 : 1;
	else
		return 0;
}





