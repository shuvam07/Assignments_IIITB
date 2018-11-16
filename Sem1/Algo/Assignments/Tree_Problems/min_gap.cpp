#include<bits/stdc++.h>
using namespace std;

struct node
{
	int data;
	int height;
	int subtree;//Denotes the number of nodes in the subtree rooted at a particular node
	int max;
	int min;
	int mingap;
	node *left,*right;
	node *parent;
};


int minFunction(int a,int b,int c,int d = INT_MAX)
{
	return min(min(a,b),min(d,c));
}


node *newNode(int data)
{
	node *newnode = new node;
	newnode->data = data;
	newnode->height = 1;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	newnode->subtree = 1;
	newnode->max = data;
	newnode->min = data;
	newnode->mingap = data;
	return newnode;
}

int getMin(node *root)
{
	if(root == NULL)
		return INT_MAX;
	return root->min;
}

int getMax(node *root)
{
	if(root == NULL)
		return INT_MIN;
	return root->max;
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


void updateMinGap(node *root)
{
	if(root->left && root->right)
	{
		int diff1 = abs(root->data - root->left->max);
		int diff2 = abs(root->data - root->right->min);
		root->mingap = min(min(diff1,diff2),min(root->left->mingap,root->right->mingap));
	}
	else if(root->left)
	{
		int diff = abs(root->data - root->left->max);
		root->mingap = min(diff,root->left->mingap);
	}
	else if(root->right)
	{
		int diff = abs(root->data - root->right->max);
		root->mingap = min(diff,root->right->mingap);
	}
	else
	{
		root->mingap = root->data;
	}
}


node *leftRotate(node *x)
{
	node *y = x->right;
	node *t2 = y->left;
	y->left = x;
	x->right = t2;
	if(t2)
		t2->parent = x;
	if(x)
		x->parent = y;
	//Update heights
	x->height = max(height(x->left),height(x->right)) + 1;
	y->height = max(height(y->left),height(y->right)) + 1; 
	//Update number of nodes in subtrees
	x->subtree = getSubtree(x->left) + getSubtree(x->right) + 1;
	y->subtree = getSubtree(y->left) + getSubtree(y->right) + 1;
	x->min = min(x->data,min(getMin(x->left),getMin(x->right)));
	y->min = min(y->data,min(getMin(y->left),getMin(y->right)));
	
	x->max = max(x->data,max(getMax(x->left),getMax(x->right)));
	y->max = max(y->data,max(getMax(y->left),getMax(y->right)));

	updateMinGap(x);
	updateMinGap(y);

	return y;
}

node *rightRotate(node *x)
{
	node *y = x->left;
	node *t3 = y->right;
	y->right = x;
	x->left = t3;
	if(t3)
		t3->parent = x;
	if(x)
		x->parent = y;
	y->height = max(height(y->left),height(y->right)) + 1;
	x->height = max(height(x->left),height(x->right)) + 1;	
	x->subtree = getSubtree(x->left) + getSubtree(x->right) + 1;
	y->subtree = getSubtree(y->left) + getSubtree(y->right) + 1;
	
	x->min = min(x->data,min(getMin(x->left),getMin(x->right)));
	y->min = min(y->data,min(getMin(y->left),getMin(y->right)));
	
	x->max = max(x->data,max(getMax(x->left),getMax(x->right)));
	y->max = max(y->data,max(getMax(y->left),getMax(y->right)));
	
	updateMinGap(x);
	updateMinGap(y);

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
	root->min = min(root->data,min(getMin(root->left),getMin(root->right)));
	root->max = max(root->data,max(getMax(root->left),getMax(root->right)));

	updateMinGap(root);

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
	root->min = min(root->data,min(getMin(root->left),getMin(root->right)));
	root->max = max(root->data,max(getMax(root->left),getMax(root->right)));

	updateMinGap(root);

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
	cout<<"("<<root->data<<","<<root->mingap<<","<<root->min<<","<<root->max<<")"<<endl;
	//cout<<"("<<root->data<<","<<root->mingap<<")"<<endl;

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
	root = insert(root,num_nodes / 2);
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
	root = deleteNode(root,1);
	preorder(root);
	return 0;
}