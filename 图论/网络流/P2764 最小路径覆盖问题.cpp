#include<bits/stdc++.h>
using namespace std;
const int MAXM=6005,MAX=170,INF=0x7fffffff;
int n,m,tot,s,t;
struct ppp{
	int to,next,flow;
}edge[MAXM<<2];
int head[MAX<<1],dep[MAX<<1],gap[MAX<<1],p[MAX<<1];
int maxflow=0,cur[MAX<<1];
void add(int u,int v,int w)
{
	edge[tot]=(ppp){v,head[u],w};
	head[u]=tot++;
}
void bfs()
{
	memset(dep,-1,sizeof(dep));
	dep[t]=0;
	gap[0]++;
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
			if(flow==used)	return used;
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
void path()
{
	memset(dep,0,sizeof(dep));
	//借用dep来记录路径起点 
	for(int i=1;i<=n;i++)
		p[i]=i;
	for(int i=1;i<=n;i++)
	{
		for(int j=head[i];j!=-1;j=edge[j].next)
		{
			int v=edge[j].to;
			if(edge[j].flow==0 and v>n and v<=n*2)
			{
				p[v-n]=i;
				dep[i]=-1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(dep[i]==-1)	continue;
		int now=i;
		while(p[now]!=now)
		{
			printf("%d ",now);
			now=p[now];
		}
		printf("%d\n",now);
	}
}
int main()
{
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v+n,1);
		add(v+n,u,0);
	}
	s=320,t=321;
	for(int i=1;i<=n;i++)
	{
		add(s,i,1);
		add(i,s,0);
		add(t,i+n,0);
		add(i+n,t,1);
	}
	int ans=n-isap();
	path();
	cout<<ans<<endl;
	return 0;
}
