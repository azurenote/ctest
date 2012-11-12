#include <stdio.h>

#define SWAP(a, b) a ^= b ^= a ^= b

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
			SWAP(list[low], list[high]);

	}while(low < high);

	SWAP(list[left], list[high]);

	return high;
}

void quicksort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quicksort(list, left, q-1);
		quicksort(list, q+1, right);
	}
}

int main()
{
	int n = 9;
	int i = 0;
	int list[] = {5,3,8,4,9,1,6,2,7};

	quicksort(list, 0, n-1);

	for (i = 0; i < n; i++)
	{
		printf("%d, ", list[i]);
	}
	printf("\n");

	return 0;
}