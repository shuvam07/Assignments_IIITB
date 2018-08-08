#include <bits/stdc++.h>
using namespace std;

vector <int> pre;
vector <int> post;
vector <int> in;

struct Node{
	int data;
	Node *left;
	Node *right;
};

void preOrder(struct Node *root){
	if(root!=NULL){
		cout<<root->data<<" ";
		pre.push_back(root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
	else
		return;
}

void postOrder(struct Node *root){
	if(root!=NULL){
		postOrder(root->left);
		postOrder(root->right);
		post.push_back(root->data);
		cout<<root->data<<" ";
	}
	else
		return;
}

void inOrder(struct Node *root){
	if(root!=NULL){
		inOrder(root->left);
		cout<<root->data<<" ";
		in.push_back(root->data);
		inOrder(root->right);
	}
	else
		return;
}

int height(struct Node *root){
	if(root==NULL)
		return 0;
	return max(height(root->left),height(root->right))+1;
}

void print(struct Node *root){
	cout<<"pre"<<" ";
	preOrder(root);
	cout<<endl<<"In"<<" ";
	inOrder(root);
	cout<<endl<<"post"<<" ";
	postOrder(root);
	cout<<endl;
}

struct Node* newNode(int data){
	struct Node *temp =(struct Node*)malloc(sizeof(struct Node));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

int level(struct Node *root,int lvl,int data){
	if(root==NULL)
		return 0;
	if(root->data == data)
		return lvl;
	int left = level(root->left,lvl+1,data);
	if(left!=0)
		return left;
	int right = level(root->right,lvl+1,data);
	return right;
}


int main() {
	struct Node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->right = newNode(6);
	print(root);
	// struct Node *root1=construct_tree1(0,pre.size()-1);
	// cout<<endl;
	// print(root1);
	// cout<<endl;
	// struct Node *root2=construct_tree1(0,post.size()-1);
	// cout<<endl;
	// print(root2);
	cout<<endl;
	cout<<"Height : "<<height(root)<<endl;
	for(int i=0;i<pre.size();i++){
		cout<<level(root,1,pre[i])<<" ";		
	}
	return 0;
}
