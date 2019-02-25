#include<bits/stdc++.h>
using namespace std;
const int MAX=2e3+9;
int head[MAX],to[MAX*MAX],next[MAX*MAX],tot,n,m,e;
int ans=0;
int linked[MAX],used[MAX];
void add(int u,int v)//u->v;
{
	tot++;
	to[tot]=v;
	next[tot]=head[u];
	head[u]=tot;
}
inline int dfs(int u)
{
	for(int i=head[u];i;i=next[i])
	{
		int v=to[i];
		if(!used[v])
		{
			used[v]=true;
			if(linked[v]==-1  or dfs(linked[v]))
			{
				linked[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int km()
{
	int res=0;
	memset(linked,-1,sizeof(linked));
	for(int i=1;i<=n;i++)
	{
		memset(used,0,sizeof(used));
		res+=dfs(i);
	}
	return res;
}
int main()
{
	scanf("%d%d%d",&n,&m,&e);
	for(int i=1;i<=e;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		if(u>=1 and u<=n and v>=1 and v<=m)
			add(u,v+n),add(v+n,u);
	}
	ans=km();
	cout<<ans<<endl;
	return 0;
}
