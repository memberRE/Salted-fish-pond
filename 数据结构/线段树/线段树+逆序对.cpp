#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAX=500005;
int pic[MAX],n,t[MAX];
struct ppp{
	int l,r,sum;
}tree[MAX<<2];
struct kkl{
	int v,id;
}a[MAX];
bool cam(kkl a,kkl b)
{
	return a.v<b.v;
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
void build_tree(int l,int r,int node)
{
	tree[node].l=l;
	tree[node].r=r;
	if(l==r)	return ;
	int mid=(l+r)>>1;
	build_tree(l,mid,node<<1);
	build_tree(mid+1,r,(node<<1)|1);
}
int findans(int l,int r,int node)
{
	if(l>r)	return 0;
	if(tree[node].l==l and tree[node].r==r)
		return tree[node].sum;
	int mid=tree[node<<1].r;
	if(l>mid)
		return findans(l,r,(node<<1)|1);
	if(r<=mid)
		return findans(l,r,node<<1);
	else
		return findans(l,mid,node<<1)+findans(mid+1,r,(node<<1)|1);
}
void add(int k)
{
	for(int i=1;;)
	{
		if(tree[i].l==tree[i].r)
		{
			tree[i].sum++;
			break;
		}
		tree[i].sum++;
		int mid=tree[i<<1].r;
		if(k<=mid)
			i=i<<1;
		else
			i=(i<<1)|1;
	}
}
int main()
{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].v);
			a[i].id=i;
		}
		discrete();
		build_tree(1,n,1);
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			ans+=findans(t[i]+1,n,1);
			add(t[i]);
		}
//		for(int i=1;i<=n;i++)
//			cout<<t[i]<<' ';
		cout<<ans<<endl;
	return 0;
}
