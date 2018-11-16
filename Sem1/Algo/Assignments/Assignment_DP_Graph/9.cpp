#include<bits/stdc++.h> 
using namespace std; 
  
int min(int x, int y, int z) 
{ 
    return min(min(x, y), z); 
} 
  
int editDistDP(string str1, string str2, int m, int n,int insert,int remove,int replace) 
{ 
    int dp[m+1][n+1]; 
  
    for (int i=0; i<=m; i++) 
    { 
        for (int j=0; j<=n; j++) 
        { 
            if (i==0) 
                dp[i][j] = insert;  

            else if (j==0) 
                dp[i][j] = remove; 

            else if (str1[i-1] == str2[j-1]) 
                dp[i][j] = dp[i-1][j-1]; 
  
             
            else
                dp[i][j] = 1 + min(dp[i][j-1] + insert,  
                                   dp[i-1][j] + remove,   
                                   dp[i-1][j-1] + replace
                                   );  
        } 
    } 
  
    return dp[m][n]; 
} 
  
int main() 
{ 
    int insert,remove,replace;

    string s;
    cin>>s;

    int n=s.size();

    string s1 = s.substr(0,n/2);
    string s2 = s.substr(n/2,n);
    reverse(s2.begin(),s2.end());

    cin>>insert>>remove>>replace; 

    cout<<s1<<endl<<s2<<endl;
  
    cout << min(editDistDP(s1, s2 , n/2, n/2, insert , remove , replace),
                editDistDP(s2, s1 , n/2, n/2, insert , remove , replace))<<endl; 

  
    return 0; 
} 