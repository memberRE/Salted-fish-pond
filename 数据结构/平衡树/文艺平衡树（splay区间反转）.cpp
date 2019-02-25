#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,INF=0x7fffffff; 
int pic[MAX],n,m,root,tot;
struct ppp{
	int val,fa,size,cnt,ch[2];
	int lazy;//cnt is not necessary in this problem
}tree[MAX];
inline int get(int p)
{
	return tree[tree[p].fa].ch[1]==p;
}
inline void update(int p)
{
	tree[p].size=tree[p].cnt+tree[tree[p].ch[1]].size;
	tree[p].size+=tree[tree[p].ch[0]].size;
}
inline void pushdown(int p)
{
	if(p and tree[p].lazy)
	{
		swap(tree[p].ch[0],tree[p].ch[1]);
		if(tree[p].ch[0])
			tree[tree[p].ch[0]].lazy^=1;
		if(tree[p].ch[1])
			tree[tree[p].ch[1]].lazy^=1;
		tree[p].lazy=0;
	}
}
inline void rotate(int p)
{
	int fa=tree[p].fa,grdfa=tree[fa].fa;
	int son=get(p);
	tree[fa].ch[son]=tree[p].ch[son^1];
	tree[tree[p].ch[son^1]].fa=fa;
	tree[p].fa=grdfa;
	tree[p].ch[son^1]=fa;
	tree[fa].fa=p;
	if(grdfa)	tree[grdfa].ch[tree[grdfa].ch[1]==fa]=p;
	update(fa);
	update(p);
}
inline void splay(int p,int goal=0)
{
	for(int fa;(fa=tree[p].fa)!=goal;rotate(p))
		if(tree[fa].fa!=goal)
			rotate(get(p)==get(fa)? fa:p);
	if(goal==0)
		root=p;
}
inline int build(int l,int r,int fa)
{
	if(l>r)	return 0;
	int mid=(l+r)>>1;
	tot++;
	int now=tot;
	tree[now].cnt=tree[now].size=1;
	tree[now].val=pic[mid];//此处可以改成原数组的指针 
	tree[now].fa=fa;
	tree[now].ch[0]=build(l,mid-1,now);
	tree[now].ch[1]=build(mid+1,r,now);
	update(now);
	return now;
}
inline int find(int k)//kth
{
	int now=root;
	while(1)
	{
		pushdown(now);
		if(k<=tree[tree[now].ch[0]].size)
			now=tree[now].ch[0];
		else// no need to think about cnt (cnt=1)
		{
			k-=(tree[tree[now].ch[0]].size+1);
			if(!k)	return now;
			now=tree[now].ch[1];
		}
	}
}
inline void reverse(int l,int r)// think of the -INF while using this function
{
	l=find(l-1);
	r=find(r+1);
	splay(l,0);
	splay(r,l);
	tree[tree[tree[root].ch[1]].ch[0]].lazy^=1;
}
inline void print(int p)
{
	pushdown(p);
	if(tree[p].ch[0])
		print(tree[p].ch[0]);
	if(abs(tree[p].val)!=INF)
		printf("%d ",tree[p].val);
	if(tree[p].ch[1])
		print(tree[p].ch[1]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		pic[i]=i;
	pic[0]=-INF;pic[n+1]=INF;
	build(0,n+1,0);
	root=1;
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		reverse(l+1,r+1);
	}
	print(root);
	return 0;
}
