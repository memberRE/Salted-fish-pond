#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
struct ppp{
    int next,to;
}edge[1000008];
int head[500008],st[20][1000008],eu[1000008],dp[500008],pos[500008],num=0,nnum=0,gen,n,m,q;
void addedge(int x,int y)
{
    nnum++;
    edge[nnum].to=y;
    edge[nnum].next=head[x];
    head[x]=nnum;
}
int getmin(int x,int y)
{
    return dp[x]>dp[y]?y:x;
}
void dfs(int fa,int u,int deep)
{
    num++;
    if(!pos[u])	pos[u]=num;
    eu[num]=u;
    dp[u]=deep;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        int v=edge[i].to;
        if(v==fa) continue;
            dfs(u,v,deep+1);
            eu[++num]=u;
    }
}
void ST(int k)
{
    for(int i=1;i<=k;i++)
        st[0][i]=eu[i];
    for(int j=1;(1<<j)<=k;j++)
        for(int i=1;i+(1<<j)<=k;i++)
            st[j][i]=getmin(st[j-1][i],st[j-1][i+(1<<j-1)]);
}
int rmq(int l,int r)
{
    int k=trunc(log2(r-l+1));
    return getmin(st[k][l],st[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(pos[u]>pos[v])	swap(u,v);
    return rmq(pos[u],pos[v]);
}
int main()
{
    cin>>n>>m>>gen;
    memset(head,-1,sizeof(head));
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        addedge(x,y);
        addedge(y,x);
    }
    dfs(-1,gen,1);
    ST(2*n-1);
    for(int i=1;i<=m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        printf("%d\n",lca(a,b));
    }
    return 0;
}