#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring> 
using namespace std;
int dp[12][5000],a[12],num,fa,x[12]={1,2,4,8,16,32,64,128,256,512,1024,2048};
void f(int k)
{
	fa=0;
	int cnt=0;
	while(k)
	{
		fa+=(k%10)*x[cnt];
		k/=10;
		cnt++;
	}
}
int mfs(int pos,int lefsum,bool lim)
{
	if(lefsum<0)	return 0;
	if(pos==-1 )	return lefsum>=0;
	if(!lim and dp[pos][lefsum]!=-1)	return dp[pos][lefsum];
	int up=lim?a[pos]:9;
	int tem=0;
	for(int i=0;i<=up;i++)
	{
		tem+=mfs(pos-1,lefsum-i*x[pos],lim and i==up);
//		if(tem==2)
//		cout<<pos-1<<" "<<lefsum-i*x[pos]<<"  "<<(lim and i==up)<<" "<<mfs(pos-1,lefsum-i*x[pos],lim and i==up)<<endl;
	} 	
	if(!lim)	dp[pos][lefsum]=tem;
	return tem;
} 
void find(int x)
{
	num=0;
	while(x)
	{
		a[num]=x%10;
		x/=10;
		num++;
	}
}//////all  begin from zero  0000!!!!!
int solve(int b)
{
	find(b);
	return mfs(num-1,fa,1);
}
int main()
{
	int t;
	cin>>t;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=t;i++)
	{	
		int A,b;
		scanf("%d%d",&A,&b);
		f(A);
		memset(a,0,sizeof(a));
		printf("Case #%d: %d\n",i,solve(b));
	}
	return 0;
}
