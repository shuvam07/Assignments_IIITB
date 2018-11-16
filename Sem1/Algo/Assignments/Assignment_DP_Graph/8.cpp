#include<bits/stdc++.h>
using namespace std;
 
int find(vector<int> &v,string num)
{
    int ans=0;
    for(int i=0;i<num.size();i++)
        ans+=v[num[i]-'0'];
    return ans;
}
 
int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        vector<int> v(10);
        bool b=true;
        for(int i=0;i<10;i++)
            cin>>v[i];
        while(b)    
        {
            b=false;
            for(int i=0;i<10;i++)
            for(int j=i;j<10;j++)
            if(v[(i+j)%10]>v[i]+v[j])
            {
                v[(i+j)%10]=v[i]+v[j];
                b=true;
            }
        }
        int n;
        cin>>n;
        string num;
        cin>>num;
        int ans=find(v,num);
        cout<<ans<<endl;
          
    }
    return 0;
    
    
}