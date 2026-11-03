#include "queue.h"

static void print_int(void *p) { printf("%d ", *(int *)p); }

int main(void)  {
	Queue_t *q = queue_initialise(sizeof(int), print_int, NULL);

	queue_enqueue_literal(q, int, 1);
	queue_enqueue_literal(q, int, 2);
	queue_enqueue_literal(q, int, 3);
	queue_print_queue(q);

	printf("\nfront: %d \n", *(int*)queue_peek_front(q));
	printf("\nrear: %d \n", *(int*)queue_peek_back(q));
	queue_dequeue(q);
	queue_dequeue(q);
	queue_dequeue(q);
	queue_dequeue(q);

	queue_enqueue_literal(q, int, 4);
	queue_print_queue(q);
	
	queue_free(q);
	return 0;
}
