#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAX=1e6+3,TYPE=26;
	int trie[MAX][TYPE],num[MAX],tot,fail[MAX];
	struct ppp{
		int num,id;
	}pic[MAX];
	bool cam(ppp a,ppp b)
	{
		if(a.num!=b.num)
			return a.num>b.num;
		else
			return a.id<b.id;
	}
	void init()
	{
		memset(trie,0,sizeof(trie));
		memset(num,0,sizeof(num));
		memset(fail,0,sizeof(fail));
		memset(pic,0,sizeof(pic));
		tot=0;
	}
	void readin(char * a,int l)
	{
		int k=strlen(a),now=0;
		for(int i=0;i<k;i++)
		{
			if(!trie[now][a[i]-'a'])
				trie[now][a[i]-'a']=++tot;
			now=trie[now][a[i]-'a'];
		}
		num[now]++;
		pic[now].id=l;
		pic[now].num=0;
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
	void find(char *s)
	{
		int ans=0,p=0;
		for(int i=0;s[i];i++)
		{
			p=trie[p][s[i]-'a'];
			for(int j=p;j;j=fail[j])	pic[j].num+=num[j];
		}
	}

char str[MAX],tem[152][75];
int main()
{
	int k;
	while(scanf("%d",&k)!=EOF)
	{
		if(k==0)	break;
		for(int i=1;i<=k;i++)
		{
			scanf("%s",tem[i]);
			readin(tem[i],i);
		}
		scanf("%s",str);
		getfail();
		find(str);
		sort(pic+1,pic+tot+1,cam);
		for(int i=1;;i++)
		{
			if(i==1)	printf("%d\n",pic[i].num);
			if(i>=2 and pic[i].num!=pic[i-1].num)	break;
			puts(tem[pic[i].id]);
		}
		init();
	}
	return 0;
}
