
#include <iostream>

#include "binsearchtree.h"

using namespace std;

int main()
{
<<<<<<< HEAD
	using namespace enseed;


	BinSearchTree tree;

	tree.insert(3);
	tree.insert(1);
	tree.insert(2);
	tree.insert(4);
	tree.insert(5);

	tree.inorderTraverse([](BinSearchTree::NodePointer node)
	{
		cout << node->data << endl;
	});

	auto res = tree.search(5);
	if (res)
		cout << res->data << endl;
=======
>>>>>>> f64162395304e7c3c8074c9b3b277a62fc7b1aee
}