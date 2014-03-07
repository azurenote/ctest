#pragma once

#include "bintree.h"
#include <xutility>

enseed_begin

template <typename T>
struct AVLTreeNode
{
	T data;
	bool visited;

	AVLTreeNode* left;
	AVLTreeNode* right;

	AVLTreeNode()
	{
		left = right = nullptr;
		visited = false;
	}

	AVLTreeNode(int data)
	{
		left = right = nullptr;
		visited = false;
		this->data = data;
	}


	AVLTreeNode* insertAtLeft(T data)
	{
		left = new AVLTreeNode<T>(data);
		return left;
	}

	AVLTreeNode* insertAtRight(T data)
	{
		right = new BinTreeNode<T>(data);
		return right;
	}

	int getHeight() 
	{ 
		int heightLeft	= left	== nullptr ?
			0 : left->getHeight();
		int heightRight	= right	== nullptr ?
			0 : right->getHeight();

		return 1 + max(heightLeft, heightRight);
	}

	int getBalanceFactor()
	{
		int heightLeft	= left	== nullptr ?
			0 : left->getHeight();
		int heightRight	= right	== nullptr ?
			0 : right->getHeight();

		return heightLeft - heightRight;
	}

};

template<typename T>
class AVLTree : BinTree<int, AVLTreeNode<T>>
{
public :
	typedef AVLTreeNode<T> node_t;
	typedef AVLTreeNode<T>* node_ptr;

	AVLTree()
	{
		root = nullptr;
	}

	void insert(int data)
	{
		if (root == nullptr)
		{
			root = new node_t(data);
			return;
		}

		bool doing = true;
		NodePointer node = root;
		while (doing)
		{
			if (data <= node->data)
			{
				if (node->left == nullptr)
				{
					node->left = new node_t(data);
					doing = false;
					root = rebalance(root);
				}
				else
					node = node->left;
			}
			else
			{
				if (node->right == nullptr)
				{
					node->right = new node_t(data);
					doing = false;
					root = rebalance(root);
				}
				else
					node = node->right;
			}

		}

		return;
	}
private:
	node_ptr rotateLL(node_ptr parent)
	{
		node_ptr child = parent->left;
		parent->left = child->right;
		child->right = parent;
		return child;
	}

	node_ptr rotateRR(node_ptr parent)
	{
		node_ptr child = parent->right;
		parent->right = child->left;
		child->left = parent;
		return child;
	}

	node_ptr rotateRL(node_ptr parent)
	{
		node_ptr child = parent->right;
		parent->right = rotateLL(child);
		return rotateRR(parent);
	}

	node_ptr rotateLR(node_ptr parent)
	{
		node_ptr child = parent->left;
		parent->left = rotateRR(child);
		return rotateLL(parent);
	}

	node_ptr rebalance(node_ptr& node)
	{
		int balanceFactor = node->getBalanceFactor();

		if (balanceFactor > 1)
		{
			if (left == nullptr)
			{
			}
			else if (node->left->getBalanceFactor() > 0)
				node = rotateLL(node);
			else
				node = rotateLR(node);
		}
		else if (balanceFactor < -1)
		{
			if (right == nullptr)
			{
			}
			else if (node->right->getBalanceFactor() < 0)
				node = rotateRR(node);
			else
				node = rotateRL(node);
		}

		return node;
	}
};



enseed_end