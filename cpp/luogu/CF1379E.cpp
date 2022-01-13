#include<bits/stdc++.h>
#define lowbit(x) x&-x

using namespace std;

const int maxn=1e5+5;

int Array[maxn],n,m,k,mmax,Base;
bool Check(int Number){return Number-lowbit(Number)==0;}

int main(){
    scanf("%d %d",&n,&k);
    mmax=max((n-3)/2,0);
    if(k>mmax||!(n&1)||n==9&&k==2||Check(n+1)&&k==1||!Check(n+1)&&k==0) return puts("NO"),0;
    puts("YES");

    Base=2*max(0,k-1);
    for(int i=1;i<Base;i+=2) Array[i+1]=i,Array[i]=max(0,i-2);
    for(int i=1;i<=n-Base;i++) if(i==1) Array[i+Base]=max(0,Base-1);else Array[i+Base]=(i>>1)+Base;

    if(Check(n-Base+1)&&k) Array[n-1]=Array[n]=2;
    for(int i=1;i<=n;i++) printf("%d ",Array[i]);

    return 0;
}