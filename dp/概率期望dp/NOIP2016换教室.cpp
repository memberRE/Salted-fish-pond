#include<bits/stdc++.h>
using namespace std;
const int MAXN=2010 ;
const double INF=1e17+5;
int n,m,e,v;
int c[MAXN],d[MAXN];
int dis[302][302];
double dp[MAXN][MAXN][2];
double p[MAXN];
int main()
{
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	for(int i=1;i<=n;i++)
		scanf("%lf",&p[i]);
	memset(dis,0x3f,sizeof(dis));
	for(int i=1;i<=v;i++)
		dis[i][i]=0;
	for(int i=1;i<=e;i++)
	{
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		if(dis[a][b]>w)	dis[a][b]=w;
		if(dis[b][a]>w)	dis[b][a]=w;
	}
	for(int k=1;k<=v;k++)
		for(int i=1;i<=v;i++)
			for(int j=1;j<=v;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=v;i++)
		dis[i][i]=dis[i][0]=dis[0][i]=0;
	for(int i=/*1*/0;i<=n;i++)
		for(int j=0;j<=n and j<=m;j++)
			dp[i][j][0]=dp[i][j][1]=INF;
	// the max of j is m;
	dp[1][0][0]=dp[1][1][1]=0;
	for(int i=2;i<=n;i++)
	{
		dp[i][0][0]=dp[i-1][0][0]+dis[c[i-1]][c[i]];
		for(int j=1;j<=i and j<=m;j++)
		{
			dp[i][j][0]=min(dp[i][j][0],min(dp[i-1][j][0]+dis[c[i-1]][c[i]],dp[i-1][j][1]+dis[c[i-1]][c[i]]*(1-p[i-1])+dis[d[i-1]][c[i]]*p[i-1]));
			dp[i][j][1]=min(dp[i][j][1],min(dp[i-1][j-1][0]+dis[c[i-1]][c[i]]*(1-p[i])+dis[c[i-1]][d[i]]*p[i],dp[i-1][j-1][1]+dis[c[i-1]][c[i]]*(1-p[i])*(1-p[i-1])+dis[c[i-1]][d[i]]*(1-p[i-1])*(p[i])+dis[d[i-1]][c[i]]*p[i-1]*(1-p[i])+dis[d[i-1]][d[i]]*p[i]*p[i-1]));
		}
	}
	double ans=INF;
	for(int i=0;i<=n and i<=m;i++)
		ans=min(ans,min(dp[n][i][0],dp[n][i][1]));
	printf("%.2lf",ans);
	return 0;
}
