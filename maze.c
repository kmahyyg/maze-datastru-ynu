/* maze.c */

#include "maze.h"
#include "stack.h"
#include "graphic.h"
#include "keyboard.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int sr(Map *map, int x, int y){
	static int d[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
	int zx=x*2,zy=y*2,nx,tn=rand()%2? 1:3,i;
	map->data[zx][zy]=1;
	for(i=0,nx=rand()%4;i<4;i++,nx=(nx+tn)%4)
		if(map->data[zx+2*d[nx][0]][zy+2*d[nx][1]]==0)
			map->data[zx+d[nx][0]][zy+d[nx][1]]=1, sr(map, x+d[nx][0],y+d[nx][1]);
	return 0;
}


Map *createMap(Map *map, int x, int y){
	int i,j;
	Map *src = (Map *)malloc(sizeof(Map));
	for (i=0,j=2*y+2;i<=2*x+2;i++)
		src->data[i][0]=1,src->data[i][j]=1;
	for(i=0,j=2*x+2;i<=2*y+2;i++)
		src->data[0][i]=1,src->data[j][i]=1;
	src->data[2][1]=0;src->data[2*x][2*y+1]=1;
	srand((unsigned)(time(NULL)));
	sr(src, rand()%x+1,rand()%y+1);

	map->height = 2*x+1;
	map->width = 2*y+1;
	for(j=0; j<=2*y; j++)
		for (i=0; i<=2*x; i++)
			if(src->data[i+1][j+1]==0)
				map->data[j][i] = WALL;
			else
				map->data[j][i] = SPACE;
	for(j=0; j <= 2*x+2; j++)
		for (i=0; i <= 2*y+2; i++)
			src->data[j][i] = 0;
	free(src);
	src = NULL;
	map->data[2*y][2*x-1] = EXIT;
	return map;
}

void eraseMap(Map *map){
	int i, j;
	for(j=0; j < MAX_HEIGHT; j++)
		for (i=0; i < MAX_WIDTH; i++)
			map->data[j][i] = SPACE;
	map->height = map->width = 0;
}

int isReachExit(Map *map, Person *person){
	return map->data[person->pos.x][person->pos.y] == EXIT ? 1 : 0;
}


char *str_direc[5]={"DOWN","RIGHT","UP","LEFT","NONE"};
Status Pass(Person *curpos,Map *maze){
	int x = curpos->pos.x, y = curpos->pos.y;
	int isReachable = 0;
	switch (curpos->direc){
		case UP:
			if(maze->data[x-1][y] != WALL && maze->data[x-1][y] != BLOCKED && maze->data[x-1][y] != WALKED)
				isReachable = 1;
			break;
		case DOWN:
			if(maze->data[x+1][y] != WALL && maze->data[x+1][y] != BLOCKED && maze->data[x+1][y] != WALKED)
				isReachable = 1;
			break;
		case LEFT:
			if(maze->data[x][y-1] != WALL && maze->data[x][y-1] != BLOCKED && maze->data[x][y-1] != WALKED)
				isReachable = 1;
			break;
		case RIGHT:
			if(maze->data[x][y+1] != WALL && maze->data[x][y+1] != BLOCKED && maze->data[x][y+1] != WALKED)
				isReachable = 1;
			break;
		default:
				;
	}
	return isReachable;
}

Status Footprint(Person *curpos,Map *maze){
	maze->data[curpos->pos.x][curpos->pos.y] = WALKED;
	return OK;
}

Person *Nextpos(Person *curpos){
	switch(curpos->direc){
		case RIGHT:curpos->pos.y+=1; break;
		case LEFT:curpos->pos.y-=1; break;
		case UP:curpos->pos.x-=1;break;
		case DOWN:curpos->pos.x+=1;break;
		default:;
	}
	return curpos;
}

Status Markprint(Person *curpos,Map *maze){
	maze->data[curpos->pos.x][curpos->pos.y] = BLOCKED;
	return OK;
}

Status autoSolveMaze(Map *maze,Person *curpos){
	// Initialize
	Stack S;
	extern Cursor start_cur;
	Cursor cur;
	InitStack(&S);
	printPerson(curpos);
	curpos->direc = DOWN;
	do{
		if(Pass(curpos,maze)){
			Footprint(curpos,maze);
			cur.x = curpos->pos.x + start_cur.x;
			cur.y = curpos->pos.y + start_cur.y;
			gotoAndPrint(cur,"+");
			Push(&S, curpos);
			Nextpos(curpos);
			cur.x = curpos->pos.x + start_cur.x;
			cur.y = curpos->pos.y + start_cur.y;
			gotoAndPrint(cur,"0");
			if (isReachExit(maze, curpos)){
				break;
			}
			else
				curpos->direc = DOWN;
		}else{
			if (curpos->direc == LEFT){
				while (curpos->direc == LEFT && !StackEmpty(&S)){
					cur.x = curpos->pos.x + start_cur.x;
					cur.y = curpos->pos.y + start_cur.y;
					gotoAndPrint(cur,"X");
					Markprint(curpos, maze);
					Pop(&S, curpos);
				}
			}else{
				curpos->direc++;
			}
		}
		hitkey();
		cur.x = curpos->pos.x + start_cur.x;
		cur.y = curpos->pos.y + start_cur.y;
		gotoCursor(cur);
	}while(!(curpos->pos.x == 1 && curpos->pos.y == 0 && curpos->direc == LEFT));
	// destroy stack
	return OK;          
}

Person *solveMaze(Map *maze,Person *curpos){
	// Initialize
	int i = 0, isReachable = 0;
	Stack S;
	InitStack(&S);
	curpos->direc = DOWN;
	do{
		if(Pass(curpos,maze)){
			Footprint(curpos,maze);
			Push(&S, curpos);
			Nextpos(curpos);
			if (isReachExit(maze, curpos)){
				isReachable = 1;
				break;
			}
			else
				curpos->direc = DOWN;
		}else{
			if (curpos->direc == LEFT){
				while (curpos->direc == LEFT && !StackEmpty(&S)){
					Markprint(curpos, maze);
					Pop(&S, curpos);
				}
			}else{
				curpos->direc++;
			}
		}
	}while(!(curpos->pos.x == 1 && curpos->pos.y == 0 && curpos->direc == LEFT));
	Person *result = (Person *)malloc(stackLength(&S)*sizeof(Person));
	for (i=0; i < stackLength(&S); i++)
		result[i] = S.base[i];
	return result;
}
