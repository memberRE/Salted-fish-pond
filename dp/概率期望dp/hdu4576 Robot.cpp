#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,l,r;
double dp[202][2];
inline int id(int k)
{
	while(k>n)
		k-=n;
	while(k<=0)
		k+=n;
	return k;
}
int main()
{
	while(1)
	{
		scanf("%d%d%d%d",&n,&m,&l,&r);
		if(n==0 and m==0 and l==0 and r==0)
			break;
		memset(dp,0,sizeof(dp));
		dp[1][0]=1.0;
		int cnt=0;
		for(int i=1;i<=m;i++)
		{
			int k;
			scanf("%d",&k);
			for(int j=1;j<=n;j++)
				dp[j][cnt^1]=dp[id(j-k)][cnt]*0.5+dp[id(j+k)][cnt]*0.5;
			cnt^=1;
		}
		double ans=0.0;
		if(l>r)	swap(l,r);
		for(int i=l;i<=r;i++)
			ans+=dp[i][cnt];
		printf("%.4lf\n",ans);
	}
	return 0;
}
