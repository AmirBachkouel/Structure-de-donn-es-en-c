#include "./stack.h"

Stack_t *stack_initialise(
		size_t typeSize,
		void (*printData)(void *),
		void (*destroyData)(void *)
	) {
	Stack_t *stack = malloc(sizeof(Stack_t));
	if (stack == NULL)  { fprintf(stderr, "malloc failed\n"); exit(1);}
	
	stack->typeSize = typeSize;
	stack->size = 0;
	stack->printData = printData;
	stack->destroyData = destroyData;
	stack->top = NULL;
	
	return stack;
}

Stack_t *stack_initialise_string_reference(void (*print)(void *)) {
	return stack_initialise(sizeof(const char *), print, NULL);
}
Stack_t *stack_initialise_string_value(void (*print)(void *), void (*destroy)(void *)) {
	return stack_initialise(sizeof(char *), print, destroy);
}

int stack_is_empty(Stack_t *stack) {
	if (stack == NULL) { fprintf(stderr, "stack is null\n"); return 1; }
	return stack->top  == NULL ? 1 : 0;
}

int stack_size(Stack_t *stack) {
	if (stack == NULL) { fprintf(stderr, "stack is null\n"); return 0; }
	return stack->size;
}

void stack_push(Stack_t *stack, const void *data) {
	if(stack == NULL) { fprintf(stderr, "stack is null\n"); return; }
	StackNode_t *temp = malloc(sizeof(StackNode_t));
	if (temp == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
	
	if (stack->typeSize > 0) { 
		temp->data = malloc(stack->typeSize);
		if (temp->data == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
		if (data != NULL) memcpy(temp->data, data, stack->typeSize);
	} else temp->data = NULL;
	
	temp->next = stack->top;
	stack->top = temp;
	stack->size++;
}

void stack_push_string_refrence(Stack_t *stack, const char *data) {
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(const char *) == (stack)->typeSize);
	
	
	stack_push(stack, &data);
}

void stack_push_string_value(Stack_t *stack, const char *data) {
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return; }
	if (data == NULL){ fprintf(stderr, "String is null\n"); return; }
	assert(sizeof(char *) == (stack)->typeSize);
	
	size_t size = strlen(data) + 1;
	char *copy = malloc(size);
	if (copy == NULL) { fprintf(stderr, "malloc failed\n"); exit(1); }
	
	memcpy(copy, data, size);
	stack_push(stack, &copy);
}

void stack_pop(Stack_t *stack) {	
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return; }
	if (stack->top == NULL){ fprintf(stderr, "stack underflow\n"); return; }
		
	StackNode_t *temp = stack->top;
	stack->top = stack->top->next;
	if (stack->destroyData != NULL) stack->destroyData(temp->data);
	free(temp->data);
	free(temp);
	
	stack->size--;
}

void *stack_peek(Stack_t *stack) {
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return NULL; }
	if (stack->top == NULL) return NULL;
	return stack->top->data;
}

void stack_free(Stack_t *stack) {
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return; }
	StackNode_t *current;
	while ((current = stack->top) != NULL) {
		stack->top = stack->top->next;
		if (stack->destroyData != NULL) stack->destroyData(current->data);
		free(current->data);
		free(current);
	}
	
	free(stack);
}

void stack_print_stack(Stack_t *stack) {
	if (stack == NULL){ fprintf(stderr, "Stack is null\n"); return; }
	
	StackNode_t *current = stack->top;
	while (current != NULL) {
		stack->printData(current->data);
		current = current->next;
	}
}