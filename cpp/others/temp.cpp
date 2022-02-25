#include <bits/stdc++.h>
#define P pair<ll,ll>
#define F first
#define S second
typedef long long ll;
using namespace std;
int n, m, x;
ll dp[5002][5002], ans = -1, a[5002];
deque< P > q[5002];
int main() {
    scanf("%d%d%d",&n,&m,&x);
    for(int i = 1; i <= n; ++i) scanf("%lld",&a[i]);
    memset(dp,-1,sizeof(dp));
    dp[0][0] =  0;
    q[0].push_back(P(0,0));
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= i && j <= x; ++j) {
            while(!q[j].empty() && q[j].front().S < i-m) q[j].pop_front();
        }
        for(int j = 1; j <= i && j <= x; ++j) {
            if(!q[j-1].empty() && q[j-1].front().F != -1)  dp[i][j] = q[j-1].front().F + a[i];
        }
        for(int j = 0; j <= i && j <= x; ++j) {
            while(!q[j].empty() && dp[i][j]>=q[j].back().F) q[j].pop_back();
            if(dp[i][j] != -1) q[j].push_back(P(dp[i][j],i));
        }
 
        if(n-i < m) ans = max(ans, dp[i][x]);
    }
    printf("%lld\n",ans);
}