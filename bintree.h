#pragma once

#include <queue>
#include <stack>
#include <list>

#ifndef enseed_lib
#define enseed_lib
#define enseed_begin namespace enseed{
#define enseed_end }
#endif

enseed_begin

template<typename T>
struct BinTreeNode
{
	T data;
	bool visited;

	BinTreeNode* left;
	BinTreeNode* right;

	BinTreeNode()
	{
		left = right = nullptr;
		visited = false;
	}

	BinTreeNode(T data)
	{
		left = right = nullptr;
		visited = false;
		this->data = data;
	}


	BinTreeNode* insertAtLeft(T data)
	{
		left = new BinTreeNode<T>(data);
		return left;
	}

	BinTreeNode* insertAtRight(T data)
	{
		right = new BinTreeNode<T>(data);
		return right;
	}


};

template <typename T, typename NodeType = BinTreeNode<T>>
struct BinTree
{
	typedef NodeType* NodePointer;

	NodePointer root;

	BinTree()
		: root(nullptr)
	{
	}

	virtual ~BinTree()
	{
		std::list<NodePointer> list;

		preorderTraverse( [&list](NodePointer node){ list.push_back(node); } );

		for (auto node : list)
			delete node;
	}


	template <typename Traveler>
	void inorderTraverse(Traveler func)
	{
//		inorder(root, func);
		std::stack<NodePointer> stack;

		NodePointer node = root;

		while (true)
		{
			for (; node != nullptr; node = node->left)
				stack.push(node);

			if (stack.empty())
				break;

			node = stack.top();
			
			stack.pop();

			if (func(node) == false)
				break;

			node = node->right;
		}
	}


	template <typename Traveler>
	void preorderTraverse(Traveler func)
	{
//		preorder(root, func);
		std::stack<NodePointer> stack;

		if (root == nullptr)
			return;

		stack.push(root);

		while (stack.empty() == false)
		{
			NodePointer node = stack.top();
			
			stack.pop();

			func(node);

			if (node->right != nullptr)
				stack.push(node->right);

			if (node->left != nullptr)
				stack.push(node->left);
		}
	}


	template <typename Traveler>
	void postorderTraverse(Traveler func)
	{
//		postorder(root, func);
		std::stack<NodePointer> stack;
		std::list<NodePointer> list;

		stack.push(root);

		while (stack.empty() == false)
		{
			NodePointer node = stack.top();

			if (node->left != nullptr && node->left->visited == false)
				stack.push(node->left);
			
			else if (node->right != nullptr && node->right->visited == false)
				stack.push(node->right);
			else
			{
				if (func(node) == false)
					break;
				node->visited = true;

				list.push_back(node);

				stack.pop();
			}
		}

		for (auto itr = list.begin(); itr != list.end(); itr++)
			(*itr)->visited = false;
	}


	template <typename Traveler>
	void levelTraverse(Traveler func)
	{
		std::queue<NodePointer> queue;

		queue.push(root);

		while (queue.empty() == false)
		{
			NodePointer node = queue.front();

			queue.pop();

			if (func(node) == false)
				break;

			if (node->left != nullptr)
				queue.push(node->left);
			if (node->right != nullptr)
				queue.push(node->right);
		}
	}

};

enseed_end