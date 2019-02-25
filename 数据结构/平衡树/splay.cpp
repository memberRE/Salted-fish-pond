#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,INF=0x7fffffff;
struct ppp{
	int val,fa,size,cnt;
	int ch[2];//0:left     1:right
}tree[MAX];
int root,n,m,tot;
inline void update(int p)
{
	if(p)
	{
		tree[p].size=tree[p].cnt;
		if(tree[p].ch[0])
		tree[p].size+=tree[tree[p].ch[0]].size;
		if(tree[p].ch[1])
		tree[p].size+=tree[tree[p].ch[1]].size;
	}
}
inline void clear(int p)
{
	tree[p].ch[0]=tree[p].ch[1]=tree[p].fa=tree[p].size=tree[p].val=tree[p].cnt=0;
}
inline int get(int p)
{
	return tree[tree[p].fa].ch[1]==p;
}
inline void rotate(int p)
{
	int fa=tree[p].fa,gfa=tree[fa].fa,son=get(p);
	tree[fa].ch[son]=tree[p].ch[son^1];
	tree[tree[p].ch[son^1]].fa=fa;
	tree[p].fa=gfa;
	tree[p].ch[son^1]=fa;
	tree[fa].fa=p;
	if(gfa)	   tree[gfa].ch[tree[gfa].ch[1]==fa]=p;
	update(p);
	update(fa);
}
inline void splay(int p,int goal=0)
{
	for(int fa;(fa=tree[p].fa)!=goal;rotate(p))
		if(tree[fa].fa!=goal)
			rotate((get(p)==get(fa))? fa:p);
	if(goal==0)
		root=p;
}
inline void insert(int val)
{ 
	if(root==0)
	{
		tot++;
		root=tot;
		tree[tot].cnt=1;
		tree[tot].size=1;
		tree[tot].val=val;
		return ;
	}
	int fa=0,now=root;
	while(1)
	{
		if(tree[now].val==val)
		{
			tree[now].cnt++;
			update(now);
			update(fa);
			splay(now);// use splay to update the size of ancestors_node
			return ;
		}
		fa=now;now=tree[now].ch[val>tree[now].val];
		if(now==0)
		{
			tot++;
			tree[fa].ch[val>tree[fa].val]=tot;
			tree[tot].val=val;
			tree[tot].cnt=tree[tot].size=1;
			tree[tot].fa=fa;
			update(fa);
			splay(tot);
			return;
		}
	}
}
inline int getrank(int val)//you should ensure the existance of the val
{
	int ans=0,now=root;
	while(1)
	{
		if(val<tree[now].val)	now=tree[now].ch[0];
		else
		{
			ans+=tree[tree[now].ch[0]].size;
			if(val==tree[now].val)
			{
				splay(now);
				return ans+1;
			}
			ans+=tree[now].cnt;
			now=tree[now].ch[1];
		}
	}
}
inline int getval(int rank)
{
	int now=root;
	if(rank>tot)	return -INF;
	while(1)
	{
		if(tree[now].cnt+tree[tree[now].ch[0]].size<rank)
		{
			rank-=tree[now].cnt+tree[tree[now].ch[0]].size;
			now=tree[now].ch[1];
		}
		else  if(tree[tree[now].ch[0]].size<rank)
		{
		//	splay(now);		// I don't know if it's necessary.
			return tree[now].val;
		}
		else
			now=tree[now].ch[0];
	}
}

inline int pre()
{
	int now=tree[root].ch[0];
	if(!now)	return -INF;
	while(tree[now].ch[1])	now=tree[now].ch[1];
	return now;
}
inline int next()
{
	int now=tree[root].ch[1];
	if(!now)	return -INF;
	while(tree[now].ch[0])	now=tree[now].ch[0];
	return now;
}

inline void remove(int val)
{
	getrank(val);
	if(tree[root].cnt>1) {tree[root].cnt--;update(root);return ;}
	if(!tree[root].ch[0] and !tree[root].ch[1]){ clear(root);root=tot=0;return ;}
	if(!tree[root].ch[0])
	{
		int orot=root;
		root=tree[root].ch[1];
		clear(orot);
		tree[root].fa=0;
		return;
	}
	else	if(!tree[root].ch[1])
	{
		int orot=root;
		root=tree[root].ch[0];
		clear(orot);
		tree[root].fa=0;
		return;
	}
	int orot=root;
	int leftbig=pre();
	splay(leftbig);
	tree[root].ch[1]=tree[orot].ch[1];
	tree[tree[orot].ch[1]].fa=root;
    clear(orot);
    update(root);
}
int getpre(int val)
{
	insert(val);
	int k=pre();
	remove(val);
	return k;
}
int getnext(int val)
{
	insert(val);
	int k= next();
	remove(val);
	return k;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int opt ,x;
		scanf("%d%d",&opt,&x);
		if(opt ==1)
			insert(x);
		if(opt ==2)
			remove(x);
		if(opt ==3)
			printf("%d\n",getrank(x));
		if(opt ==4)
			printf("%d\n",getval(x));
		if(opt ==5)
			printf("%d\n",tree[getpre(x)].val);
		if(opt ==6)
			printf("%d\n",tree[getnext(x)].val);
	}
	return 0;
}
