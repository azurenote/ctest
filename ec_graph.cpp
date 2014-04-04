

#include <iostream>
#include <queue>
#include <list>
#include <vector>


class Graph
{
public:
	struct Edge;

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
		std::list<Edge*> edges;
	};


	struct Edge
	{
		Node* a;
		Node* b;
		int tag;
	};

	typedef Node* node_ptr;
	typedef std::vector<node_ptr> Path;
	typedef std::list<Edge> EdgeList;

public:
	Node& add(int value);

	Path getPathDFS(node_ptr root, node_ptr);
	Path getPathBFS(node_ptr root, node_ptr);
	
	static void Print(Path& list);

	void linkWith(node_ptr a, node_ptr b);
	void linkTo(node_ptr a, node_ptr b);
	void resetTags();

private:
	std::list<Node> nodes;
	EdgeList edges;
};



void Graph::linkWith(Graph::node_ptr a, Graph::node_ptr b)
{
	linkTo(a, b);
	linkTo(b, a);
}

void Graph::linkTo(Graph::node_ptr a, Graph::node_ptr b)
{
	Edge edge = {a, b, 0};

	edges.push_back(edge);

	a->edges.push_back(&edges.back());
}

void Graph::resetTags()
{
	for (auto& edge : edges)
	{
		edge.tag = 0;
	}
}
