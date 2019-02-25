#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,INF=0x7fffffff;
struct ppp{
	int val,rnd,ch[2],size;// Attention: FHQ-Treap don't have 'cnt'; I don't know the reason;
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
inline void merge(int &now,int x,int y) // the max of x is smaller than y (x<y)
{
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
}
inline void split(int now,int val,int &x,int &y)
{
	if(now==0)
	{
		x=0;y=0;
		return ;
	}
	if(treap[now].val<=val)
	{
		x=now;
		split(treap[now].ch[1],val,treap[x].ch[1],y);
	}
	else
	{
		y=now;
		split(treap[now].ch[0],val,x,treap[y].ch[0]);
	}
	update(now);
}
inline void insert(int val)
{
	int x=0,y=0,z;
	split(root,val,x,y);
	z=NEW(val);
	merge(x,x,z);
	merge(root,x,y);
}
inline void remove(int val)
{
	int x=0,y=0,z=0;
	split(root,val,x,y);
	split(x,val-1,x,z);
	merge(z,treap[z].ch[0],treap[z].ch[1]);
	merge(x,x,z);
	merge(root,x,y);
}
inline int getrank(int val)
{
	int x=0,y=0;
	split(root,val-1,x,y);
	int ans=treap[x].size+1;
	merge(root,x,y);
	return ans;
}
inline int getval(int rank)
{
	int ans=0,now=root;
	while(treap[treap[now].ch[0]].size+1!=rank)
	{
		if(treap[treap[now].ch[0]].size>=rank)
			now=treap[now].ch[0];
		else
			rank-=(treap[treap[now].ch[0]].size+1),now=treap[now].ch[1]; 
	}
	return treap[now].val;
}
inline int getpre(int val)	//you should ensure the existence of the pre and the next
{
	int x,y;
	split(root,val-1,x,y);
	int now=x;
	while(treap[now].ch[1])
		now=treap[now].ch[1];
	merge(root,x,y);
	return now;
}
inline int getnext(int val)
{
	int x,y;
	split(root,val,x,y);
	int now=y;
	while(treap[now].ch[0])
		now=treap[now].ch[0];
	merge(root,x,y);
	return now;
}
inline void init()
{
	NEW(-INF);
	NEW(INF);
	treap[1].ch[1]=2;
	update(1);
	root=1;
}
int main()
{
	int n;
	scanf("%d",&n);
	init();
	for(int i=1;i<=n;i++)
	{
		int opt ,x;
		scanf("%d%d",&opt,&x);
		if(opt ==1)
			insert(x);
		if(opt ==2)
			remove(x);
		if(opt ==3)
			printf("%d\n",getrank(x)-1);
		if(opt ==4)
			printf("%d\n",getval(x+1));
		if(opt ==5)
			printf("%d\n",treap[getpre(x)].val);
		if(opt ==6)
			printf("%d\n",treap[getnext(x)].val);
	}
	return 0;
}
