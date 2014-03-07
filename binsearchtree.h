

#pragma once

#include "bintree.h"

enseed_begin


struct BinSearchTree : BinTree<int>
{
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

	NodePointer insert(NodePointer element)
	{
		NodePointer node = root;
		

		while (node != nullptr)
		{
			if (element->data == node->data)
				return node;

			else if (element->data < node->data)
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

		NodePointer newnode = new BinTreeNode<int>(element->data);

		if (node == nullptr)
			root = newnode;

		else if (newnode->data < node->data)
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