#include<bits/stdc++.h>
using namespace std;
const int MAX=5e5+50;
int tree[MAX],sum[MAX],n,m;
int lowbit(int x)
{
	return x& -x;
}
//void build_tree()
//{
//	for(int i=1;i<=n;i++)
//		tree[i]=sum[i]-sum[i-lowbit(i)];
//}
void add(int x,int k)
{
	while(x<=n)
	{
		tree[x]+=k;
		x+=lowbit(x);
	}
}
int qurry(int x)
{
	int ans=0;
	while(x!=0)
	{
		ans+=tree[x];
		x-=lowbit(x);
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&sum[i]);
		sum[i]+=sum[i-1];
	}
	//build_tree();
	for(int i=1;i<=m;i++)
	{
		int k;
		scanf("%d",&k);
		if(k==1)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			add(l,x);
			add(r+1,-x);
		}
		if(k==2)
		{
			int l;
			scanf("%d",&l);
			printf("%d\n",sum[l]-sum[l-1]+qurry(l));
		}
	}
	return 0;
}
