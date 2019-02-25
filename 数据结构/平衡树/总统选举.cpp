#include<bits/stdc++.h>
using namespace std;
const int MAX=5e5+2;
struct ppp{
	int cnt,cand;
}tree[MAX<<2];
struct iop{
	int val,ch[2],size,rnd;
}treap[MAX<<1];
int root[MAX],tot,n,m,pic[MAX],modify[MAX<<1];//pic 先用于储存原图，后用于存取线段树节点编号 
inline void up(int node)
{
	if(tree[node<<1].cand==tree[(node<<1)|1].cand)
	{
		tree[node].cand=tree[node<<1].cand;
		tree[node].cnt=tree[node<<1].cnt+tree[(node<<1)|1].cnt;
	}
	else
	{
		if(tree[node<<1].cnt>=tree[(node<<1)|1].cnt) 
			tree[node].cnt=tree[node<<1].cnt-tree[(node<<1)|1].cnt,tree[node].cand=tree[node<<1].cand;
        else 
			tree[node].cnt=tree[(node<<1)|1].cnt-tree[node<<1].cnt,tree[node].cand=tree[(node<<1)|1].cand;
	}
}
void build(int node,int l,int r)
{
	if(l==r)
	{
		tree[node].cand=pic[l];
		tree[node].cnt=1;
		pic[l]=node;
		return;
	}
	else
	{
		int mid=(l+r)>>1;
		build(node<<1,l,mid);
		build((node<<1)|1,mid+1,r);
		up(node);
	}
}
inline ppp find(int node,int l,int r,int L,int R)
{
	int mid=(L+R)>>1;
	if(l==L and r==R)	return tree[node];
	if(r<=mid)
		return find(node<<1,l,r,L,mid);
	else if(l>mid)
		return find((node<<1)|1,l,r,mid+1,R);
	else
	{
		ppp a=find(node<<1,l,mid,L,mid);
		ppp b=find((node<<1)|1,mid+1,r,mid+1,R);
		ppp c;
		if(a.cand==b.cand)	
			c.cnt=a.cnt+b.cnt,c.cand=a.cand;
		else
		{
			if(a.cnt>=b.cnt) c.cnt=a.cnt-b.cnt,c.cand=a.cand;
            else c.cnt=b.cnt-a.cnt,c.cand=b.cand;
		}
		return c;
	}
}
inline void update(int p)
{
	treap[p].size=treap[treap[p].ch[0]].size+treap[treap[p].ch[1]].size+1;
}
inline int NEW(int val)
{
	tot++;
	treap[tot]=(iop){val,0,0,1,rand()};
	return tot;
}
inline int merge(int x,int y)
{
	if(x==0 or y==0 )
		return x+y;
	if(treap[x].rnd<treap[y].rnd)
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
inline void split(int now,int &x,int &y,int val)
{
	if(now==0)
	{
		x=0,y=0;
		return ;
	}
	if(treap[now].val<=val)
	{
		x=now;
		split(treap[now].ch[1],treap[now].ch[1],y,val);
	}
	else
	{
		y=now;
		split(treap[now].ch[0],x,treap[now].ch[0],val);
	}
	update(now);
}
inline bool check(int l,int r,int cad)
{
	if(root[cad]==0)
		return false;
	int x,y,z;
	split(root[cad],x,y,l-1);
	split(y,y,z,r); 
	bool ans=(treap[y].size<<1)>(r-l+1);
	root[cad]=merge(merge(x,y),z);
	return ans;
}
inline void change(int voter,int cad)
{
	//------------------------------treap
	int ori=tree[pic[voter]].cand;
	int x,y,z;
	split(root[ori],x,y,voter-1);
	split(y,y,z,voter);
	root[ori]=merge(x,z);
	split(root[cad],x,z,voter-1);
	root[cad]=merge(merge(x,y),z);
	//-----------------------------segment_tree
	int node=pic[voter];
	tree[node].cand=cad;
	node>>=1;
	while(node)
	{
		up(node);
		node>>=1;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&pic[i]);
		int p=NEW(i);
		if(!root[pic[i]])
			root[pic[i]]=p;
		else
			root[pic[i]]=merge(root[pic[i]],p);
	}
	build(1,1,n);
	for(int i=1;i<=m;i++)
	{
		int l,r,s,k;
		scanf("%d%d%d%d",&l,&r,&s,&k);
		for(int j=1;j<=k;j++)
			scanf("%d",&modify[j]);
		int cad=find(1,l,r,1,n).cand;
		if(check(l,r,cad))	
			s=cad;
		for(int j=1;j<=k;j++)
			change(modify[j],s);
		printf("%d\n",s);
	}
	int winner=-1;
	for(int i=1;i<=n;i++)
		if((treap[root[i]].size<<1)>n)	winner=i;
	printf("%d",winner);
	return 0;
}
