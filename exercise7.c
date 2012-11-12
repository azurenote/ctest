#include <stdio.h>
#include <stdlib.h>

#ifdef EXERCISE_7
typedef struct t_treenode
{
	int data;
	struct t_treenode *left, *right;
}TreeNode;

TreeNode n1 = {1, NULL,NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};

TreeNode* root = &n6;

void inorder(TreeNode* root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}

void preorder(TreeNode* root)
{
	if (root == NULL)
		return;

	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void postorder(TreeNode* root)
{
	if (root == NULL)
		return;

	postorder(root->left);
	postorder(root->right);

	printf("%d ", root->data);
}


int main()
{
	puts("\nin");
	inorder(root);

	puts("\npre");
	preorder(root);

	puts("\npost");
	postorder(root);
}
#endif