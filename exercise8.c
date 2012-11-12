#include <stdio.h>
#include <stdlib.h>

#ifdef EXER8

#define TRUE 1
#define FALSE 0
#define MAX_ELEMENT 200

#define ARRIVAL 1
#define ORDER 2
#define LEAVE 3

typedef struct{
	int key;
	int type;
	int number;
}element;

typedef struct{
	element heap[MAX_ELEMENT];
	int size;
}Heap;

Heap heap1;
int free_seats = 10;
double profit = 0;

void insert_max_heap(Heap* heap, element item)
{
	int i;
	i = ++(heap->size);

	while ((i != 1) && (item.key > heap->heap[i/2].key))
	{
		heap->heap[i] = heap->heap[i / 2];
		i /= 2;
	}

	heap->heap[i] = item;
}

void init(Heap* h)
{
	h->size = 0;
}

int is_empty(Heap* h)
{
	if (h->size == 0)
		return TRUE;
	else
		return FALSE;
}

void insert_min_heap(Heap* h, element item)
{
	int i;
	i = ++(h->size);
	while ((i != 1) && (item.key < h->heap[i/2].key))
	{
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(Heap* h)
{
	int parent, child;

	element item, temp;

	item = h->heap[1];
	temp = h->heap[h->size];

	h->size--;

	parent = 1;
	child  = 2;

	while (child <= h->size)
	{
		if ((child < h->size) &&
			(h->heap[child].key) > h->heap[child+1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int random(int n)
{
	return (int)(n*rand()/(double)RAND_MAX);
}



int is_seat_available(int number)
{
	printf("%d 명의 고객 도착 \n", number);

	if (free_seats >= number)
	{
		free_seats -= number;
		return TRUE;
	}
	else
	{
		puts("자리가 없어서 떠남");
		return FALSE;
	}
}

void order(int scoops)
{
	printf("아이스크림 %d개 주문 받음\n", scoops);
	profit += 0.35 * scoops;
}

void leave(int number)
{
	printf("%d명이 매장을 떠남\n", number);

	free_seats += number;
}

void process_event(Heap* heap, element e)
{
	int i = 0;
	element new_event;

	printf("현재 시간=%d\n", e.key);

	switch(e.type)
	{
	case ARRIVAL:
		if (is_seat_available(e.number))
		{
			new_event.type = ORDER;
			new_event.key = e.key + 1 + random(4);
			new_event.number = e.number;
			insert_min_heap(heap, new_event);
		}
		break;

	case ORDER:
		//
		for (i = 0; i < e.number; ++i)
		{
			order(1 + random(3));
		}

		// leave
		new_event.type = LEAVE;
		new_event.key = e.key + 1 + random(10);
		new_event.number = e.number;
		insert_min_heap(heap, new_event);
		break;

	case LEAVE:
		//if customer leaved,
		leave(e.number);
		break;
	}
}

int main()
{
	element event;
	Heap heap;

	unsigned int t = 0;

	init(&heap);

	while (t < 5)
	{
		t += random(6);
		event.type  = ARRIVAL;
		event.key = t;

		event.number = 1 + random(4);
		insert_min_heap(&heap, event);
	}

	while (!is_empty(&heap))
	{
		event = delete_min_heap(&heap);
		process_event(&heap, event);
	}

	printf("전체 순이익은 %f입니다\n", profit);
}


#endif