#include<bits/stdc++.h>
using namespace std;
#include<atcoder/all>
using namespace atcoder;
using mint=modint998244353;

int main(){
    int n,k;cin>>n>>k;
    vector<pair<int,int>>pq(n);
    for(int i=0;i<n;i++)cin>>pq[i].first;
    for(int i=0;i<n;i++)cin>>pq[i].second;
    sort(pq.begin(),pq.end());
    vector<vector<vector<mint>>>dp(n,vector<vector<mint>>(n+1,vector<mint>(n+2)));
    dp[0][1][n+1]=1;
    dp[0][0][pq[0].second]=1;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            for(int l=0;l<=n+1;l++){
                if(l>pq[i+1].second)dp[i+1][j+1][l]+=dp[i][j][l];
                dp[i+1][j][min(pq[i+1].second,l)]+=dp[i][j][l];
            }    
        }
    }
    mint ans=0;
    for(int i=1;i<=n+1;i++)ans+=dp[n-1][k][i];
    cout<<ans.val()<<endl;
}