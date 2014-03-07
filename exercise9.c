#ifdef Exer9
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define SWAP(a, b) a ^= b ^= a ^= b
#define SWAP(a,b,t) ((t) = (a), (a) = (b), (b) = (t))

int partition(int list[], int left, int right)
{
	int pivot ,temp;
	int low, high;
	
	low = left;
	high = right + 1;

	pivot = list[left];

	do
	{
		do
			low++;
			while(low <= right && list[low] < pivot);

		do
			high--;
			while (high >= left && list[high] > pivot);

		if (low < high)
			SWAP(list[low], list[high],temp);

	}
	while(low < high);

	SWAP(list[left], list[high], temp);

	return high;
}

void quicksort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quicksort(list, left, q - 1);
		quicksort(list, q + 1, right);
	}
}


void merge(int list[], int left, int mid, int right);


void mergesort(int list[], int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right)/ 2;

		mergesort(list, left, mid);
		mergesort(list, mid + 1, right);

		merge(list, left, mid, right);
	}

	return;
}

void merge(int list[], int left, int mid, int right)
{
	int* out;
	int indexL, indexR, indexO;

	indexL = left;
	indexR = mid + 1;
	indexO = 0;

	out = (int*)malloc(sizeof(int) * (right - left + 1));

	while (indexL <= mid && indexR <= right)
	{
		if (list[indexL] < list[indexR])
		{
			out[indexO] = list[indexL];
			indexO++;
			indexL++;
		}
		else
		{
			out[indexO] = list[indexR];
			indexR++;
			indexO++;
		}
	}

	if (indexL > mid)
	{
		memcpy(out + indexO, list + indexR, sizeof(int) * (right - indexR + 1));
	}
	else
	{
		memcpy(out + indexO, list + indexL, sizeof(int) * (mid - indexL + 1));
	}

	memcpy(list + left, out, sizeof(int) * (right - left + 1));

	free(out);
}

void display(int list[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf("%d, ", list[i]);
	}
	printf("\n");
}

int main()
{
	int n = 9;
	int listA[] = {5,3,8,4,9,1,6,2,7};
	int listB[] = {5,3,8,4,9,1,6,2,7};

	printf("merge sort : \n");

	display(listA, n);

	mergesort(listA, 0, n -1);

	display(listA, n);

	printf("quick sort : \n");

	display(listB, n);

	quicksort(listB, 0, n -1);

	display(listB, n);

	return 0;
}

//
#endif