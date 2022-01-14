#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+5;

int Arr[maxn][2],Father[maxn],ID[maxn],Cost[maxn];
#define tl(rt) Arr[rt][0]
#define tr(rt) Arr[rt][1]
int Root(int rt){return tl(Father[rt])==rt||tr(Father[rt])==rt;}
int Get(int rt){return rt=tr(Father[rt]);}

void Pushup(int rt){ID[rt]=ID[tl(rt)]?ID[tl(rt)]:(Cost[rt]?rt:(ID[tr(rt)]?ID[tr(rt)]:0));}
void Rotate(int rt){
	int F1=Father[rt],F2=Father[F1],GetSum=Get(rt),Val=Arr[rt][!GetSum];

	if(Root(F1)) Arr[F2][Get(F1)]=rt;
	Arr[rt][!GetSum]=F1,Arr[F1][GetSum]=Val;

	if(Val) Father[Val]=F1;
	Father[F1]=rt,Father[rt]=F2;Pushup(rt),Pushup(F1); 
}
void Splay(int rt){while(Root(rt)){if(Root(Father[rt])) Rotate(Get(rt)^Get(Father[rt])?rt:Father[rt]);Rotate(rt);}}
void Access(int rt){for(int Fa=0;rt;rt=Father[Fa=rt]) Splay(rt),tr(rt)=Fa,Pushup(rt);}

int n,ques,Tot,Head[maxn];
struct Road{int To,Next;}Edge[maxn<<1];
void Add(int from,int to){Edge[++Tot]=(Road){to,Head[from]},Head[from]=Tot;}

void INIT(int rt,int Fa){Father[rt]=Fa;for(int i=Head[rt];i;i=Edge[i].Next){if(Edge[i].To==Fa) continue;INIT(Edge[i].To,rt);}}

int main(){
	scanf("%d %d",&n,&ques);
	for(int i=1,from,to;i<n;i++) scanf("%d %d",&from,&to),Add(from,to),Add(to,from);
	INIT(1,0);

	for(int i=1,Opt,Val;i<=ques;i++){scanf("%d %d",&Opt,&Val);if(Opt){Access(Val),Splay(Val),printf("%d\n",ID[Val]==0?-1:ID[Val]);}else{Splay(Val),Cost[Val]^=1,Pushup(Val);}}

	return 0;
}