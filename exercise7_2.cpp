#if 0
#include <iostream>
#include "bintree.h"
#include "heap.h"
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace enseed;

void foo(BinTreeNode<int>* node)
{
	cout<< node->data << endl;
}

void main()
{
	BinTreeNode<int>* temp;
	BinTreeNode<int>* temp2;
	BinTreeNode<int>* temp3;
	BinTree<int> tree;

	temp = tree.root =  new BinTreeNode<int>(1);

	temp2 = temp->insertAtLeft(2);
	temp3 = temp->insertAtRight(3);

	temp = temp2;

	temp->insertAtLeft(4);
	temp->insertAtRight(5);

	temp = temp3;

	temp->insertAtLeft(6);
	temp->insertAtRight(7);
	
	cout << "post" << endl;
	tree.postorderTraverse([](BinTreeNode<int>* node){cout<<node->data<<endl;});

	cout << "level " << endl;
	tree.levelTraverse([](BinTreeNode<int>* node)
	{
		cout << node->data << endl;
	});
	getchar();
}
#endif