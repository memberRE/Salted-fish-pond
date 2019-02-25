#include<iostream>
#include<cstring> 
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;
struct Node
{
	int x,v,w;
	friend bool operator < (Node a,Node b)
	{
		if(a.v!=b.v) return a.v>b.v;
		return a.w>b.w;
	}
}node[10001];
struct E
{
	int b,v,w,next;
}e[10001];
priority_queue<Node>q;
int n,m,head[10001],a,b,c,num=0,k,d;
void e_add(int x,int y,int z,int f)
{
	e[++num].b=y;
	e[num].v=z;
	e[num].w=f;
	e[num].next=head[x];
	head[x]=num;
	return;
}
int dij()
{
	Node p,h;
	p.x=1;p.v=0;p.w=0;q.push(p);
	while(!q.empty())
	{
		p=q.top();q.pop();
		if(p.x==n) return p.v;
		for(int i=head[p.x];i!=-1;i=e[i].next)
		{
			if(k<e[i].w+p.w) continue;
			h.x=e[i].b;
			h.v=e[i].v+p.v;
			h.w=e[i].w+p.w;
			q.push(h);
		}
	}
	return -1;
}
int main()
{
	cin>>k>>n>>m;
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b>>c>>d;
		e_add(a,b,c,d);
	}
	cout<<dij();
	return 0;
}
