/* stack.c */

#include "stack.h"
#include <stdlib.h>
Status InitStack(Stack *S){
	S->base=(ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));
	if(!S->base) exit(OVERFLOW);
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return OK;
}

Status destroyStack(Stack *S){
	free(S->base);
	S->base = S->top = NULL;
	S->stacksize = 0;
}

Status Push(stack_ptr S,ElemType *e){
	if(S->top-S->base>=S->stacksize){
		S->base=(ElemType *)realloc(S->base,(S->stacksize+INCREMENT)*sizeof(ElemType));
		if(!S->base) exit(OVERFLOW);
		S->top=S->base+S->stacksize;
		S->stacksize+=INCREMENT;
	}
	*(S->top++)=*e;
	return OK;
}

Status StackEmpty(Stack *S){
	if(S->base==S->top) return 1;
	else return 0;
}

Status Pop(Stack *S, ElemType *e){
	if(StackEmpty(S)) exit(ERROR);
	*e = *(--S->top);
	return OK;
}

Status GetTop(Stack *S, ElemType *e){
	if(StackEmpty(S)) exit(ERROR);
	*e = *(S->top-1);
	return OK;
}

int stackLength(Stack *S){
	return S->top - S->base;
}
