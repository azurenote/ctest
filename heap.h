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

	void insert(int value)
	{
		data[size] = value;

		int ipos = size;
		int ppos = posParent(ipos);

		while (0 < ipos && compare(data[ppos], data[ipos]) < 0)
		{
			std::swap(data[ipos], data[ppos]);
			ipos = ppos;
			ppos = posParent(ipos);
		}

		++size;
	}

	int extract()
	{
		if (size < 1)
			throw std::exception("no item");

		int ret = data[0]; //top

	}

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