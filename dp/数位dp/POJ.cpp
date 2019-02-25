#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int num[100],m,dp[51][101];
int hx(int c)
{
	return c+40;
}
int mfs(int pos,int sum,bool lim)
{
	if(!lim and dp[pos][sum]!=-1)	return dp[pos][sum];
	if(pos==-1)	return sum>=40;
	int up=lim?num[pos]:9;
	for(int i=0;i<=up)
}
int solve(int x)
{
	m=0;
	while(x)
	{
		num[n]=x%10;
		x/=10;
		n++;
	}
	return mfs(n-1,40,1);//0-1
}
int main()
{
	int a,b;
	cin>>a>>b;
	memset(dp,-1,sizeof(dp));
	cout<<solve(b)-solve(a-1)<<endl;
	return 0;
}
