#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	int height;
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
	return newnode;
}


int height(node *root)
{
	//cout<<"\nYahan\n";
	if(root == NULL)
		return 0;
	return root->height;

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

void visit(node *root)
{
	if(root->parent)
		cout<<"("<<root->data<<","<<root->height<<","<<root->parent->data<<")"<<endl;
	else
		cout<<"("<<root->data<<","<<root->height<<")"<<endl;
}

void preorder(node *root)
{
	if(root != NULL)
	{
		//visit(root);
		cout<<root->data<<" ";
		preorder(root->left);
		//visit(root);
		preorder(root->right);
	}
}
node *genRandomTree(node *root,int num_nodes)
{	
	root = insert(root,num_nodes / 2);
	for(int i = 1; i < num_nodes/2; i++)
	{
		root = insert(root,i);
	}
	for(int i = num_nodes/2 + 1; i <= num_nodes; i++)
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
	preorder(root);
	return 0;
}