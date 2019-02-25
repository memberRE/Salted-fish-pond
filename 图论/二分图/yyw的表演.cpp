#include<bits/stdc++.h>
#define cl(a) memset(a,0,sizeof(a))
using namespace std;
const int MAX=1e3+4;
int n,a,b,c,tot[3];
int head[3][MAX],to[3][MAX*MAX],next[3][MAX*MAX],used[MAX],linked[3][MAX];
inline int dfs(int u,int id)
{
	for(int i=head[id][u];i;i=next[id][i])
	{
		int v=to[id][i];
		if(!used[v])
		{
			used[v]=1;
			if(!linked[id][v] or dfs(linked[id][v],id))
			{
				linked[id][v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int km()
{
	int res=0;
	for(int i=1;i<=n;i++)
	{
		cl(used);
		int last[3]={linked[0][i],linked[1][i],linked[2][i]};
		int k1=dfs(i,0);
		if(!k1)	continue;
		cl(used); 
		int k2=dfs(i,1);
		if(!k2)
		{
			linked[0][i]=last[0];
			continue;
		}
		cl(used);
		int k3=dfs(i,2);
		if(!k3)
		{
			linked[0][i]=last[0];
			linked[1][i]=last[1];
			continue;
		}
		res++;
	}
	return res;
}
void add(int u,int v,int id)
{
	tot[id]++;
	to[id][tot[id]]=v;
	next[id][tot[id]]=head[id][u];
	head[id][u]=tot[id];
}
int main()
{
	scanf("%d%d%d%d",&n,&a,&b,&c);
	int ans;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=a;j++)
		{
			int k;
			scanf("%d",&k);
			if(k)
				add(i,j,0);
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=b;j++)
	{
		int k;
		scanf("%d",&k);
		if(k)
			add(i,j,1);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=c;j++)
	{
		int k;
		scanf("%d",&k);
		if(k)
			add(i,j,2);
	}
	ans=km();
	cout<<ans*3<<endl;
	return 0;
}
