#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

typedef struct Node {
    void* data;
    struct Node *next;
} StackNode_t;

typedef struct Stack {
	size_t size;
	size_t typeSize;
	void (*printData)(void *);
	void (*destroyData)(void *);
	StackNode_t *top;
} Stack_t;

#define stack_push_literal(stack, type, literal) \
	do { \
		assert(sizeof(type) == (stack)->typeSize); \
		stack_push((stack), &(type){(literal)}); \
	} while(0)

#define stack_push_struct(stack, ...) \
	do { \
		assert(sizeof(*(__VA_ARGS__)) == (stack)->typeSize); \
		stack_push((stack), (__VA_ARGS__)); \
	} while(0)

Stack_t *stack_initialise(
	size_t typeSize,
	void (*printData)(void *),
	void (*destroyData)(void *)
);
Stack_t *stack_initialise_string_reference(void (*print)(void *));

Stack_t *stack_initialise_string_value(void (*print)(void *), void (*destroy)(void *));

int stack_is_empty(Stack_t *stack);

int stack_size(Stack_t *stack);

void stack_push(Stack_t *stack, const void *data);

void stack_push_string_value(Stack_t *stack, const char *data);

void stack_push_string_refrence(Stack_t *stack, const char *data);

void stack_pop(Stack_t *stack);

void *stack_peek(Stack_t *stack);

void stack_free(Stack_t *stack);

void stack_print_stack(Stack_t *stack);

#endif /* STACK_H_ */