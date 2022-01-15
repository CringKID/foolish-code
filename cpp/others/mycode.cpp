#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstring>
#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
#define inf 0x7fffffff
using namespace std;
const int _N = 11000;
const int _M = 31000;
inline int read()
{
    char c = getchar(); int sign = 1; int x = 0;
    while(c > '9' || c < '0') { if(c=='-')sign = -1; c = getchar(); } 
    while(c <= '9' && c >= '0') { x *= 10; x += c - '0'; c = getchar(); }
    return x * sign;
}
int n, m;
int head[_N + _M];
struct edges{
	int node;
	int nxt;
}edge[1100000];
int tot = 0;
void add(int u, int v)
{
	edge[++tot].nxt = head[u];
	head[u] = tot;
	edge[tot].node = v;
}
bool vis[_N + _M];
void dfs(int now)
{
	vis[now] = true; 
	for(register int i = head[now];i;i = edge[i].nxt)
	{
		int exNode = edge[i].node;
		if(vis[exNode]) continue;
		dfs(exNode); 
	}
}
int main()
{
	n = read(), m = read();
	for(register int i = 1;i <= n;i++)
	{
		int k = read();
		for(register int j = 1;j <= k;j++)
		{
			int tmp = read();
			add(i, n + tmp);
			add(n + tmp, i);
		}
	}
	int ans = 0 ;
	memset(vis, false, sizeof(vis));
	for(register int i = 1;i <= n;i++)
		if(!vis[i])
		{
			dfs(i);
			ans ++;
		}
	printf("%d", ans - 1);
    return 0;
}