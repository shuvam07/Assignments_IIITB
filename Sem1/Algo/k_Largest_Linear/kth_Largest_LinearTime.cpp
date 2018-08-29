#include <bits/stdc++.h>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int a[],int l,int r){
    int pivot = a[r];
    int i=l;
    for(int j=l;j<r;j++){
        if(a[j]<=pivot){
            swap(&a[i],&a[j]);
            i++;
        }
    }
    swap(&a[i],&a[r]);
    return (i);
}
int kth_Small(int a[],int l,int r,int k){
    
    if(k>0 && (r-l+1)>=k){
        int pos = partition(a,l,r);
        //printf("pos %d\n",pos);
        if((pos-l+1)==k)
            return pos;
        else if((pos-l+1)>k){
            return kth_Small(a,l,pos-1,k);
        }
        else
            return kth_Small(a,pos+1,r,k-pos+l-1);
    }
}

int main(){
	int data;
	int k,v,i=0,cnt=0;
    cout<<"Give the value of k : ";
	cin>>k;
	ifstream read("data.txt");
	int a[2*k];
    while(read>>data && cnt<2*k-1){
    	// if(v<0)
    	// 	break;
    	cnt++;
    	a[i++]=data;
    	//cout<<a[i++]<<" ";
    }
    a[i]=data;
    //cout<<endl;

    // for(i=0;i<2*k;i++){
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;

    int pos = kth_Small(a,0,2*k-1,k);
    //cout<<"median "<<a[pos]<<endl;
    // for(int i=0;i<2*k;i++){
    //     cout<<a[i]<<" ";
    // }
    // cout<<endl;
    int flag=0;
    while(1){
    	cnt=0,i=0;
    	while(read>>data && cnt<pos){
    	// if(v<0)
    	// 	break;
	    	cnt++;
	    	a[pos-i]=data;
	    	i++;
    	}
        a[pos-i]  = data;
        // for(int i=0;i<2*k;i++){
        //     cout<<a[i]<<" ";
        // }
        // cout<<endl;
	    pos = kth_Small(a,0,2*k-1,k);
	    if(read>>data==0)
	    	break;
        // for(int i=0;i<2*k;i++){
        //     cout<<a[i]<<" ";
        // }
        // cout<<endl;
        
    }
    for(int i=0;i<k;i++){
    	cout<<a[2*k-i-1]<<" ";
    }
    cout<<endl;
  	return 0;
}