#ifndef __STACK_H__
#define __STACK_H__
#include <stddef.h>

typedef struct stack stack_t;

stack_t *StackCreate(size_t capacity);

void StackDestroy(stack_t *s_ptr);

void StackPop(stack_t *s_ptr);

void StackPush(stack_t *s_ptr, void *element);

void *StackPeek(stack_t *s_ptr);

size_t StackSize(stack_t *s_ptr);

int StackIsEmpty(stack_t *s_ptr);

size_t StackCapacity(stack_t *s_ptr);

#endif

