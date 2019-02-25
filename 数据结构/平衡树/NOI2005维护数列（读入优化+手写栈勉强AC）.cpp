#include<bits/stdc++.h>
using namespace std;
const int MAX=5e5+20,INF=0x7fffffff;
struct ppp{
	int val,ch[2],rnd,sum,lmax,rmax,mmax,size;
	int change,reverse;
}treap[MAX];
int n,m,tot,root,name[MAX],st[MAX];
int read() 
{
    int tmp=0,fh=1; char c=getchar();
    while ((c<'0'||c>'9')&&c!='-') c=getchar();
    if (c=='-') fh=-1,c=getchar();
    while (c>='0'&&c<='9') tmp=tmp*10+c-48,c=getchar();
    return tmp*fh;
}
inline int NEW(int val)
{
	int p=name[tot--];
	treap[p]=(ppp){val,0,0,rand(),0,0,0,0,0,0,0};
	treap[p].val=val;
	treap[p].rnd=rand();
	treap[p].sum=val;
	treap[p].lmax=treap[p].rmax=treap[p].mmax=val;
	treap[p].size=1;
	treap[p].change=INF;
	return p;
}
inline void reuse(int p)
{
	if(!p)	return ;
	name[++tot]=p;
	reuse(treap[p].ch[0]);
	reuse(treap[p].ch[1]);
}
inline void down(int p)
{
	if(p==0)	return;
	if(treap[p].reverse)
	{
		treap[p].reverse=0;
		swap(treap[p].ch[1],treap[p].ch[0]);
		treap[treap[p].ch[0]].reverse^=1;
		treap[treap[p].ch[1]].reverse^=1;
		swap(treap[p].lmax,treap[p].rmax);
	}
	if(treap[p].change!=INF)
	{
		int k=treap[p].change;
		treap[p].change=INF;
		treap[p].rmax=treap[p].mmax=treap[p].lmax=(k>=0? k*treap[p].size:k);
		treap[p].sum=treap[p].size*k;
		treap[p].val=k;
		treap[treap[p].ch[0]].change=k;
		treap[treap[p].ch[1]].change=k;
	}
}
inline void update(int p)
{
	down(treap[p].ch[0]);
	down(treap[p].ch[1]);
	treap[p].sum=treap[p].val+treap[treap[p].ch[0]].sum+treap[treap[p].ch[1]].sum;
	treap[p].size=treap[treap[p].ch[0]].size+treap[treap[p].ch[1]].size+1;
	treap[p].lmax=max(treap[treap[p].ch[0]].lmax,treap[treap[p].ch[0]].sum+treap[p].val+max(0,treap[treap[p].ch[1]].lmax));
	treap[p].rmax=max(treap[treap[p].ch[1]].rmax,treap[treap[p].ch[1]].sum+treap[p].val+max(0,treap[treap[p].ch[0]].rmax));
	treap[p].mmax=max(max(treap[treap[p].ch[0]].mmax,treap[treap[p].ch[1]].mmax),treap[p].val+max(0,treap[treap[p].ch[0]].rmax)+max(0,treap[treap[p].ch[1]].lmax));
}

inline int build(int k)//笛卡尔树的建树方式 按照权值升序插入 O(n) 
{
	int tem_root,top=0;
	tem_root=read();
	tem_root=NEW(tem_root);
	st[++top]=tem_root;
	for(int i=1;i<k;i++)//k-1 次循环 
	{
		int val;
		val=read();
		int p=NEW(val),last=0;
		while(top and treap[st[top]].rnd>treap[p].rnd)//小根堆 
		{
			treap[p].ch[0]=st[top];
			update(st[top]);
			top--;
		}
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
inline void split(int now,int &x,int &y,int rank)
{
	down(now);
	if(rank>=treap[now].size)
	{
		x=now,y=0;
		return ;
	}
	if(rank<=0)
	{
		y=now,x=0;
		return ;
	}
	if(rank<=treap[treap[now].ch[0]].size)
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
	down(x);down(y);
	if(x==0 or y==0)
		return x+y;
	if(treap[x].rnd<treap[y].rnd)
	{
		treap[x].ch[1]=merge(treap[x].ch[1],y);
		update(x);
		update(treap[x].ch[1]);
		return x;
	}
	else
	{
		treap[y].ch[0]=merge(x,treap[y].ch[0]);
		update(y);
		update(treap[y].ch[0]);
		return y;
	}
}
inline void remove(int pos,int num)
{
	int x=0,y=0,z=0;
	split(root,x,y,pos-1);
	split(y,y,z,num);
	reuse(y);
	root=merge(x,z);
}
inline void insert(int pos,int num)
{
	int x,y,z;
	split(root,x,y,pos);
	z=build(num);
	root=merge(merge(x,z),y);
}
inline void make_same(int pos,int num,int c)
{
	int x=0,y=0,z=0;
	split(root,x,y,pos-1);
	split(y,y,z,num);
	treap[y].change=c;
	y=merge(y,z);
	root=merge(x,y);
}
inline void reverse(int pos,int num)
{
	int x=0,y=0,z=0;
	split(root,x,y,pos-1);
	split(y,y,z,num);
	treap[y].reverse^=1;
	y=merge(y,z);
	root=merge(x,y);
}
inline void getsum(int pos,int sum)
{
	int x=0,y=0,z=0;
	split(root,x,y,pos-1);
	split(y,y,z,sum);
	printf("%d\n",treap[y].sum);
	y=merge(y,z);
	root=merge(x,y);
}
inline void maxsum()
{
	printf("%d\n",treap[root].mmax);
}
int main()
{
	//scanf("%d%d",&n,&m);
	n=read();m=read();
	for (int i=500010;i;i--) name[++tot]=i;
	treap[0].lmax=treap[0].rmax=treap[0].mmax=-INF;
	root=build(n);
	char opt[15];
	for(int i=1;i<=m;i++)
	{
		char c=getchar();
		while(c<'A' or c>'Z')	c=getchar();
		opt[0]=c;opt[1]=getchar();opt[2]=getchar();
		while((c>='A' and c<='Z') or c=='-')	c=getchar();
		if(opt[0]=='I')
		{
			int k=read(),jkl=read();
			//scanf("%d%d",&k,&jkl);
			insert(k,jkl);
		}
		else if(opt[0]=='D')
		{
			int  O=read(),P=read();
			//scanf("%d%d",&O,&P);
			remove(O,P);
		}
		else if(opt[2]=='K')
		{
			int  O=read(),P=read(),C=read();
			//scanf("%d%d%d",&O,&P,&C);
			make_same(O,P,C);
		}
		else if(opt[0]=='R')
		{
			int  O=read(),P=read();
			//scanf("%d%d",&O,&P);
			reverse(O,P);
		}
		else if(opt[0]=='G')
		{
			int  O=read(),P=read();
			//scanf("%d%d",&O,&P);
			getsum(O,P);
		}
		else
			maxsum();
	}
	return 0;
}
