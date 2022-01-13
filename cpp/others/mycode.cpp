#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,t1,t2,fg,s=1,tp;
int sta[N],in[N],out[N],pre[N];
vector<int> e[N];
void dfs(int x)
{
    for(int i=pre[x];i<e[x].size();i=pre[x])
    {
        pre[x]=i+1;
        dfs(e[x][i]);
    }
    sta[++tp]=x;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        e[x].push_back(y);out[x]++,in[y]++;
    }
    for(int i=1;i<=n;i++) 
    {
        if(in[i]==out[i]-1) t1++,s=i;
        if(out[i]==in[i]-1) t2++;
        if(in[i]!=out[i]) fg=1;
    }
    if(fg&&!(t1==1&&t2==1)) return puts("No"),0;
    for(int i=1;i<=n;i++) sort(e[i].begin(),e[i].end());
    dfs(s);for(int i=tp;i>=1;i--) printf("%d ",sta[i]);
    return 0;
}