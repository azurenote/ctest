#pragma once

#include "bintree.h"

enseed_begin

class Graph
{
public:
	struct Node
	{
	public:
		Node(int v)
			: value(v)
			, parent(nullptr)
		{}

	public:
		/// make non directional link
		void linkWith(Node* other);

		/// make directional link to target node
		void linkTo(Node* other);

	public:
		int value;
		Node* parent;
		std::list<Node*> adj;
	};

	typedef std::vector<Graph::Node*> Path;

public:
	Node& add(int value);

	Path getPathDFS(Graph::Node* root, Graph::Node*);
	Path getPathBFS(Graph::Node* root, Graph::Node*);
	
	static void Print(Path& list);


private:
	std::list<Node> nodes;
};


enseed_end;