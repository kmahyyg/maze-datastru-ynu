/* graphic.h */

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "basic.h"
#include "keyboard.h"

#define gotoAndDraw(x) gotoAndDrawByPoint(x)

void gotoCursor(Cursor cur);
void gotoAndPrint(Cursor cur, char *src);
void gotoAndPrintCenter(Cursor cur, char *src);
void gotoAndPrintOption(Cursor cur, char *src);
void gotoAndDrawByMap(Cursor cur, Map *map);
void drawRectangle(Cursor start, Cursor end, char ch);
void drawFrame();
void printMap(Map *map);
void printPerson(Person *person);
void erasePerson(Person *person);
void movePerson(Person *person, int key);
int isMovable(Map *map, Person *person, Key key);




#endif
