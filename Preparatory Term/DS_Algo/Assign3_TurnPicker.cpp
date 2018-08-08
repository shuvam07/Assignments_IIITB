#include<bits/stdc++.h>
using namespace std;

bool solve(multiset<int>& , multiset<int>& , int);

multiset<int>::iterator getMax(multiset<int> mult){
	multiset<int>::iterator maxIt;
	int maxVal = INT_MIN;
	for(multiset<int>::iterator it=mult.begin();it!=mult.end();it++){
		if(*it>maxVal){
			maxVal=*it;
			maxIt = it;
		}
	}	
	return maxIt;
} 

bool solveRec(multiset <int> &dist, multiset <int> &points){
	if(dist.empty())
		return true;
	int maxDist = *(getMax(dist));
	int maxPoint = *(getMax(points));
	//cout<<maxDist<<" "<<maxPoint<<endl;
	if(solve(dist,points,maxDist)){
		return true;
	}
	else if(solve(dist,points,maxPoint-maxDist))
		return true;
	else 
		return false;
}

bool solve(multiset <int> &dist, multiset <int> &points, int point){
	vector <int> toRemove;
	for(multiset<int>::iterator it=points.begin();it!=points.end();it++){
		if(dist.find(abs(*it-point)) != dist.end()){
			toRemove.push_back(abs(*it-point));
		}
		else
			return false;
		
	}
	points.insert(point);
	for(vector<int>::iterator it=toRemove.begin();it!=toRemove.end();*it++){
		dist.erase(dist.find(*it));
	}
	if(solveRec(dist,points)){
		return true;
	}
	else{
		points.erase(points.find(point));
		for(vector<int>::iterator it=toRemove.begin();it!=toRemove.end();*it++){
			dist.insert(*it);
		}
		return false;
	}
}



void solveTurn(multiset <int> &dist, multiset <int> &points){
	if(dist.empty())
		return;
	points.insert(0);
	multiset<int>::iterator it = getMax(dist);
	//cout<<*it<<endl;;
	points.insert(*it);
	dist.erase(dist.find(*it));
	//cout<<*(getMax(dist))<<endl;
	if(solveRec(dist,points)){
		for(multiset<int>::iterator it=points.begin();it!=points.end();it++){
			cout<<*it<<" ";
		}
	}
	else{
		cout<<"Not possible"<<endl;
	}
}


int main(){
	int n,val;
	cin>>n;
	multiset <int> dist;
	for(int i=0;i<n;i++){
		cin>>val;
		dist.insert(val);
	}
	multiset <int> points;
	solveTurn(dist,points);
}


