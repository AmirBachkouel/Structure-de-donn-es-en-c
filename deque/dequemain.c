#include "deque.h"

static void print_int(void *p) { printf("%d ", *(int *)p); }

int main(void)  {
	Deque_t *d = deque_initialise(sizeof(int), print_int, NULL);

	deque_enqueue_back_literal(d, int, 2);
	deque_enqueue_back_literal(d, int, 3);
	deque_enqueue_front_literal(d, int, 1);
	deque_enqueue_front_literal(d, int, 0);
	deque_print_deque(d);

	printf("\nfront %d, back %d\n",
		*(int *)deque_peek_front(d), *(int *)deque_peek_back(d));

	deque_deque_front(d);
	deque_deque_back(d);
	deque_print_deque(d);
	
	deque_deque_back(d);
	deque_deque_back(d);
	deque_deque_back(d);

	deque_enqueue_front_literal(d, int, 7);
	deque_enqueue_back_literal(d, int, 8);
	deque_print_deque(d);

	deque_free(d);	
	return 0;
}
