#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int dp[11][2],a[12];
int mfs(int pos,int pre,int stat,bool lim)
{
	if(pos==-1)	return 1;
	if(!lim and dp[pos][stat]!=-1)	return dp[pos][stat];
	int up=lim?a[pos]:9;
	int tem=0;
	for(int i=0;i<=up;i++)
	{
		if(i==4)	continue;
		if(pre==6 and i==2)	continue;
		tem+=mfs(pos-1,i,i==6,lim and i==up);
	}
	if(!lim)	dp[pos][stat]=tem;
	return tem;
}
int solve(int k)
{
	int pos=0;
	while(k)
	{
		a[pos]=k%10;
		pos++;
		k/=10;
	}
	return mfs(pos-1,-1,0,1);
}
int main()
{
	memset(dp,-1,sizeof(dp));
	while(1)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a==0 and b==0)
			return 0;
		printf("%d\n",solve(b)-solve(a-1));
	}
	return 0;
}
