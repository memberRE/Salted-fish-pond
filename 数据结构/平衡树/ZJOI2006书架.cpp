#include<bits/stdc++.h>
using namespace std;
const int MAX=8e4+30,INF=0x7fffffff;
struct ppp{
	int val,ch[2],size,rand,fa;
}treap[MAX];
int n,m,tot,root,st[MAX],top,pic[MAX];
inline int NEW(int val)
{
	tot++;
	treap[tot].val=val;
	treap[tot].size=1;
	treap[tot].rand=rand();
	return tot;
}
inline void update(int p)
{
	treap[p].size=treap[treap[p].ch[0]].size+treap[treap[p].ch[1]].size+1;
	if(treap[p].ch[0]!=0)
		treap[treap[p].ch[0]].fa=p;
	if(treap[p].ch[1]!=0)
		treap[treap[p].ch[1]].fa=p;
}
inline void split(int now,int &x,int &y,int rank)
{
	if(rank<=0)
	{
		y=now,x=0;
		return ;
	}
	if(rank>=treap[now].size)
	{
		x=now,y=0;
		return ;
	}
	if(treap[treap[now].ch[0]].size>=rank)
	{
		y=now;
		split(treap[now].ch[0],x,treap[now].ch[0],rank);
	}
	else
	{
		x=now;
		split(treap[now].ch[1],treap[now].ch[1],y,rank-treap[treap[now].ch[0]].size-1);
	}
	update(now);
}
inline int merge(int x,int y)
{
	if(x==0 or y==0)
		return x+y;
	if(treap[x].rand<treap[y].rand)
	{
		treap[x].ch[1]=merge(treap[x].ch[1],y);
		update(x);
		return x;
	}
	else
	{
		treap[y].ch[0]=merge(x,treap[y].ch[0]);
		update(y);
		return y;
	}
}
inline int build(int k)
{
	int tem_root;
	scanf("%d",&tem_root);
	tem_root=NEW(tem_root);
	pic[treap[tem_root].val]=tem_root;
	st[++top]=tem_root;
	for(int i=1;i<k;i++)
	{
		int val;
		scanf("%d",&val);
		int p=NEW(val);
		pic[val]=p;
		int last=0;
		while(top and  treap[st[top]].rand>treap[p].rand)
		{
			//treap[p].ch[0]=st[top];
			last=st[top];
			update(st[top]);
			top--;
		}
		treap[p].ch[0]=last;
		if(top)
			treap[st[top]].ch[1]=p;
		else
			tem_root=p;
		st[++top]=p;
		update(p);
	}
	while(top)
	{
		update(st[top]);
		top--;
	}
	return tem_root;
}
inline int find(int p)
{
	int fa=treap[p].fa;
	if(fa==0 or p==0)	return 0;
	int son=treap[fa].ch[1]==p;
	if(son)	return treap[treap[fa].ch[0]].size+1+find(fa);
	else	return find(fa);
}
inline int getrank(int p)
{
	return find(p)+treap[treap[p].ch[0]].size+1;
}
int main()
{
	scanf("%d%d",&n,&m);
	root=build(n);
	for(int i=1;i<=m;i++)
	{
		char s[10];
		int val;
		scanf("%s %d",s,&val);
		if(s[0]=='T')
		{
			int p=pic[val];
			int rank=getrank(p);
			int x,y,z;
			split(root,x,y,rank-1);
			split(y,z,y,1);
			root=merge(merge(z,x),y);
		}
		else if(s[0]=='B')
		{
			int p=pic[val];
			int rank=getrank(p);
			int x,y,z;
			split(root,x,y,rank-1);
			split(y,z,y,1);
			root=merge(merge(x,y),z);
		}
		else if(s[0]=='I')
		{
			int t;
			scanf("%d",&t);
			if(t==0)	continue;
			if(t==1)	t=0;
			
			int p=pic[val];
			int rank=getrank(p);
			int x,y,z,q;
			split(root,x,y,rank-1+t);
			split(y,z,y,1);
			split(y,q,y,1);
			root=merge(merge(x,q),merge(z,y));
		}
		else if(s[0]=='A')
		{
			int p=pic[val];
			int rank=getrank(p);
			printf("%d\n",rank-1);
		}
		else if(s[0]=='Q')
		{
			int x,y,z;
			split(root,x,y,val-1);
			split(y,z,y,1);
			printf("%d\n",treap[z].val);
			root=merge(merge(x,z),y);
		}
	}
	return 0;
}

