#include "./deque.h"

Deque_t *deque_initialise(
		size_t typeSize,
		void (*printData)(void *),
		void (*destroyData)(void *)
	) {
	Deque_t *deque = malloc(sizeof(Deque_t));
	if (deque == NULL)  { fprintf(stderr, "Malloc failed\n"); exit(1);}
	
	deque->typeSize = typeSize;
	deque->size = 0;
	deque->printData = printData;
	deque->destroyData = destroyData;
	deque->head = NULL;
	deque->tail = NULL;
	
	return deque;
}

Deque_t *deque_initialise_string_reference(void (*print)(void *)) {
	return deque_initialise(sizeof(const char *), print, NULL);
}
Deque_t *deque_initialise_string_value(void (*print)(void *), void (*destroy)(void *)) {
	return deque_initialise(sizeof(char *), print, destroy);
}

int deque_is_empty(Deque_t *deque) {
	if (deque == NULL) { fprintf(stderr, "Deque is null\n"); return 1; }
	return deque->size  == 0 ? 1 : 0;
}

int deque_size(Deque_t *deque) {
	if (deque == NULL) { fprintf(stderr, "Deque is null\n"); return 0; }
	return deque->size;
}

void deque_enqueue_front(Deque_t *deque, const void *data) {
	if(deque == NULL) { fprintf(stderr, "Deque is null\n"); return; }
	DequeNode_t *temp = malloc(sizeof(DequeNode_t));
	if (temp == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
	
	if (deque->typeSize > 0) { 
		temp->data = malloc(deque->typeSize);
		if (temp->data == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
		if (data != NULL) memcpy(temp->data, data, deque->typeSize);
	} else temp->data = NULL;
	
	temp->prev = NULL;
	temp->next = deque->head;
	if (deque->head == NULL) deque->tail = temp;
	else deque->head->prev = temp;
	deque->head = temp;
	deque->size++;
}

void deque_enqueue_front_string_refrence(Deque_t *deque, const char *data) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(const char *) == (deque)->typeSize);
	
	
	deque_enqueue_front(deque, &data);
}

void deque_enqueue_front_string_value(Deque_t *deque, const char *data) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(char *) == (deque)->typeSize);
	
	size_t size = strlen(data) + 1;
	char *copy = malloc(size);
	if (copy == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
	
	memcpy(copy, data, size);
	deque_enqueue_front(deque, &copy);
}
void deque_enqueue_back(Deque_t *deque, const void *data) {
	if(deque == NULL) { fprintf(stderr, "Deque is null\n"); return; }
	DequeNode_t *temp = malloc(sizeof(DequeNode_t));
	if (temp == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
	
	if (deque->typeSize > 0) { 
		temp->data = malloc(deque->typeSize);
		if (temp->data == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
		if (data != NULL) memcpy(temp->data, data, deque->typeSize);
	} else temp->data = NULL;
	
	temp->prev = deque->tail;
	temp->next = NULL;
	if (deque->head == NULL) deque->head = temp;
	else deque->tail->next = temp;
	deque->tail = temp;
	deque->size++;
}

void deque_enqueue_back_string_refrence(Deque_t *deque, const char *data) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(const char *) == (deque)->typeSize);
	
	
	deque_enqueue_back(deque, &data);
}

void deque_enqueue_back_string_value(Deque_t *deque, const char *data) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(char *) == (deque)->typeSize);
	
	size_t size = strlen(data) + 1;
	char *copy = malloc(size);
	if (copy == NULL) { fprintf(stderr, "Malloc failed\n"); exit(1); }
	
	memcpy(copy, data, size);
	deque_enqueue_back(deque, &copy);
}

void deque_deque_front(Deque_t *deque) {	
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (deque->head == NULL){ fprintf(stderr, "Deque underflow\n"); return; }
		
	DequeNode_t *temp = deque->head;
	deque->head = temp->next;
	if (deque->head == NULL) deque->tail = NULL;
	else deque->head->prev = NULL;
	
	if (deque->destroyData != NULL) deque->destroyData(temp->data);
	free(temp->data);
	free(temp);
	deque->size--;
}
void deque_deque_back(Deque_t *deque) {	
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	if (deque->head == NULL){ fprintf(stderr, "Deque underflow\n"); return; }
		
	DequeNode_t *temp = deque->tail;
	deque->tail = temp->prev;
	if (deque->tail == NULL) deque->head = NULL;
	else deque->tail->next = NULL;
	 
	
	if (deque->destroyData != NULL) deque->destroyData(temp->data);
	free(temp->data);
	free(temp);
	deque->size--;
}

void *deque_peek_front(Deque_t *deque) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return NULL; }
	if (deque->head == NULL) return NULL;
	return deque->head->data;

}
void *deque_peek_back(Deque_t *deque) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return NULL; }
	if (deque->tail == NULL) return NULL;
	return deque->tail->data;
}

void deque_free(Deque_t *deque) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	DequeNode_t *current;
	while ((current = deque->head) != NULL) {
		deque->head = deque->head->next;
		if (deque->destroyData != NULL) deque->destroyData(current->data);
		free(current->data);
		free(current);
	}
	
	free(deque);
}

void deque_print_deque(Deque_t *deque) {
	if (deque == NULL){ fprintf(stderr, "Deque is null\n"); return; }
	
	DequeNode_t *current = deque->head;
	printf("\nDeque: ");
	while (current != NULL) {
		deque->printData(current->data);
		current = current->next;
	}
}
