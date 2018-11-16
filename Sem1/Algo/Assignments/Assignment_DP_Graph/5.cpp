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

    if(mov == m){                       // all movers finshed their work
        if(pack != p) return 1e18;      // not all packages are moved (invalid case)
        return 0;                       // all packages are moved (valid case)
    }

    if(pack == p) return 0;             // all packages are moved (valid case)

    int &st = dp[mov][pack];            // reference to this state in memory
    if(st != -1) return st;

    int sum = 0;
    int ans = 1e18;

    ans = rec(mov + 1, pack);           // this mover will not carry any thing

    for(int i = pack; i < p; i++){

        sum += arr[i];                  // this mover will take carry this package
        ans = min (ans , max(sum , rec(mov + 1, i + 1)) );      //minimize the anwer such that all packages are moved
    }

    return st = ans;
}

int main()
{
    //ios::sync_with_stdio(false);cin.tie(0);


    cin >>   m >> p;

    memdp(dp);              // set all the states to -1 (haven't stored values yet)

    for(int i = 0; i < p; i++) cin >> arr[i];

    cout << rec(0 , 0);


    return 0;
}
