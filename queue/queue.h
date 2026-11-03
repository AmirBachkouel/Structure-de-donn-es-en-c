#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdio.h>

typedef struct QueueNode {
    void* data;
    struct Node *next;
} QueueNode_t;

typedef struct Queue {
	size_t size;
	size_t typeSize;
	void (*printData)(void *);
	void (*destroyData)(void *);
	QueueNode_t *head;
	QueueNode_t *tail;
} Queue_t;

#define queue_enqueue_literal(queue, type, literal) \
	do { \
		assert(sizeof(type) == (queue)->typeSize); \
		queue_enqueue((queue), &(type){(literal)}); \
	} while(0)

#define queue_enqueue_struct(queue, ...) \
	do { \
		assert(sizeof(*(__VA_ARGS__)) == (queue)->typeSize); \
		queue_enqueue((queue), (__VA_ARGS__)); \
	} while(0)

Queue_t *queue_initialise(
	size_t typeSize,
	void (*printData)(void *),
	void (*destroyData)(void *)
);
Queue_t *queue_initialise_string_reference(void (*print)(void *));
Queue_t *queue_initialise_string_value(void (*print)(void *), void (*destroy)(void *));

int queue_is_empty(Queue_t *queue);
int queue_size(Queue_t *queue);

void queue_enqueue(Queue_t *queue, const void *data);
void queue_enqueue_string_value(Queue_t *queue, const char *data);
void queue_enqueue_string_refrence(Queue_t *queue, const char *data);

void queue_dequeue(Queue_t *queue);
void *queue_peek_front(Queue_t *queue);
void *queue_peek_back(Queue_t *queue);

void queue_free(Queue_t *queue);
void queue_print_queue(Queue_t *queue);

#endif /* QUEUE_H_ */
