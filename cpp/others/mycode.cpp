#include<bits/stdc++.h>
#define Long long long
using namespace std;
class Node{
public:
	struct Edge{
		Node*a,*b;
		Long dis;
		Edge(Node*a,Node*b,Long dis){
			this->a=a; this->b=b;
			this->dis=dis;
		}
		inline Node* operator[](Node*e){
			return e==a?b:a;
		}
	};
	Long height,sec,res;
	bool traversable,top;
	list<Edge*> nei;
	Node(){
		traversable=true; res=0;
		height=0; sec=0; top=false;
	}
	inline void connect(Node*e,Long dis){
		Edge*tmp=new Edge(e,this,dis);
		this->nei.push_back(tmp);
		e->nei.push_back(tmp);
	}
    //找环
	bool find(Edge*pre,vector<Node*>&ring,vector<Long>&dis){
		if(!traversable){
			ring.push_back(this);
			dis.push_back(pre->dis);
			return top=true;
		}
		traversable=false;
		Node*tmp;
		for(auto e:nei){
			tmp=(*e)[this];
			if(e==pre) continue;
			if(tmp->find(e,ring,dis)){
				if(*ring.begin()==this) return false;
				ring.push_back(this);
				dis.push_back(pre->dis);
				return top=true;
			}
			if(!ring.empty()) return false;
		}
		return false;
	}
    //计算树高和树内的最长路
	void initAsTree(Edge*pre){
		Node*tmp;
		traversable=false;
		for(auto e:nei){
			tmp=(*e)[this];
			if(tmp->top||e==pre) continue;
			tmp->initAsTree(e);
			if(height<e->dis+tmp->height){
				sec=height;
				height=e->dis+tmp->height;
			}else{
				sec=max(sec,e->dis+tmp->height);
			}
			res=max(res,tmp->res);
		}
		res=max(height+sec,res);
	}
};
Node**p;
Long*seq,*dis;
//环形DP
Long solve(vector<Node*>&r,vector<Long>&d){
	Long n=r.size(),res=0;
	for(int i=0;i<n;i++){
		seq[i]=seq[i+n]=r[i]->height;
		dis[i]=dis[i+n]=d[i];
		res=max(res,r[i]->res);
	}
	for(int i=1;i<(n<<1);i++) dis[i]+=dis[i-1];
	deque<int> q; q.push_back(0);
	for(int i=1;i<(n<<1);i++){
		while(!q.empty()&&i-q.front()>=n) q.pop_front();
		res=max(res,seq[q.front()]+seq[i]+dis[i-1]-dis[q.front()-1]);
		while(!q.empty()&&seq[i]-dis[i-1]>=
			  seq[q.back()]-dis[q.back()-1]) q.pop_back();
		q.push_back(i);
	}
	return res;
}
int main(){
	int n; scanf("%d",&n);
	p=new Node*[n+1];
	for(int i=0;i<=n;i++) p[i]=new Node();
	for(int i=1,e,dis;i<=n;i++){
		scanf("%d%d",&e,&dis);
		p[i]->connect(p[e],dis);
	}
	
	seq=new Long[n<<1];
	dis=new Long[(n<<1)+1]; *(dis++)=0;
	
	Long res=0;
    //处理每个基环树
	for(int i=1;i<=n;i++){
		if(!p[i]->traversable) continue;
		vector<Node*> ring; vector<Long> dis;
		p[i]->find(NULL,ring,dis);
		for(auto e:ring) e->initAsTree(NULL);
		res+=solve(ring,dis);
	}
	printf("%lld",res);
	return 0;
}