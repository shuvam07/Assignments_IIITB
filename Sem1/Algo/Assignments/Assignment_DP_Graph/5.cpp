#include <bits/stdc++.h>

using namespace std;

#define mem0(arr) memset(arr , 0 , sizeof arr)
#define memf(arr) memset(arr , false , sizeof arr)
#define memdp(arr) memset(arr , -1 , sizeof arr)
#define rep(i , n) for(int i = 1; i <= n; i++)
#define loop(i , n) for(int i = 0; i < n; i++)
#define pb push_back
#define fi first
#define se second
#define cs(y) cout << "Case " << y << ": "
#define cs2(y) cout << "Case " << y << ":" << "\n"

//typedef long long ll;

int m , p , w;
int arr [250 + 1];

int dp [15 + 1][250 + 1];

int rec(int mov , int pack){

    if(mov == m){                       
        if(pack != p) return INT_MAX;      
        return 0;                       
    }

    if(pack == p) return 0;            

    int &st = dp[mov][pack];            
    if(st != -1) return st;

    int sum = 0;
    int ans = INT_MAX;


    for(int i = pack; i < p; i++){

        sum += arr[i];                  
        ans = min (ans , max(sum , rec(mov + 1, i + 1)) );      
    }

    return st = ans;
}

int main()
{


    cin >>   m >> p;

    memdp(dp);              

    for(int i = 0; i < p; i++) cin >> arr[i];

    cout << rec(0 , 0) << endl;


    return 0;
}
