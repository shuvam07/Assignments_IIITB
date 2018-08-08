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

int search_idx(int st,int end,int data){
	for(int i=st;i<=end;i++){
		if(in[i]==data)
			return i;
	}
}
struct Node* construct_tree1(int st,int end){
	// InOrder and PreOrder
	static int preIdx = 0;
	if(st>end)
		return NULL;
	struct Node *root = newNode(pre[preIdx++]);
	if(st==end)
		return root;
	int idx = search_idx(st,end,pre[preIdx-1]);
	root->left = construct_tree1(st,idx-1);
	root->right = construct_tree1(idx+1,end);
	return root;
}

struct Node* construct_tree2(int st,int end){
	// InOrder and PostOrder
	static int postIdx = end;
	if(st>end)
		return NULL;
	struct Node *root = newNode(post[postIdx--]);
	if(st==end)
		return root;
	int idx = search_idx(st,end,post[postIdx+1]);
	root->left = construct_tree2(st,idx-1);
	root->right = construct_tree2(idx+1,end);
	return root;
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
	cout<<endl;
	struct Node *root2=construct_tree1(0,post.size()-1);
	cout<<endl;
	print(root2);
	return 0;
}
