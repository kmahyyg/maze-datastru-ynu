/* maze.h */

#ifndef MAZE_H
#define MAZE_H

#include "basic.h"

/* Functions */
Map *createMap(Map*map, int h, int w);
void eraseMap(Map *map);
int isReachExit(Map *map, Person *person);
Status Pass(Person *curpos,Map *maze);
Status Footprint(Person *curpos,Map *maze);
Status Markprint(Person *curpos,Map *maze);
Person *Nextpos(Person *curpos);
Person *solveMaze(Map *maze,Person *curpos);
Status autoSolveMaze(Map *maze,Person *curpos);

#endif