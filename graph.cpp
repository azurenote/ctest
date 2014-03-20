
#include <set>
#include <queue>

#include "graph.h"



enseed_begin





/// utility
bool contains(std::list<Graph::Node*>& list, Graph::Node const* target)
{
	return find(list.begin(), list.end(), target) != list.end();
}




/// make non directional link
void Graph::Node::linkWith(Node* other)
{
	linkTo(other);
	other->linkTo(this);
}










/// make directional link to target node
void Graph::Node::linkTo(Node* other)
{
	if (contains(adj, other) == false)
		adj.push_back(other);
}










/// create node
Graph::Node& Graph::add(int value)
{
	nodes.push_back(Node(value));

	return nodes.back();
}










/// make a path by Depth-first searching
Graph::Path Graph::getPathDFS(Graph::Node* root, Graph::Node* target)
{
	std::stack<Graph::Node*> stack;
	std::set<Graph::Node*> visited;
	Path list;

	stack.push(root);

	while(!stack.empty())
	{
		auto node = stack.top();

		list.push_back(node);
		visited.insert(node);

		if (node == target)
			break;

		bool backtrack = true;

		for (auto adj : node->adj)
		{
			if (visited.find(adj) == visited.end())
			{
				stack.push(adj);
				backtrack = false;
			}
		}

		if (backtrack)
		{
			while (!stack.empty() && stack.top() == list.back())
			{
				stack.pop();
				list.pop_back();
			}

			while (!stack.empty() && visited.find(stack.top()) != visited.end())
				stack.pop();
		}
	}

	return list;
}










/// make a path by Breadth-first searching
Graph::Path Graph::getPathBFS(Graph::Node* root, Graph::Node* target)
{
	std::queue<Graph::Node*> queue;
	Path list;

	queue.push(root);

	root->parent = root;

	while(!queue.empty())
	{
		auto node = queue.front();

		queue.pop();

		if (node == target)
			break;

		for (auto adj : node->adj)
		{
			if (adj->parent)
				continue;

			queue.push(adj);
			adj->parent = node;
		}
	}

	std::stack<Graph::Node*> stack;

	Graph::Node* current = target;


	// reverse list
	while (current->parent && current != root)
	{
		stack.push(current);
		current = current->parent;
	}

	list.push_back(root);

	while (stack.empty() == false)
	{
		list.push_back(stack.top());
		stack.pop();
	}

	for (auto& node : nodes)
	{
		node.parent = nullptr;
	}

	return list;
}


void Graph::Print(Path& path)
{
	printf("start");
	for (auto node : path)
	{
		printf("->%d", node->value);
	}
	printf("\n");
}





enseed_end