#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
#include<vector>
#include<cstdio>
using namespace std;
stack<int> s;
int dfn[200001],low[200001],ans=9999999,n,pic[200001],id=1;
bool vztd[200001];
int stap[200001],stop=0;//--------
void tarjan(int u)
{
	dfn[u]=low[u]=++id;
	vztd[u]=1;
	s.push(u);
	//stap[++stop] = u;//--------
	if(!dfn[pic[u]])
	{
		tarjan(pic[u]);
		low[u]=min(low[u],low[pic[u]]);
	}
	else if(vztd[pic[u]]) low[u]=min(low[u],dfn[pic[u]]);
	if(dfn[u]==low[u])
	{  // cout<<s.size()<<endl;
		int b=1;
		while(s.top()!=u)
		{
			b++;
			vztd[s.top()]=0;
			s.pop();
		}
		s.pop();
	/*	for (;stap[stop+1]!=u;stop--)//-------
		{
			vztd[stap[stop]] = false;
			b++;
		}*/
		if(b!=1)
		ans=min(ans,b);	
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)  	scanf("%d",&pic[i]);
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	cout<<ans<<endl;
	return 0;
}