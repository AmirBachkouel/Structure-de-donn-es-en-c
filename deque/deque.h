#ifndef DEQUE_H_
#define DEQUE_H_

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

typedef struct DequeNode {
    void* data;
    struct DequeNode *next;
    struct DequeNode *prev;
} DequeNode_t;

typedef struct Deque {
	size_t size;
	size_t typeSize;
	void (*printData)(void *);
	void (*destroyData)(void *);
	DequeNode_t *head;
	DequeNode_t *tail;
} Deque_t;

#define deque_enqueue_front_literal(deque, type, literal) \
	do { \
		assert(sizeof(type) == (deque)->typeSize); \
		deque_enqueue_front((deque), &(type){(literal)}); \
	} while(0)

#define deque_enqueue_front_struct(deque, ...) \
	do { \
		assert(sizeof(*(__VA_ARGS__)) == (deque)->typeSize); \
		deque_enqueue_front((deque), (__VA_ARGS__)); \
	} while(0)
#define deque_enqueue_back_literal(deque, type, literal) \
	do { \
		assert(sizeof(type) == (deque)->typeSize); \
		deque_enqueue_back((deque), &(type){(literal)}); \
	} while(0)

#define deque_enqueue_back_struct(deque, ...) \
	do { \
		assert(sizeof(*(__VA_ARGS__)) == (deque)->typeSize); \
		deque_enqueue_back((deque), (__VA_ARGS__)); \
	} while(0)


Deque_t *deque_initialise(
	size_t typeSize,
	void (*printData)(void *),
	void (*destroyData)(void *)
);
Deque_t *deque_initialise_string_reference(void (*print)(void *));
Deque_t *deque_initialise_string_value(void (*print)(void *), void (*destroy)(void *));

int deque_is_empty(Deque_t *deque);
int deque_size(Deque_t *deque);

void deque_enqueue_front(Deque_t *deque, const void *data);
void deque_enqueue_front_string_value(Deque_t *deque, const char *data);
void deque_enqueue_front_string_refrence(Deque_t *deque, const char *data);

void deque_enqueue_back(Deque_t *deque, const void *data);
void deque_enqueue_back_string_value(Deque_t *deque, const char *data);
void deque_enqueue_back_string_refrence(Deque_t *deque, const char *data);

void deque_deque_front(Deque_t *deque);
void deque_deque_back(Deque_t *deque);

void *deque_peek_front(Deque_t *deque);
void *deque_peek_back(Deque_t *deque);

void deque_free(Deque_t *deque);
void deque_print_deque(Deque_t *deque);

#endif /* DEQUE_H_ */
