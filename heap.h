#pragma once

#include "bintree.h"

enseed_begin

struct Heap
{
	typedef int (*Comparer)(int,int);
	Heap()
		: size(0)
	{
		memset(data, 0, sizeof(int)* 100);
	}

	~Heap()
	{
	}

	void insert(int element)
	{
		int i;
		i = ++size;
 
		while( (i!=1) && (element > data[i/2]) )
		{
			data[i] = data[i/2];
			i/=2;
		}
		data[i]=element;

		++size;
	}

	int extract()
	{
		if (size < 1)
			throw std::exception("no item");

		int parent = 1, child = 2;
		int element, temp;
         
		element = data[1];
		temp = data[size--];
 
		while( child <= size )
		{
			if( data[child] < data[child+1] )
				child++;
 
			if( temp >= data[child] ) break;

			data[parent]=data[child];
 
			parent=child;
			child*=2;
		}

		data[parent] = temp;
		return element;
	}

	bool any() {return 0 < size;}

	int posParent(int pos)
	{
		return (pos - 1) >> 1;
	}
	int posLeft(int pos) { return (pos << 1) + 1; }
	int posRight(int pos) {return (pos << 1) + 2; }

	int data[100];
	int size;
	Comparer compare;
};

enseed_end