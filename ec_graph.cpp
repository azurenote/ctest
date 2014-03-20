#include <iostream>

#include "graph.h"


int main()
{
	using namespace enseed;

	Graph g;
	Graph::Node  &n1 = g.add(1)
				,&n2 = g.add(2)
				,&n3 = g.add(3)
				,&n4 = g.add(4)
				,&n5 = g.add(5)
				,&n6 = g.add(6)
				,&n7 = g.add(7)
				,&n8 = g.add(8)
				;

	n1.linkWith(&n2);
	n1.linkWith(&n3);
	n1.linkWith(&n4);

	n2.linkWith(&n1);
	n2.linkWith(&n3);

	n3.linkWith(&n1);
	n3.linkWith(&n2);
	n3.linkWith(&n4);
	n3.linkWith(&n5);

	n4.linkWith(&n1);
	n4.linkWith(&n3);
	n4.linkWith(&n6);
	n4.linkWith(&n7);

	n5.linkWith(&n3);

	n6.linkWith(&n4);
	n6.linkWith(&n7);
	n6.linkWith(&n8);

	n7.linkWith(&n4);
	n7.linkWith(&n6);

	n8.linkWith(&n6);

	std::vector<Graph::Node*> nodes;

	nodes.push_back(&n1);
	nodes.push_back(&n2);
	nodes.push_back(&n3);
	nodes.push_back(&n4);
	nodes.push_back(&n5);
	nodes.push_back(&n6);
	nodes.push_back(&n7);
	nodes.push_back(&n8);

	for (auto item : nodes)
	{
		printf("DFS (%d) -> (%d)\n", n1.value, item->value);
		Graph::Print( g.getPathDFS(&n1, item) );
	}

	for (auto item : nodes)
	{
		printf("BFS (%d) -> (%d)\n", n1.value, item->value);
		Graph::Print( g.getPathBFS(&n1, item) );
	}

}




