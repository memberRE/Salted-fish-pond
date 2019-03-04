#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e4+20,MAXM=1e5+20;
int nxt[MAXM<<1],head[MAXN],to[MAXM<<1];
int iscut[MAXN],cutnum,dfn[MAXN],low[MAXN],dfstim;
int m,n,tot;
int dfs(int u,int fa)
{
	int ch=0;// 用于根节点的判断 
	dfn[u]=++dfstim;
	low[u]=dfn[u];
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(!dfn[v])
		{
			ch++;
			int lowv=dfs(v,u);
			low[u]=min(low[u],lowv);
			if(low[v]>=dfn[u])
				iscut[u]=1;
		}
		else 
			if(v!=fa and dfn[v]<dfn[u])
				low[u]=min(low[u],dfn[v]);
	}
	if(fa<0 and ch==1 and iscut[u])	iscut[u]=0;
	return low[u];
}
inline void add(int u,int v)
{
	tot++;
	nxt[tot]=head[u];
	to[tot]=v;
	head[u]=tot;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,-1);
	for(int i=1;i<=n;++i)
		if(iscut[i])
			cutnum++;
	printf("%d\n",cutnum);
	for(int i=1;i<=n;++i)
		if(iscut[i])
			printf("%d ",i);
	return 0;
}
