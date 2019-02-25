#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define il inline
using namespace std;
typedef long long ll;
const int MAX=500005;
int pic[MAX],n,t[MAX],N=1;
int tree[MAX<<2];
struct kkl{
	int v,id;
}a[MAX];
bool cam(kkl a,kkl b)
{
	return a.v<b.v;
}
il void build_tree()
{
	for(;N<=n+1;N<<=1);//换成开区间，所以这里的n要写成n+1; 
						//找到不小于n+1的2的次幂 
}
void discrete()
{
	int cnt=0;
	a[0].v=-1;
	sort(a+1,a+n+1,cam);
	for(int i=1;i<=n;i++)
	{
		if(a[i].v!=a[i-1].v)	t[a[i].id]=cnt+1,cnt++;
		else	t[a[i].id]=cnt;
	}
}
ll findans(int l,int r)
{
	//转化成开区间;s,和t是否是兄弟； 
	ll ans=0;
	for(int s=l+N-1,t=r+N+1;s^t^1;s>>=1,t>>=1)
	{
		if(~s&1)	ans+=tree[s^1];
		if(t&1)		ans+=tree[t^1];
	} 
	return ans;
}
void add(int k)
{
	for(int i=N+k;i>=1;i>>=1)
		tree[i]++;
}
int main()
{
	scanf("%d",&n);build_tree();
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
		a[i].id=i;
	}
	discrete();
	
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		ans+=findans(t[i]+1,n);
		add(t[i]);
	}
	printf("%lld",ans);
	return 0;
}
