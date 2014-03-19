#include <iostream>

#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <set>

class Graph
{
public:
	struct Node
	{
		Node(int v) : value(v){}
		int value;
		std::list<Node*> adj;
	};
};

void traverseDFS(Graph::Node* root);
void traverseBFS(Graph::Node* root);

int main()
{
	Graph::Node n1(1),n2(2),n3(3),n4(4)
		,n5(5),n6(6),n7(7),n8(8);

	n1.adj.push_back(&n2);
	n1.adj.push_back(&n3);
	n1.adj.push_back(&n4);

	n2.adj.push_back(&n1);
	n2.adj.push_back(&n3);

	n3.adj.push_back(&n1);
	n3.adj.push_back(&n2);
	n3.adj.push_back(&n4);
	n3.adj.push_back(&n5);

	n4.adj.push_back(&n1);
	n4.adj.push_back(&n3);
	n4.adj.push_back(&n6);
	n4.adj.push_back(&n7);

	n5.adj.push_back(&n3);

	n6.adj.push_back(&n4);
	n6.adj.push_back(&n7);
	n6.adj.push_back(&n8);

	n7.adj.push_back(&n4);
	n7.adj.push_back(&n6);

	n8.adj.push_back(&n6);

	puts("\nDFS");
	traverseDFS(&n1);
	puts("\nBFS");
	traverseBFS(&n1);
}


using namespace std;


typedef vector<Graph::Node*> Path;

bool contain(Path&, Graph::Node*); 

void print(list<Path>& list);

void traverseDFS(Graph::Node* root)
{
	set<Graph::Node*> visited;

	stack<Graph::Node*> bin;

	bin.push(root);

	list<Path> trace;

	Path newpath;
	newpath.push_back(root);
	trace.push_back(newpath);

	while (bin.empty() == false)
	{
		auto node = bin.top();
		bin.pop();

		auto path = trace.back();

		visited.insert(node);

		for (auto adj : node->adj)
		{
			if (contain(path, adj))
				continue;

			bin.push(adj);

			auto newpath = path;

			newpath.push_back(adj);

			trace.push_back(newpath);
		}
	}

	print(trace);
}

void traverseBFS(Graph::Node* root)
{
	set<Graph::Node*> visited;

	queue<Graph::Node*> bin;

	bin.push(root);

	while (bin.empty() == false)
	{
		auto node = bin.front();
		bin.pop();

		visited.insert(node);

		for (auto adj : node->adj)
		{
			if (visited.find(adj) != visited.end())
				continue;

			bin.push(adj);

			printf("%d", adj->value);
		}
	}
}


void print(list<Path>& list)
{
	for (auto item : list)
	{
		for (auto node : item)
		{
			printf("%d->", node->value);
		}
		puts("end");
	}
}


bool contain(Path& path, Graph::Node* node)
{
	return 
		std::find(path.begin(), path.end(), node)
		!= path.end();
}