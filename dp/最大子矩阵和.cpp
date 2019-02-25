#include<stdio.h>
#include<string.h>
using namespace std;
int n,m/*,pic[502][502]*/,sum[502][502],dp[502],ans=-1000000000;
int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&sum[i][j]);
			sum[i][j]+=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
		}
	for(int i=1;i<=n;i++)//ио╫Г
		for(int j=i;j<=n;j++)//об╫Л 
			{
				int maxx=-1000000000;
				for(int k=1;k<=m;k++)
				{
					int pic=sum[j][k]-sum[i-1][k]-sum[j][k-1]+sum[i-1][k-1];
					dp[k]=max(dp[k-1]+pic,pic);
					maxx=max(dp[k],maxx);
				}
				ans=max(ans,maxx);
			}
	printf("%d",ans);
	return 0;
}
