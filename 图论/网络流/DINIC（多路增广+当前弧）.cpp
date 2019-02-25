#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e4+3,MAXM=1e5+3,INF=0x7fffffff;
struct ppp{
    int from,to,flow,next;
}edge[MAXM<<1];
int head[MAXN],tot,n,m,s,t,maxflow,vis;
int dep[MAXN],vztd[MAXN],cur[MAXN];//cur  µ±Ç°»¡
void add(int u,int v,int w)
{
    edge[tot]=(ppp){u,v,w,head[u]};
    head[u]=tot;
    tot++;
}
bool bfs()
{
    for(int i=1;i<=n;i++)	
        cur[i]=head[i],dep[i]=0x3f3f3f3f,vztd[i]=0;
    dep[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        vztd[k]=0;
        for(int i=head[k];i!=-1;i=edge[i].next)
        {
            int d=edge[i].to,lef=edge[i].flow;
            if(dep[d]>dep[k]+1 and lef)
            {
                dep[d]=dep[k]+1;
                if(!vztd[d])
                {
                    q.push(d);
                    vztd[d]=1;
                }
            }
        }
    }
    if(dep[t]!=0x3f3f3f3f)	return 1;
    return 0;
}
int dfs(int u,int flow)
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
        int d=edge[i].to;
        int lef=edge[i].flow;
        if(lef and dep[d]==dep[u]+1)
        {
            int low=dfs(d,min(flow-used,lef));
            if(low)
            {
                used+=low;
                edge[i].flow-=low;
                edge[i^1].flow+=low;
                if(used==flow)	break;
            }
        }
    }
    return used;
}
int dinic()
{
    while(bfs())
        dfs(s,INF);
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
    printf("%d",dinic());
    return 0;
}
