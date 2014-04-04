#include <iostream>
#include <random>
#include <functional>

const int Size = 10;

typedef std::function<bool (int const&, int const&)> Comparer;

void MakeRandom(int* data, int count);
void PrintArray(int* data, int count);

void BubbleSort(int* data, int count, Comparer);
void InsertSort(int* data, int count, Comparer);
void SelectSort(int* data, int count, Comparer);





template<typename Function>
void Case(Function f)
{
	int dataset[Size];

	puts("---------------------------");
	puts("original array :");
	MakeRandom(dataset, Size);
	PrintArray(dataset, Size);

	std::less<int> less;
	std::greater<int> greater;

	puts("sorted by less() :");
	BubbleSort(dataset, Size, less);
	PrintArray(dataset, Size);

	puts("sorted by greater() :");
	BubbleSort(dataset, Size, greater);
	PrintArray(dataset, Size);

	puts("");
}










int main()
{
	puts("func: bubble");
	Case(BubbleSort);

	puts("func: insertion");
	Case(InsertSort);

	puts("func: selection");
	Case(SelectSort);
}










void PrintArray(int* data, int count)
{
	printf("[");
	for (int i = 0 ; i < count; ++i)
	{
		if (i != 0)
			printf(", ");

		printf("%d", data[i]);
	}
	printf("]\n");
}










void MakeRandom(int* data, int count)
{
	using namespace std;
    random_device rd;
    default_random_engine e1(rd());
    uniform_int_distribution<int> uniform_dist(1,100);

	for (int i = 0; i < Size; ++i)
		data[i] = uniform_dist(e1);
}










void BubbleSort(int* data, int count, Comparer f)
{
	for (int i = 0; i < count; ++i)
		for (int j = 0; j < count; ++j)
		{
			if (f(data[i], data[j]))
				std::swap(data[i], data[j]);
		}
}









void SelectSort(int* data, int count, Comparer comp)
{
	int currentTarget = *data;

	for (int i = 0; i < count; ++i)
	{
		for (int j = i; j < count; ++j)
		{
			if (comp( currentTarget, data[j] ))
				currentTarget = data[j];
		}

		data[i] = currentTarget;
	}
}









void InsertSort(int* data, int count, Comparer comp)
{
	for (int i = 1 ; i < count; ++i)
	{
		int temp = data[i];
		int j = i - 1;

		for (; 0 <= j && comp(data[j], temp); --j)
			data[j + 1] = data[j];

		data[j + 1] = temp;
	}
}