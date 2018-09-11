#include<bits/stdc++.h>
using namespace std;

struct Node
{
	Node* left;
	Node* right;
	int data;
};

Node* newNode(int val){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->left = NULL;
	temp->right = NULL;
	temp->data = val;
	return temp;
}

void inorder(Node* root){
	if(root!=NULL){
		inorder(root->left);
		cout<<root->data<<" ";
		inorder(root->right);
	}
}

Node* insert(Node* root,int val){
	if(root == NULL){
		return newNode(val);
	}
	if(val>root->data){
		root->right = insert(root->right,val);
	}
	else
		root->left = insert(root->left,val);

	return root;
}

Node* minVal(Node* root){
	Node* curr = root;
	while(curr->left!=NULL){
		curr = curr->left;
	}
	return curr;
}

Node* deleteBST(Node* root,int val){
	if(root == NULL)
		return root;
	if(val<root->data){
		root->left = deleteBST(root->left,val);
	}
	else if(val>root->data){
		root->right = deleteBST(root->right,val);
	}
	else{
		if(root->left == NULL){
			Node* temp = root->right;
			free(temp);
			return temp;
		}
		if(root->right == NULL){
			Node* temp = root->left;
			free(temp);
			return temp;
		}
		else{

			Node* temp = minVal(root->right);
			root->data = temp->data;
			root->right = deleteBST(root->right,temp->data);
		}
	}
	return root;
}

bool search(Node* root,int val){
	if(root == NULL){
		return false;
	}
	if(val == root->data)
		return true;

	if(val>root->data){
		search(root->right,val);
	}
	else
		search(root->left,val);

}

int main(){
	int n,val,q;
	cin>>n;
	Node* root = NULL;
	for(int i=0;i<n;i++)
	{
		cin>>val;
		if(root == NULL)
			root = insert(root,val);
		else
			insert(root,val);
	}
	inorder(root);
	cout<<endl<<"Search Queries"<<" ";
	cin>>q;
	while(q--){
		cin>>val;
		cout<<search(root,val)<<endl;
	}
	cout<<"Delete "<<" ";
	cin>>val;
	root = deleteBST(root,val);
	inorder(root);
	cout<<endl;
	cout<<endl;
}