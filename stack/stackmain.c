#include "stack.c"


typedef struct Point {
	int x;
	int y;
} Point_t;

static void print_int(void *p)   { printf("%d ", *(int *)p); }
static void print_point(void *p) { Point_t *pt = p; printf("(%d,%d) ", (*pt).x, (*pt).y); }
static void print_str(void *p)   { printf("%s ", *(char **)p); }
static void destroy_str(void *p) { free(*(char **)p); }


int main() {
	/*Stack_t *stack = stack_initialise(sizeof(int), print_int);
	stack_push_literal(stack, int, 10);
	stack_push_literal(stack, int, 20);
	stack_push_literal(stack, int, 30);
	stack_push_literal(stack, int, 40);
	stack_push_literal(stack, int, 50);
	
    printf("Stack: ");
	stack_print_stack(stack);
    
	stack_pop(stack);
    stack_pop(stack);
    printf("\nStack: ");
	stack_print_stack(stack);
	stack_free(stack);
	
	stack = stack_initialise(sizeof(Point_t), print_point, NULL);
	Point_t point = {2, 1};
	stack_push_struct(stack, &point);
	stack_push_struct(stack, &(Point_t){.x = 1, .y = 2});
	stack_push_struct(stack, &(Point_t){5, 9});
	printf("\nStack: ");
	stack_print_stack(stack);
	stack_free(stack);
	
	stack = stack_initialise(sizeof(const char *), print_str, NULL);*/
	
	/* A stack of ints */
    Stack_t *ints = stack_initialise(sizeof(int), print_int, NULL);
    stack_push_literal(ints, int, 10);
    stack_push_literal(ints, int, 20);
    stack_print_stack(ints);                 /* 20 10 */
    int top = *(int *)stack_peek(ints);      /* read the top... */
    stack_pop(ints);                         /* ...then remove it */
    stack_free(ints);

    /* A stack of structs */
    Stack_t *points = stack_initialise(sizeof(Point_t), print_point, NULL);
    Point_t p = {2, 1};
    stack_push_struct(points, &p);
    stack_push_struct(points, &(Point_t){.x = 5, .y = 9});
    stack_print_stack(points);               /* (5,9) (2,1) */
    stack_free(points);

    /* A stack of owned strings */
    Stack_t *strs = stack_initialise_string_value(print_str, destroy_str);
    stack_push_string_value(strs, "hello");
    stack_push_string_value(strs, "a much longer string");
    stack_print_stack(strs);
    stack_free(strs);

    (void)top;
	
	return 0;
}
