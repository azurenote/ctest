

#pragma once

#include "bintree.h"

enseed_begin


struct BinSearchTree : BinTree<int>
{
<<<<<<< HEAD
	typedef BinTreeNode<int> NodeType;
	typedef BinTree<int>::NodePointer NodePointer;



=======
	typedef BinTree<int>::NodePointer NodePointer;

>>>>>>> f64162395304e7c3c8074c9b3b277a62fc7b1aee
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

<<<<<<< HEAD
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
=======
	NodePointer insert(NodePointer element)
	{
		NodePointer node = root;
		

		while (node != nullptr)
		{
			if (element->data == node->data)
				return node;

			else if (element->data < node->data)
>>>>>>> f64162395304e7c3c8074c9b3b277a62fc7b1aee
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

<<<<<<< HEAD

		if (newnode->data < node->data)
=======
		NodePointer newnode = new BinTreeNode<int>(element->data);

		if (node == nullptr)
			root = newnode;

		else if (newnode->data < node->data)
>>>>>>> f64162395304e7c3c8074c9b3b277a62fc7b1aee
			node->left = newnode;
		else
			node->right = newnode;

<<<<<<< HEAD

=======
>>>>>>> f64162395304e7c3c8074c9b3b277a62fc7b1aee
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