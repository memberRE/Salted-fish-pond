#include<bits/stdc++.h>
#define cl(a) memset(a,0,sizeof(a))
using namespace std;
const int MAX=202;
int n,tot,head[MAX*MAX],to[MAX*MAX],next[MAX*MAX];
int linked[MAX],used[MAX];
void add(int u,int v)
{
	tot++;
	to[tot]=v;
	next[tot]=head[u];
	head[u]=tot;
}
void init()
{
	tot=0;
	for(int i=1;i<=n;i++)	head[i]=0;
	memset(to,0,sizeof(to));
	memset(next,0,sizeof(next));
}
inline int dfs(int u)
{
	for(int i=head[u];i;i=next[i])
	{
		int v=to[i];
		if(!used[v])
		{
			used[v]=1;
			if(!linked[v] or dfs(linked[v]))
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
	int res;
	for(int i=1;i<=n;i++)
	{
		cl(used);
		res+=dfs(i);
	}
	return res;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		init();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				int k;
				scanf("%d",&k);
				if(k)	add(i,j);
			}
		if(km()<n)	printf("No\n");
		else		printf("Yes\n");
	}
	return 0;
}
