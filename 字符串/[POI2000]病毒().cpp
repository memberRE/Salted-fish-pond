#include<bits/stdc++.h>
using namespace std;
const int MAX=3e4+4;
char s[MAX];
int trie[MAX][2],tot,fail[MAX];
bool vztd[MAX],danger[MAX],flag=0,f[MAX];
void build(char* t)
{
	int now=0;
	for(int i=0;t[i];i++)
	{
		int id=t[i]-'0';
		if(!trie[now][id])	trie[now][id]=++tot;
		now=trie[now][id];
	}
	danger[now]=1;
}
void getfail()
{
	queue<int>q;
	for(int i=0;i<=1;i++)
		if(trie[0][i])
			q.push(trie[0][i]);
	while(!q.empty())
	{
		int k=q.front();
		q.pop();
		for(int i=0;i<2;i++)
		{
			
			if(danger[fail[k]])	danger[k]=1;
			if(trie[k][i])
			fail[trie[k][i]]=trie[fail[k]][i],q.push(trie[k][i]);
			else
			trie[k][i]=trie[fail[k]][i];
			if(danger[fail[trie[k][i]]])	danger[trie[k][i]]=1;
		}
	}
}
void dfs(int node)
{
	vztd[node]=1;
	for(int i=0;i<2;i++)
	{
		int k=trie[node][i];
		if(vztd[k])
		{
			printf("TAK");
			exit(0);
		}
		else if(!danger[k] and !f[k])
		{
			f[k]=1;
			dfs(k);
		}
	}
	vztd[node]=0;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s);
		build(s);	
	}
	getfail();
	dfs(0);
	printf("NIE");
	return 0;
}
