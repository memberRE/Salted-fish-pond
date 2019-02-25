#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+5,INF=0x7fffffff;
struct ppp{
	int val,l,r,size,cnt,rnd;
}treap[MAX];
int root=1,tot;
inline int NEW(int v)
{
	tot++;
	treap[tot].val=v;
	treap[tot].size=treap[tot].cnt=1;
	treap[tot].rnd=rand();
	return tot;
}
inline void update(int p)
{
	treap[p].size=treap[treap[p].l].size+treap[treap[p].r].size+treap[p].cnt;
}
void init()
{
	NEW(-INF);
	NEW(INF);
	root=1;
	treap[1].r=2;
	update(root);
}
inline void zag(int &p)//left
{
	int r=treap[p].r;
	treap[p].r=treap[r].l;
	treap[r].l=p;
	p=r;
	update(treap[p].l);
	update(p);
}
inline void zig(int &p)//right
{
	int l=treap[p].l;
	treap[p].l=treap[l].r;
	treap[l].r=p;
	p=l;
	update(treap[p].r);
	update(p);
}

inline void insert(int &p,int val)
{
	if(p==0)
	{
		p=NEW(val);
		return ;
	}
	if(treap[p].val==val)
	{
		treap[p].cnt++;
		update(p);
		return ;
	}
	if(treap[p].val>val)
	{
		insert(treap[p].l,val);
		if(treap[p].rnd<treap[treap[p].l].rnd)	zig(p);
	}
	else
	{
		insert(treap[p].r,val);
		if(treap[p].rnd<treap[treap[p].r].rnd)	zag(p);
	}
	update(p);
}
inline void remove(int &p,int val)
{
	if(p==0)	return ;
	if(treap[p].val==val)
	{
		if(treap[p].cnt>1)
		{
			treap[p].cnt--;
			update(p);
			return ;
		}
		if(treap[p].r or treap[p].l)
		{
			if(treap[p].r==0 or treap[treap[p].l].rnd>treap[treap[p].r].rnd)
			{
				zig(p);
				remove(treap[p].r,val);
			}
			else
			{
				zag(p);
				remove(treap[p].l,val);
			}
			update(p);
		}
		else
			p=0;
		return;
	}
	val < treap[p].val ? remove(treap[p].l,val) : remove(treap[p].r,val);
	update(p);
}
inline int getrank(int p,int val)
{
	if(p==0)	return 0;
	if(val==treap[p].val)	return treap[treap[p].l].size+1;
	if(val<treap[p].val)	return getrank(treap[p].l,val);
	return getrank(treap[p].r,val)+treap[treap[p].l].size+treap[p].cnt;
}
inline int getval(int &p,int rank)
{
	if(p==0)	return INF;
	if(treap[treap[p].l].size>=rank)	return getval(treap[p].l,rank);
	if(treap[treap[p].l].size+treap[p].cnt>=rank)	return treap[p].val;
	return getval(treap[p].r,rank-treap[treap[p].l].size-treap[p].cnt);
}
inline int getpre(int val)
{
	int ans=1;// a[1]=-INF  旋转操作不会改变a[1]!!!
	int p=root;
	while(p)
	{
		if(treap[p].val==val)
		{
			if(treap[p].l>0)
			{
				p=treap[p].l;
				while(treap[p].r>0)	p=treap[p].r;
				ans=p;
			}
			break;
		}
		if(treap[p].val< val and treap[p].val > treap[ans].val)	ans=p;
		p=val<treap[p].val ? treap[p].l : treap[p].r;
	} 
	return treap[ans].val;
}
inline int getnext(int val)
{
	int ans=2;// a[2]=INF  旋转操作不会改变a[1]!!!
	int p=root;
	while(p)
	{
		if(treap[p].val==val)
		{
			if(treap[p].r>0)
			{
				p=treap[p].r;
				while(treap[p].l>0)	p=treap[p].l;
				ans=p;
			}
			break;
		}
		if(treap[p].val> val and treap[p].val < treap[ans].val)	ans=p;
		p=val<treap[p].val ? treap[p].l : treap[p].r;
	} 
	return treap[ans].val;
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
			insert(root,x);
		if(opt ==2)
			remove(root,x);
		if(opt ==3)
			printf("%d\n",getrank(root,x)-1);//多了一个-INF 
		if(opt ==4)
			printf("%d\n",getval(root,x+1));
		if(opt ==5)
			printf("%d\n",getpre(x));
		if(opt ==6)
			printf("%d\n",getnext(x));
	}
	return 0;
}
