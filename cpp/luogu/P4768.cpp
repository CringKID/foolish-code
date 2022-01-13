#include<bits/stdc++.h>

using namespace std;

const int maxn=2e5+5,inf=2e9;

struct Node{int val,place;bool operator < (const Node &Another) const {return val>Another.val;}};priority_queue<Node> pq;vector<Node> Fir[maxn],Fat[maxn],mnn[maxn];
struct Road{int to,next,val;bool operator < (const Road &Another) const {return next>Another.next;}}Edge[maxn<<1];

int vis[maxn],Dist[maxn],Size[maxn],Father[maxn],T,n,m,las,q,k,s;
int Root(int x){return Father[x]==x?x:Father[x]=Root(Father[x]);}

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m),las=0;
        for(int i=1;i<=n;i++) Fir[i].clear(),Fat[i].clear(),mnn[i].clear();
        for(int i=0,u,v,l,a;i<m;i++) scanf("%d %d %d %d",&u,&v,&l,&a),Fir[u].push_back(Node{l,v}),Fir[v].push_back(Node{l,u}),Edge[i]=Road{a,u,v};
        sort(Edge,Edge+m),memset(vis,0,sizeof(vis)),memset(Dist,0x3f,sizeof(Dist));

        Dist[1]=0,pq.push((Node){0,1});
        while(!pq.empty()){
            Node from=pq.top();pq.pop();
            if(vis[from.val]) continue;vis[from.val]=true;

            for(Node to:Fir[from.val]) if(from.val+to.val<Dist[to.place]) pq.push((Node){Dist[to.place]=from.val+to.val,to.place});
        }

        for(int i=1;i<=n;i++) Fat[i].push_back((Node){inf,Father[i]=i}),mnn[i].push_back((Node){inf,Dist[i]}),Size[i]=1;
        for(int Next,i=0,from,to;i<m;i++){
            Next=Edge[i].next,from=Root(Edge[i].val),to=Root(Edge[i].to);if(from==to) continue;
            if(Size[from]<Size[to]) from^=to^=from^=to;Size[from]+=Size[to],Father[to]=from;

            mnn[from].push_back((Node){Next,min(mnn[from].begin()->val,mnn[to].begin()->val)});
            Fat[to].push_back((Node){Next,from});
        }

        scanf("%d %d %d",&q,&k,&s);
        for(int to,Next,Temp,i=0;i<q;i++){
            scanf("%d",&Temp),to=(Temp+k*las-1)%n+1;scanf("%d",&Temp),Next=(Temp+k*las)%(s+1);
            while(to!=(Temp=(--lower_bound(Fat[to].begin(),Fat[to].end(),(Node){Next,0}))->val)) to=Temp;
            printf("%d\n",las=(--lower_bound(mnn[to].begin(),mnn[to].end(),(Node){Next,0}))->val);
        }
    }

    return 0;
}