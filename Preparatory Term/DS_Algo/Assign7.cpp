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

void iterative_Inorder(struct Node *root){
	stack<struct Node*>s;
	if(root==NULL)
		return;
	while(root!=NULL){
		s.push(root);
		root = root->left;
	}
	while(!s.empty()){
		struct Node* temp = s.top();
		s.pop();
		cout<<temp->data<<" ";
		if(temp->right){
			root  = temp->right;
		}
		while(root!=NULL){
			s.push(root);
			root = root->left;
		}
			
	}
}

void iterative_Preorder(struct Node *root){
	queue<struct Node*>q;
	if(root==NULL)
		return;
	q.push(root);
	while(!q.empty()){
		struct Node *temp =q.front();
		cout<<temp->data<<" ";
		q.pop();
		if(temp->left){
			q.push(temp->left);
		}
		if(temp->right){
			q.push(temp->right);
		}
	}
}

void iterative_Postorder(struct Node *root){
	stack<struct Node*>s;
	if(root==NULL)
		return;
	while(root!=NULL){
		s.push(root);
		root = root->left;
	}
	while(!s.empty()){
		bool left = false , right = false;
		if(root!= NULL && s.top()->left == root){
			left = true;
		}
		else if(root!=NULL && s.top()->right == root){
			left =right = true;
		}
		root = s.top();
		if(root->left!=NULL && !left){
			s.push(root->left);
		}
		else if(root->right!=NULL && !right){
			s.push(root->right);
		}
		else{
			s.pop();
			cout<<root->data<<" ";
		}
	}
}

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
	iterative_Preorder(root);
	// struct Node *root1=construct_tree1(0,pre.size()-1);
	// cout<<endl;
	// print(root1);
	// cout<<endl;
	// struct Node *root2=construct_tree1(0,post.size()-1);
	// cout<<endl;
	// print(root2);
	cout<<endl;
	iterative_Inorder(root);
	cout<<endl;
	iterative_Postorder(root);
	// cout<<"Height : "<<height(root)<<endl;
	// for(int i=0;i<pre.size();i++){
	// 	cout<<level(root,1,pre[i])<<" ";		
	// }
	return 0;
}
