
#if 0
#include <iostream>

#include "heap.h"


int main()
{
	using namespace enseed;

	Heap heap;

	heap.insert(3);
	heap.insert(2);
	heap.insert(7);
	heap.insert(6);


	while (heap.any())
	{
		std::cout << heap.extract() <<std::endl;
	}
}
#endif