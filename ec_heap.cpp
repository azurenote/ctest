#include <iostream>

#include "heap.h"


int main()
{
	using namespace enseed;

	Heap heap;

	heap.compare = [](int a, int b)
	{
		if (a < b)
			return -1;
		else if (a == b)
			return 0;
		else
			return 1;
	};

	heap.insert(3);
	heap.insert(2);
	heap.insert(7);
	heap.insert(6);

	for (int i : heap.data)
	{
		if (i == 0)
			break;
		std::cout << i <<std::endl;
	}
}