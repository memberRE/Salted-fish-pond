#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=12,MOD=1e9+7;
typedef long long ll;
struct mat{
	ll m[13][13];
}e,a;
ll jkl[13][13]={{0},{0,26,0,0,-2,0,0,0,1,0,0,0,0},{0,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,1},{0,0,0,1},{0,0,0,0,0,26,0,0,-2,0,0,0,1},{0,0,0,0,0,1},{0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,26,0,0,-2},{0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,1},{0,0,0,0,0,0,0,0,0,0,0,1}};
ll /*f[5],g[5]={0,0,0,0,1},*/h[]={0,0,0,0,0,1,0,0,0,26*26*26*26-2,26*26*26,26*26,26};
mat mul(mat x,mat y)
{
	mat c;
	memset(c.m,0,sizeof(c.m));
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			for(int k=1;k<=N;k++)	
				c.m[i][j]=(x.m[i][k]*y.m[k][j]%MOD+c.m[i][j])%MOD;
	return c;
}
mat qpower(mat x,ll y)
{
	mat ans=e;
	while(y)
	{
		if(y&1)
			ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}
int main()
{
	for(int i=1;i<=12;i++)
		e.m[i][i]=1;
	memcpy(a.m,jkl,sizeof(jkl));
	int t,cnt=1;
	scanf("%d",&t);
	while(t--)
	{
		ll y;
		scanf("%lld",&y);
		ll hh=0;
		if(y>4)
		{
			mat ans=qpower(a,y-4);
			for(int i=1;i<=12;i++)
			{
				hh+=(ans.m[1][i]*h[i])%MOD;
				hh%=MOD;
			}
		//	hh+=ans.m[1][5];
		}
		while(hh<0)	hh+=MOD;
		printf("Case #%d: %lld\n",cnt++,hh%MOD);
	}
	return 0;
}    
