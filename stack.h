
#ifndef _STACK_H_
#define _STACK_H_

#include "deque.h"

typedef struct Stack Stack;

Stack *stack_construct();
void stack_push(Stack *stack, void *data);
int stack_empty(Stack *stack);
void *stack_pop(Stack *stack);
void stack_destroy(Stack *stack);

#endif