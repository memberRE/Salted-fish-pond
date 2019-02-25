#include<bits/stdc++.h>
using namespace std;
const int MAX=1e4+3,MAXM=1e5+5,INF=0x7fffffff;
struct ppp{
	int to,next,flow;
}edge[MAXM<<1];
int head[MAX],dep[MAX],gap[MAX],cur[MAX];
int n,m,s,t,tot,maxflow=0;
void add(int u,int v,int w)
{
	edge[tot]=(ppp){v,head[u],w};
	head[u]=tot;
	tot++;
}
void bfs()
{
	memset(dep,-1,sizeof(dep));
	memset(gap,0,sizeof(gap));
	dep[t]=0;
	gap[0]=1;
	queue<int>q;
	q.push(t);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			int v=edge[i].to;
			if(dep[v]!=-1)	continue;
			q.push(v);
			dep[v]=dep[u]+1;
			gap[dep[v]]++;
		}
	}
	return ;
}
inline int dfs(int u,int flow)
{
	if(u==t)
	{
		maxflow+=flow;
		return flow;
	}
	int used=0;
	for(int i=cur[u];i!=-1;i=edge[i].next)
	{
		cur[u]=i;
		int v=edge[i].to;
		if(edge[i].flow and dep[v]+1==dep[u])
		{
			int low=dfs(v,min(flow-used,edge[i].flow));
			if(low)
			{
				edge[i].flow-=low;
				edge[i^1].flow+=low;
				used+=low;
			}
			if(used==flow)	return used;
		}
	}
	gap[dep[u]]--;
	if(gap[dep[u]]==0)	dep[s]=n+1;
	dep[u]++;
	gap[dep[u]]++;
	return used;
}
int isap()
{
	bfs();
	while(dep[s]<n)	
	{
		memcpy(cur,head,sizeof(head));
		dfs(s,INF);
	}
	return maxflow;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(head,-1,sizeof(head));
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,0);
	}
	printf("%d",isap());
	return 0;
}
