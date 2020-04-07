#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack stack_t;

/*stack funcs*/
stack_t *StackCreate(size_t capacity);
void StackDestroy(stack_t *s_ptr);
void StackPush(stack_t *s_ptr, void *element);
void StackPop(stack_t *s_ptr);
void *StackPeek(stack_t *s_ptr);
size_t StackSize(stack_t *s_ptr);
int StackIsEmpty(stack_t *s_ptr);
size_t StackCapacity(stack_t *s_ptr);

#endif

