#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	int height;
	int subtree;//Denotes the number of nodes in the subtree rooted at a particular node
	node *left,*right;
	node *parent;
};

node *newNode(int data)
{
	node *newnode = new node;
	newnode->data = data;
	newnode->height = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	newnode->subtree = 1;
	return newnode;
}


int height(node *root)
{
	//cout<<"\nYahan\n";
	if(root == NULL)
		return 0;
	return root->height;

}

int getSubtree(node *root)
{
	if(root == NULL)
		return 0;
	return root->subtree;
}

node *leftRotate(node *x)
{
	//cout<<"\nHere";
	node *y = x->right;
	node *t2 = y->left;
	y->left = x;
	x->right = t2;
	if(t2)
		t2->parent = x;
	if(x)
		x->parent = y;
	x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1; 
	x->subtree = getSubtree(x->left) + getSubtree(x->right) + 1;
	y->subtree = getSubtree(y->left) + getSubtree(y->right) + 1;
	return y;
}

node *rightRotate(node *x)
{
	//cout<<"\nIn right rotate";
	node *y = x->left;
	node *t3 = y->right;
	y->right = x;
	x->left = t3;
	//cout<<"\nProblem setting parent pointers\n";
	if(t3)
		t3->parent = x;
	if(x)
		x->parent = y;
	y->height = max(height(y->left),height(y->right)) + 1;
	x->height = max(height(x->left),height(x->right)) + 1;	
	x->subtree = getSubtree(x->left) + getSubtree(x->right) + 1;
	y->subtree = getSubtree(y->left) + getSubtree(y->right) + 1;
	return y;	
}
int getBalance(node *root)
{
	if(root == NULL)
		return 0;
	return height(root->left) - height(root->right);
}

node *insert(node *root,int data)
{
	if(root == NULL)
	{
		return newNode(data);
	}
	else if(root->data > data)
	{
		root->left = insert(root->left,data);
		root->left->parent = root;
	}
	else
	{
		root->right = insert(root->right,data);
		root->right->parent = root;
	}
	root->height = 1 + max(height(root->left),height(root->right));
	root->subtree = 1 + getSubtree(root->left) + getSubtree(root->right);
	int balance = getBalance(root);
	if(balance > 1)
	{
		if(data < root->left->data)
		{
			return rightRotate(root);
		}
		else
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
	}
	//Implies right subtree has greater height than left subtree of root
	if(balance < -1)
	{
		if(data > root->right->data)
		{
			return leftRotate(root);	
		}
		else
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
	}
	return root;
}

node *inorderSuccessor(node *root)
{
	node *curr = root;
	while(curr->left)
	{
		curr = curr->left;
	}
	return curr;
}
node *deleteNode(node *root,int data)
{
	if(root == NULL)
	{
		return root;
	}
	else if(data < root->data)
	{
		root->left = deleteNode(root->left,data);
	}
	else if(data > root->data)
	{
		root->right = deleteNode(root->right,data);
	}
	else
	{
		if(root->left == NULL || root->right == NULL)
		{
			node *temp = root->left ? root->left : root->right;
			if(!temp)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			delete(temp);
		}
		else
		{
			node *temp = inorderSuccessor(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right,temp->data);
		}
	}
	if(root == NULL)
		return root;
	root->height = 1 + max(height(root->left),height(root->right));
	root->subtree = 1 + getSubtree(root->left) + getSubtree(root->right);
	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) 
    { 
        root->left =  leftRotate(root->left); 
        return rightRotate(root); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
    return root;
}


node *findRank(node *root,int r)
{
	while(root)
	{
		if(r == 1 + getSubtree(root->right))
		{
			return root;
		}
		else if(r < 1 + getSubtree(root->right))
		{
			root = root->right;
		}
		else
		{
			r = r - 1 - getSubtree(root->right);
			root = root->left;
		}
	}
	return root;
}

void visit(node *root)
{
	cout<<"("<<root->data<<","<<root->subtree<<")"<<endl;
}

void preorder(node *root)
{
	if(root != NULL)
	{
		visit(root);
		//cout<<root->data<<" ";
		preorder(root->left);
		//visit(root);
		preorder(root->right);
	}
}
node *genRandomTree(node *root,int num_nodes)
{	
	//root = insert(root,num_nodes / 2);
	for(int i = 1; i < num_nodes/2; i++)
	{
		root = insert(root,i);
	}
	for(int i = num_nodes/2 + 1; i < num_nodes; i++)
	{
		root = insert(root,i);
	}
	return root;
}
int main()
{
	node *root = NULL;
	int n;
	cout<<"\nEnter the number of nodes that you want to insert in the tree : ";
	cin>>n;
	root = genRandomTree(root,n);
	root->parent = NULL;
	//preorder(root);
	int r;
	cout<<"\nEnter the rank to be searched : ";
	cin>>r;
	if(r >= 1 && r <= n)
	{
		node *resultant_rank_node = findRank(root,r);
		cout<<resultant_rank_node->data<<endl;
	}
	else
		cout<<"\nNo such element exists";
	return 0;
}