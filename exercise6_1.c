#include <stdio.h>
#include <stdlib.h>

#ifdef COMPILE_6_1

#define QUEUE_MAX 10

typedef int element;


typedef struct queue_t
{
	element array[QUEUE_MAX];

	int front, rear;
} Queue;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}


//void queue_create();
void init(Queue* queue)
{
	queue->front = queue->rear = 0;
}

int is_empty(Queue* queue)
{
	return queue->front == queue->rear;
}

int is_full(Queue* queue)
{
	return (queue->rear + 1) % QUEUE_MAX == queue->front;
}

void enqueue(Queue* queue, element data)
{
	if (is_full(queue))
		return;

	queue->rear = (queue->rear + 1) % QUEUE_MAX;
	queue->array[queue->rear] = data;
}
element dequeue(Queue* queue)
{
	if (is_empty(queue))
		return;

	queue->front = (queue->front + 1) % QUEUE_MAX;
	return queue->array[queue->front];
}


int main()
{
	Queue q;

	int i;

	init(&q);



	for (i = 0; i < QUEUE_MAX + 4; ++i)
		enqueue(&q, i);

	while (!is_empty(&q))
	{
		printf("dequeue : %d\n", dequeue(&q));
	}

	return 0;
}


#endif