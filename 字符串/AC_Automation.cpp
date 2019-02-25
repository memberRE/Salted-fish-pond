#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAX=1e6,TYPE=26;
struct ac_automation{
	int trie[MAX][TYPE],num[MAX],tot,fail[MAX];
	void readin(char * a)
	{
		int k=strlen(a),now=0;
		for(int i=0;i<k;i++)
		{
			if(!trie[now][a[i]-'a'])
				trie[now][a[i]-'a']=++tot;
			now=trie[now][a[i]-'a'];
		}
		num[now]++;
	}
	void getfail()
	{
		queue<int> q;
		memset(fail,0,sizeof(fail));
		for(int i=0;i<TYPE;i++)
			if(trie[0][i])
				q.push(trie[0][i]);
		while(!q.empty())
		{
			int k=q.front();
			q.pop();
			for(int i=0;i<TYPE;i++)
				if(trie[k][i])	
				{
					fail[trie[k][i]]=trie[fail[k]][i];
					q.push(trie[k][i]);
				}
				else
					trie[k][i]=trie[fail[k]][i];
		}
	}
	int find(char *s)
	{
		int ans=0,p=0;
		for(int i=0;s[i];i++)
		{
			p=trie[p][s[i]-'a'];
			for(int j=p;j and ~num[j];j=fail[j])	ans+=num[j],num[j]=-1;
		}
		return ans;
	}
}ac; 
char str[MAX],tem[MAX];
int main()
{
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
	{
		scanf("%s",tem);
		ac.readin(tem);
	}
	scanf("%s",str);
	ac.getfail();
	printf("%d",ac.find(str));
	return 0;
}
