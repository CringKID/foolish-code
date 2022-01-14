#include<cstdio>
#include<iostream>

#define int long long
const int maxn=1e5+10;

int n,m,l,r,a[maxn],fsum[maxn];
bool f;

inline int read(){
	char ch=getchar();int f=1,r=0;
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){r=r*10+ch-'0';ch=getchar();}
	return f*r;
}

signed main(){
	n=read(),m=read();
	for(register int i=1;i<=n;i++){
		a[i]=read()*10000;
		r=std::max(a[i],r);
	}
	while(l<r){
		int mid=(l+r)>>1,Min=0;
		for(register int i=1;i<=n;i++){
			fsum[i]=fsum[i-1]+a[i]-mid;
			if(i>=m){
				Min=std::min(Min,fsum[i-m]);
				if(fsum[i]-Min>=0){
					f=true;
					break ;
				}
			}
		}
		if(f) l=mid+1;
		else r=mid;
		f=false;
	}
	int mid=l,Min=0;
	for(register int i=1;i<=n;i++){//防止mid才是答案
		fsum[i]=fsum[i-1]+a[i]-mid;
		if(i>=m){
			Min=std::min(Min,fsum[i-m]);
			if(fsum[i]-Min>=0){
				f=true;
				break ;
			}
		}
	}
	if(!f) l=mid-1;
	printf("%lld",l/10);
	return 0;
}