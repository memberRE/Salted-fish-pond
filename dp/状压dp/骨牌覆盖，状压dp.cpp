#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int m,n,cur;
long long dp[2][(1<<15)];
void check(int a,int b)
{
	if(b&(1<<m)) dp[cur][b^(1<<m)]+=dp[cur^1][a];
}
int main()
{
	while(1)
	{
		cin>>n>>m;
		memset(dp,0,sizeof(dp));
		cur=0;
		if(n<m)	swap(n,m);
		if(n==0 and m==0)	return 0;
		if(n%2 and m%2)		{cout<<"0"<<endl;continue;}
		dp[0][(1<<m)-1]=1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				cur^=1;
				memset(dp[cur],0,sizeof(dp[cur]));
				for(int k=0;k<(1<<m);k++)
				{
					check(k,k<<1);
					if(i!=1 and !(k&(1<<(m-1)))) 	check(k,(k<<1)^(1<<m)^1);
					if(j!=1 and !(k&1))				check(k,(k<<1)^3);
				}
			}
		cout<<dp[cur][(1<<m)-1]<<endl;
	}
	return 0;
}
