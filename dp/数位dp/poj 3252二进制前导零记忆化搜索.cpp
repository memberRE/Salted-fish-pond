#include<iostream>//记忆化搜索不是最好的方法，还是递推对二进制最好 
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int a[102],dp[102][102],num;
int hs(int y)
{
	return y+40;
}
int mfs(int pos,int zmo,bool lim,bool forzero)
{	
	if(pos==-1)	return zmo>=40;
	
	if(!lim  and !forzero and dp[pos][zmo]!=-1)	return dp[pos][zmo];

	int up=lim?a[pos]:1;
	int tmp=0;
	for(int i=0;i<=up;i++)
	{
		if(i==0)
		{
			if(!forzero)
				tmp+=mfs(pos-1,zmo+1,lim and i==up,forzero);
			else
				tmp+=mfs(pos-1,zmo,lim and i==up,forzero);
		}
		if(i==1)
			tmp+=mfs(pos-1,zmo-1,lim and i==up,0);
	}
	if(!lim and !forzero)	dp[pos][zmo]=tmp;
	return tmp;
}
int solve(int x)
{
	num=0;
	while(x)
	{
		a[num]=x&1;
		num++;
		x>>=1;
	}
	return mfs(num-1,hs(0),1,1);
}
int main()
{
	int A,S;
	memset(dp,-1,sizeof(dp));
	cin>>A>>S;
	cout<<solve(S)-solve(A-1)<<endl;
	return 0;
}
