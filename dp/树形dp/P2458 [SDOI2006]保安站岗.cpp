#include<iostream>
#include<cstdio>
#include<cstring>//   0 from son  1 from itself   2 from father
#include<algorithm>
#include<vector>
using namespace std;
struct ppp{
	int v;
	vector<int> son;
}tree[1503];
int dp[3][1503],n;
int MIN(int a,int b,int c)
{
	int k=min(a,b);
	return min(k,c);
}
int mfs(int flag,int node)
{
	if(dp[flag][node]!=1061109567)	return dp[flag][node];
	if(flag==2)
	{
		int sum=0;
		for(int i=0;i<tree[node].son.size();i++)
			sum+=min(mfs(0,tree[node].son[i]),mfs(1,tree[node].son[i]));
		int sum2=0;
		for(int i=0;i<tree[node].son.size();i++)
			sum2+=mfs(2,tree[node].son[i]);
		sum2+=tree[node].v;
		dp[flag][node]=min(sum,sum2);
		return dp[flag][node];
	}
	if(flag==1)
	{
		int sum=tree[node].v;
		for(int i=0;i<tree[node].son.size();i++)
			sum+=MIN(mfs(0,tree[node].son[i]),mfs(1,tree[node].son[i]),mfs(2,tree[node].son[i]));
		dp[flag][node]=sum;
		return sum;
	}
	if(flag==0)
	{
		int sum=0,mmin=2000000999,fff=0;
		for(int i=0;i<tree[node].son.size();i++)
		{
			sum+=min(mfs(0,tree[node].son[i]),mfs(1,tree[node].son[i]));
			if(dp[1][tree[node].son[i]]<dp[0][tree[node].son[i]])
				fff=1;
			else
				if(abs(dp[1][tree[node].son[i]]-dp[0][tree[node].son[i]])<mmin)
					mmin=abs(dp[1][tree[node].son[i]]-dp[0][tree[node].son[i]]);
		}
		if(fff==0)
			sum+=mmin;
		dp[flag][node]=sum;
		return sum;
	}
}
int main()
{
	memset(dp,0x3f,sizeof(dp));
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int m,node;
		scanf("%d",&node);
		scanf("%d",&tree[node].v);
		scanf("%d",&m);
		for(int j=1;j<=m;j++)
		{
			int k;
			scanf("%d",&k);
			tree[node].son.push_back(k);
		}
	}
	printf("%d",min(mfs(0,1),mfs(1,1)));
	return 0;
}
