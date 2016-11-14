/* stack.h */

#ifndef STACK_H
#define STACK_H

#include "basic.h"

Status InitStack(stack_ptr S);
Status Push(stack_ptr S,ElemType *e);
Status StackEmpty(stack_ptr S);
Status Pop(stack_ptr S, ElemType *e);
Status GetTop(stack_ptr S, ElemType *e);
int stackLength(Stack *S);

// Add a commit

#endif
