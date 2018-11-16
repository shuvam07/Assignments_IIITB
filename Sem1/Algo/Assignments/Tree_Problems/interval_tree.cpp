#include<bits/stdc++.h>
using namespace std;

struct Interval
{
	int l,r; 
};

struct node
{
	int l;
	int r;
	int max_right;
	int height;
	node *left,*right;
};
int getRightmostLimit(node *root)
{
	if(root == NULL)
		return 0;
	return root->max_right;
}

int height(node *root)
{
	if(root == NULL)
		return 0;
	return root->height;
}

int getBalance(node *root)
{
	return height(root->left) - height(root->right);
}
node *newNode(int l,int r)
{
	node *newnode = new node;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->max_right = r; 
	newnode->l = l;
	newnode->r = r;
	newnode->height = 1;
	return newnode;
}

node *leftRotate(node *x)
{
	node *y = x->right;
	node *t2 = y->left;

	y->left = x;
	x->right = t2;

	y->max_right = max(y->r,max(getRightmostLimit(y->left),getRightmostLimit(y->right)));
	x->max_right = max(x->r,max(getRightmostLimit(x->left),getRightmostLimit(x->right)));

	y->height = 1 + max(height(y->left),height(y->right));
	x->height = 1 + max(height(x->left),height(x->right));
	return y;
}

node *rightRotate(node *x)
{
	node *y = x->left;
	node *t3 = y->right;
	y->right = x;
	x->left = t3;

	y->max_right = max(y->r,max(getRightmostLimit(y->left),getRightmostLimit(y->right)));
	x->max_right = max(x->r,max(getRightmostLimit(x->left),getRightmostLimit(x->right)));

	y->height = 1 + max(height(y->left),height(y->right));
	x->height = 1 + max(height(x->left),height(x->right));

	return y;
}

node *zigzig(node *root,int flag)
{
	if(flag == 1)
	{
		return rightRotate(root);
	}	
	else
	{
		return leftRotate(root);
	}
}

node *zigzag(node *root,int flag)
{
	if(flag == 1)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else
	{
		root->right = rightRotate(root->right);
		return leftRotate(root->left);
	}
}

node *insert(node *root,int l,int r)
{
	if(root == NULL)
		return newNode(l,r);
	else if(l < root->l)
	{
		root->left = insert(root->left,l,r);
	}	
	else if(l > root->l)
	{
		root->right = insert(root->right,l,r);
	}
	else
		return root;
	
	root->height = 1 + max(height(root->left),height(root->right));
	root->max_right = max(root->r,max(getRightmostLimit(root->left),getRightmostLimit(root->right)));
	
	int balance = getBalance(root);
	if(balance > 1 && l < root->left->l)
	{
		return zigzig(root,1);
	}
	else if(balance < -1 && l > root->right->l)
		return zigzig(root,2);
	else if(balance > 1 && l > root->left->l)
	{
		return zigzag(root,1);
	}
	else if(balance < -1 && l < root->right->l)
	{
		return zigzag(root,2);
	}
	return root;
}

bool overlap(node *root,Interval a)
{
	while(root != NULL)
	{
		if(a.r >= root->l && root->r >= a.l)
		{	
			cout<<"\nOverlaps with interval : ["<<root->l<<","<<root->r<<"]"<<endl;
			return true;
		}
		if(root->left && root->left->max_right < a.l)
			root = root->right;
		else
			root = root->left;
	}
	return false;
}

int main()
{
	int n;
	cout<<"\nEnter the number of intervals : ";
	cin>>n;
	node *root = NULL;
	for(int i = 0; i < n; i++)
	{
		int a,b;
		cin>>a>>b;
		root = insert(root,a,b);
	}
	Interval x;
	x.l = 10;
	x.r = 20;
	bool res = overlap(root,x); 
	return 0;
}