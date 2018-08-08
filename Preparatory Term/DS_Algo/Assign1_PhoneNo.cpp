#include <iostream>
using namespace std;

#define MAX 1000005
#define ll long long int

ll hash_map[MAX];

void add(ll n){
	int key  = n % MAX;
	if(hash_map[key]==-1){
		hash_map[key]=n;
	}
	else{
		int prev = key-1;
		while(hash_map[key]!=-1 && prev!=key){
			key++;
			key=key%MAX;
		}
		if(prev == key){
			cout<<"Sorry hash is full"<<endl;
		}
		else{
			hash_map[key] = n;
		}
	}
}

void remove(ll n){
	int key = n % MAX;
	if(hash_map[key]==n){
		hash_map[key]=-1;
		cout<<"Number deleted successfully";
	}
	else{
		int prev = key-1;
		while(hash_map[key]!=n && prev!=key && hash_map[key]!=-1){
			key++;
			key=key%MAX;
		}
		if(hash_map[key]==-1 || (prev==key)){
			cout<<"Sorry number not found"<<endl;
		}
		else if(hash_map[key]==n){
			hash_map[key] = -1;
			cout<<"Number deleted successfully";
		}
	}
}

void search(ll n){
	int key  = n % MAX;
	if(hash_map[key]==n){
		cout<<"Found number"<<endl;
	}
	else{
		int prev = key-1;
		while(hash_map[key]!=n && prev!=key && hash_map[key]!=-1){
			key++;
			key=key%MAX;
		}
		if(hash_map[key]==-1 || (prev==key)){
			cout<<"Sorry number not found"<<endl;
		}
		else if(hash_map[key]==n){
			cout<<"Found number"<<endl;
		}
	}
}

int main() {
	for(int i=0;i<MAX;i++)
		hash_map[i]=-1;
	int op;
	ll n;
	while(1){
		cout<<"choose 1 to add , 2 to remove and 3 to search\n";
		cin>>op;
		cout<<"Enter a number\n";
		cin>>n;
		switch(op){
			case 1: add(n);
					break;
			case 2: remove(n);
					break;
			case 3: search(n);
					break;
			default: cout<<"Invalid";
		}
	}
	return 0;
}
