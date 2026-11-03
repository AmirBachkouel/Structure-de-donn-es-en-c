#include "./queue.h"

Queue_t *queue_initialise(
		size_t typeSize,
		void (*printData)(void *),
		void (*destroyData)(void *)
	) {
	Queue_t *queue = malloc(sizeof(Queue_t));
	if (queue == NULL)  { fprintf(stderr, "malloc failed\n"); exit(1);}
	
	queue->typeSize = typeSize;
	queue->size = 0;
	queue->printData = printData;
	queue->destroyData = destroyData;
	queue->head = NULL;
	queue->tail = NULL;
	
	return queue;
}

Queue_t *queue_initialise_string_reference(void (*print)(void *)) {
	return queue_initialise(sizeof(const char *), print, NULL);
}
Queue_t *queue_initialise_string_value(void (*print)(void *), void (*destroy)(void *)) {
	return queue_initialise(sizeof(char *), print, destroy);
}

int queue_is_empty(Queue_t *queue) {
	if (queue == NULL) { fprintf(stderr, "queue is null\n"); return 1; }
	return queue->size  == 0 ? 1 : 0;
}

int queue_size(Queue_t *queue) {
	if (queue == NULL) { fprintf(stderr, "queue is null\n"); return 0; }
	return queue->size;
}

void queue_enqueue(Queue_t *queue, const void *data) {
	if(queue == NULL) { fprintf(stderr, "queue is null\n"); return; }
	QueueNode_t *temp = malloc(sizeof(QueueNode_t));
	if (temp == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
	
	if (queue->typeSize > 0) { 
		temp->data = malloc(queue->typeSize);
		if (temp->data == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
		if (data != NULL) memcpy(temp->data, data, queue->typeSize);
	} else temp->data = NULL;
	
	temp->next = NULL;
	if (queue->head == NULL) queue->head = temp;
	else queue->tail->next = temp;
	queue->tail = temp;
	queue->size++;
}

void queue_enqueue_string_refrence(Queue_t *queue, const char *data) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(const char *) == (queue)->typeSize);
	
	
	queue_enqueue(queue, &data);
}

void queue_enqueue_string_value(Queue_t *queue, const char *data) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(char *) == (queue)->typeSize);
	
	size_t size = strlen(data) + 1;
	char *copy = malloc(size);
	if (copy == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
	
	memcpy(copy, data, size);
	queue_enqueue(queue, &copy);
}

void queue_dequeue(Queue_t *queue) {	
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return; }
	if (queue->head == NULL){ fprintf(stderr, "Queue underflow\n"); return; }
		
	QueueNode_t *temp = queue->head;
	queue->head = temp->next;
	if (queue->head == NULL) queue->tail = NULL;
	
	if (queue->destroyData != NULL) queue->destroyData(temp->data);
	free(temp->data);
	free(temp);
	queue->size--;
}

void *queue_peek_front(Queue_t *queue) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return NULL; }
	if (queue->head == NULL) return NULL;
	return queue->head->data;

}
void *queue_peek_back(Queue_t *queue) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return NULL; }
	if (queue->tail == NULL) return NULL;
	return queue->tail->data;
}

void queue_free(Queue_t *queue) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return; }
	QueueNode_t *current;
	while ((current = queue->head) != NULL) {
		queue->head = queue->head->next;
		if (queue->destroyData != NULL) queue->destroyData(current->data);
		free(current->data);
		free(current);
	}
	
	free(queue);
}

void queue_print_queue(Queue_t *queue) {
	if (queue == NULL){ fprintf(stderr, "Queue is null\n"); return; }
	
	QueueNode_t *current = queue->head;
	while (current != NULL) {
		queue->printData(current->data);
		current = current->next;
	}
}
