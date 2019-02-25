#include<cstdio>
#include<algorithm>
#include<string>
#include<iostream>
#include<cstring>
#include<map>
#include<vector>
#include<cmath>
#define MAX 100002
using namespace std;
typedef long long ll;
struct ppp{
	int l,r;
	ll sum,maxx,lazy;
}tree[MAX*4];
int n,m;
ll pic[MAX];
// the lazy node ,,,  itself's sum has been summed  so he was lazy for his sons
void build_tree(int l,int r,int node)
{
	tree[node].l=l;
	tree[node].r=r;
	if(l==r)
	{
		tree[node].sum=pic[l];
		tree[node].maxx=pic[l];
		tree[node].lazy=0;
		return ;
	}
	int m=(l+r)>>1;
	build_tree(l,m,node<<1);
	build_tree(m+1,r,(node<<1)|1);
	tree[node].sum=tree[node<<1].sum+tree[(node<<1)|1].sum;
	tree[node].maxx=max(tree[node<<1].maxx,tree[(node<<1)|1].maxx);
	tree[node].lazy=0;
}
void add(int l,int r,int x,int node)
{
	tree[node].sum+=x*(r-l+1);
	if(tree[node].l==l and tree[node].r==r)
	{
		if(l!=r)
			tree[node].lazy+=x;
		return ;
	}
	if(tree[node<<1].r>=r)
		add(l,r,x,node<<1);
	else if(tree[(node<<1)|1].l<=l)
		add(l,r,x,(node<<1)|1);
	else
	{
		add(l,tree[node<<1].r,x,node<<1);
        add(tree[(node<<1)+1].l,r,x,(node<<1)|1);
	}
}
ll sear(int l,int r,int node)
{
	if(tree[node].l==l and tree[node].r==r)
		return tree[node].sum;
	if(tree[node].lazy!=0)
	{
		tree[node<<1].sum+=tree[node].lazy*(tree[node<<1].r-tree[node<<1].l+1);
        tree[(node<<1)|1].sum+=tree[node].lazy*(tree[(node<<1)|1].r-tree[(node<<1)|1].l+1);
        if(tree[node<<1].r!=tree[node<<1].l)
            tree[node<<1].lazy+=tree[node].lazy;
        if(tree[(node<<1)|1].r!=tree[(node<<1)|1].l)
            tree[(node<<1)|1].lazy+=tree[node].lazy;
        tree[node].lazy=0;
	}
	if(l>=tree[(node<<1)|1].l)	return sear(l,r,(node<<1)|1);
    if(r<=tree[node<<1].r)		return sear(l,r,node<<1);
    else return sear(l,tree[node<<1].r,node<<1)+sear(tree[(node<<1)|1].l,r,(node<<1)|1);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&pic[i]);
	build_tree(1,n,1);
	for(int i=1;i<=m;i++)
	{
		int k;
		scanf("%d",&k);
		if(k==1)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z,1);
		}
		if(k==2)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",sear(x,y,1));
		}
	}
	return 0;
}
