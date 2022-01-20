#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
struct pp{
	int l,g[3000];//l存长度，g存数字
	pp()//这里一定要初始化
	{
		l=0;
		memset(g,0,sizeof(g));
	}
	void print()
	{
	    for(int i=l-1;i>=0;i--)//输出
                printf("%d",g[i]);
            printf("\n");
	}
}f[10010];
int n;
queue<int>q;//这里就存数组下标了
pp operator +(const pp &a,const pp &b)//重载运算符
{
    pp c;
    c.l=max(a.l,b.l);
    int x=0;
    for(int i=0;i<c.l;i++)//普通高精打法（贴板子）
    {
        c.g[i]=a.g[i]+b.g[i]+x;
        x=c.g[i]/10;
        c.g[i]%=10;
    }
    if(x>0) c.g[++c.l]=x;//进位
    return c;
}
pp operator *(const pp &a,const pp &b)//还是重载运算符
{
    pp c;
    for(int i=0;i<a.l;i++)
    	for(int j=0;j<b.l;j++)
    		c.g[i+j]+=a.g[i]*b.g[j];
    c.l=a.l+b.l-1;
    for(int i=0;i<c.l;i++)
    {        
        c.g[i+1]+=c.g[i]/10;
      	c.g[i]=c.g[i]%10;
    }
    while(c.g[c.l++]);//注意这里的高精计算
    while(!c.g[c.l-1]) c.l--;//同上
    return c;
}
int main()
{
	scanf("%d",&n);
	pp k;
    	int ans,anss;
	k.g[0]=1;
	k.l++;
	for(int i=1;i<=n;i++) q.push(i),f[i]=k;
	while(q.size()!=1)//留下最后的答案
	{
		ans=q.front();
		q.pop();
		anss=q.front();
		q.pop();
		f[ans]=f[ans]*f[anss];
		f[ans]=f[ans]+k;
		q.push(ans);
	}
	ans=q.front();
	f[ans].print();
	return 0;
}