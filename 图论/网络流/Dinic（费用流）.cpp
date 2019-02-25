#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN=5e3+3,MAXM=5e4+3,INF=0x7fffffff;
struct ppp{
    long long from,to,flow,next,cost;
}edge[MAXM<<1];
int head[MAXN],tot,n,m,s,t,maxflow,vis;
int dis[MAXN],vztd[MAXN];
LL cost;
void add(int u,int v,int w,int f)
{
    edge[tot]=(ppp){u,v,w,head[u],f};
    head[u]=tot;
    tot++;
}
bool spfa()
{
    memset(vztd,0,sizeof(vztd));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
	vztd[s]=1;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        vztd[k]=0;
        for(int i=head[k];i!=-1;i=edge[i].next)
        {
            int d=edge[i].to;
            if(dis[d]>dis[k]+edge[i].cost and edge[i].flow)
            {
                dis[d]=dis[k]+edge[i].cost;
                if(!vztd[d])
                {
                    q.push(d);
                    vztd[d]=1;
                }
            }
        }
    }
    if(dis[t]!=0x3f3f3f3f)	return 1;
    return 0;
}
int dfs(int u,int flow)
{
    if(u==t)	
    {
        vztd[t]=1;
		maxflow+=flow;
        return flow;
    }
    int used=0;
    vztd[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int d=edge[i].to;
        int lef=edge[i].flow;
        if((vztd[d]==0 or d==t) and lef and dis[d]==dis[u]+edge[i].cost)
        {
            int low=dfs(d,min(flow-used,lef));
            if(low)
            {
                cost+=edge[i].cost*(LL)low;
				used+=low;
                edge[i].flow-=low;
                edge[i^1].flow+=low;
            }
			if(used==flow)	break;
        }
    }
    return used;
}
void dinic()
{
    while(spfa())
    {
    	vztd[t]=1;
    	while(vztd[t])
    	{
    		memset(vztd,0,sizeof(vztd));
    		dfs(s,INF);
		}
	}
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    memset(head,-1,sizeof(head));
    for(int i=1;i<=m;i++)
    {
        int u,v,w,f;
        scanf("%d%d%d%d",&u,&v,&w,&f);
        add(u,v,w,f);
        add(v,u,0,-f);
    }
    dinic();
    printf("%d %d",maxflow,cost);
    return 0;
}
