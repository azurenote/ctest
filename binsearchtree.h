

#pragma once

#include "bintree.h"

enseed_begin


struct BinSearchTree : BinTree<int>
{
	typedef BinTreeNode<int> NodeType;
	typedef BinTree<int>::NodePointer NodePointer;




	NodePointer search(int key)
	{
		NodePointer result = root;

		while (result != nullptr)
		{
			if (key == result->data)
				break;

			else if (key < result->data)
				result = result->left;

			else
				result = result->right;
		}

		return result;
	}

	NodePointer insert(int value)
	{
		NodePointer node = root;

		NodePointer newnode = new BinTreeNode<int>(value);

		if (node == nullptr)
		{
			root = newnode;
			return newnode;
		}

		while (node != nullptr)
		{
			if (newnode->data < node->data)
			{
				if (node->left == nullptr)
					break;
				else
					node = node->left;
			}
			else
			{
				if (node->right == nullptr)
					break;
				else
					node = node->right;
			}
		}

		if (newnode->data < node->data)
			node->left = newnode;
		else
			node->right = newnode;

		return newnode;
	}

	void remove(int key)
	{
		NodePointer result = search(key);

		if (result == nullptr)
			return;


	}
};

enseed_end