#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,INF=0x7fffffff;
struct ppp{
	int val,rnd,ch[2],size,lazy;// Attention: FHQ-Treap don't have 'cnt'; I don't know the reason;
}treap[MAX];
int root ,tot,n,m;
inline int NEW(int val)
{
	tot++;
	treap[tot].val=val;
	treap[tot].rnd=rand();
	treap[tot].size=1;
	return tot;
}
inline void update(int p)
{
	treap[p].size=treap[treap[p].ch[1]].size+treap[treap[p].ch[0]].size+1;
}
inline void pushdown(int p)
{
	if(p and treap[p].lazy)
	{
		swap(treap[p].ch[0],treap[p].ch[1]);
		if(treap[p].ch[0])
			treap[treap[p].ch[0]].lazy^=1;
		if(treap[p].ch[1])
			treap[treap[p].ch[1]].lazy^=1;
		treap[p].lazy=0;
	}
}
inline void merge(int &now,int x,int y) // the max of x is smaller than y (x<y)
{
	pushdown(x);
	pushdown(y);
	pushdown(now); 	
	if(x==0 or y==0)
	{
		now=x+y;
		return ;
	}
	if(treap[x].rnd<treap[y].rnd)//Î¬»¤Ð¡¸ù¶Ñ 
	{
		now=x;
		merge(treap[now].ch[1],treap[x].ch[1],y);
	}
	else
	{
		now=y;
		merge(treap[now].ch[0],x,treap[y].ch[0]);
	}
	update(now);
	pushdown(now);
}
inline void split(int now,int rank,int &x,int &y)
{
	pushdown(now);
	if(now==0 )
	{
		x=0;y=0;
		return ;
	}
	if(rank==0)
	{
		x=0,y=now;
		return ;
	}
	if(rank>=treap[now].size)
	{
		y=0,x=now;
		return;
	}
	if(treap[treap[now].ch[0]].size+1<=rank)
	{
		x=now;
		split(treap[now].ch[1],rank-treap[treap[now].ch[0]].size-1,treap[x].ch[1],y);
	}
	else
	{
		y=now;
		split(treap[now].ch[0],rank,x,treap[y].ch[0]);
	}
	update(now);
	pushdown(now);
}
inline void print(int p)
{
	pushdown(p);
	if(treap[p].ch[0])
		print(treap[p].ch[0]);
	if(abs(treap[p].val)!=INF)
		printf("%d ",treap[p].val);
	if(treap[p].ch[1])
		print(treap[p].ch[1]);
}
inline void insert(int val)
{
	int x=0,y=0,z;
	split(root,val,x,y);
//	debug(x);debug(y);
	z=NEW(val);
	merge(x,x,z);
	merge(root,x,y);
}
inline void init()
{
	NEW(-INF);
	NEW(INF);
	treap[1].ch[1]=2;
	update(1);
	root=1;
}

inline void reverse(int l,int r)
{
	int a,b,c;
	split(root,l-1,a,b);
//	debug(a);debug(b);
	split(b,r-l+1,b,c);
//	debug(b);debug(c);
	treap[b].lazy^=1;
	merge(b,b,c);
	merge(root,a,b);
}

int main()
{
	int n;
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=n;i++)
		insert(i);
	for(int i=1;i<=m;i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		reverse(l+1,r+1);
	}
	print(root);
	return 0;
}
