#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+3;
struct ppp{
	int x;int y,id;//x 在y中出现了多少次 
}que[MAX];
char pic[MAX];
int trie[MAX][26],local[MAX],fa[MAX],fail[MAX];//local: 编号为y的字符串结尾在trie的那个地方.  fa: father 
int tot,num,kks,N;//num is the ID of string (y);kks is the ID of edges;
int l[MAX],r[MAX];//i的子树范围为l[i]~l[r[i]];  N is the ID of nodes;
queue<int> q;
int head[MAX],next[MAX],to[MAX],bit[MAX],ans[MAX];//bst:树状数组 
bool cam(ppp a,ppp b)
{
	return a.y<b.y;
}
void maketrie()
{
	int len=strlen(pic);
	int now=0;
	for(int i=0;i<len;i++)
	{
		if(pic[i]>='a' and pic[i]<='z')
		{
			int id=pic[i]-'a';
			if(!trie[now][id])
				trie[now][id]=++tot;
			fa[trie[now][id]]=now;
			now=trie[now][id];
		}
		else if(pic[i]=='B')
			now=fa[now];
		else if(pic[i]=='P')
			local[++num]=now;
	}
}
inline void add(int x,int y) //x->y
{//单向边，貌似得改成双向边 
	kks++;
	to[kks]=y;
	next[kks]=head[x];
	head[x]=kks;
}
void makefail()
{
	for(int i=0;i<26;i++)
		if(trie[0][i])
		{
			q.push(trie[0][i]);
			add(0,trie[0][i]);
		}
	while(!q.empty())
	{
		int k=q.front();
		q.pop();
		for(int i=0;i<26;i++)
			if(trie[k][i])
			{
				fail[trie[k][i]]=trie[fail[k]][i];
				q.push(trie[k][i]);
				add(fail[trie[k][i]],trie[k][i]);
			}
			else
				trie[k][i]=trie[fail[k]][i];
	}
}
inline void dfs(int x,int fa)
{
	l[x]=++N;
	for(int i=head[x];i!=-1;i=next[i])
		if(to[i]!=fa)
			dfs(to[i],x);
	r[x]=N;		
}
inline void change(int node,int val)
{
	for(int i=node;i<=N;i+=i&(-i))
		bit[i]+=val;
}
inline int qurry(int node)
{
	int ANS=0;
	for(int i=node;i;i-=i&(-i))
		ANS+=bit[i];
	return ANS;
}
int main()
{
	scanf("%s",pic);
	memset(head,-1,sizeof(head));
	maketrie();
	makefail();
	int m;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&que[i].x,&que[i].y);
		que[i].id=i;
	}
	sort(que+1,que+1+m,cam);
	dfs(0,-1);
	int len=strlen(pic),now=0,k=1,cnt=0;
	for(int i=0;i<len;i++)
	{
		if(pic[i]>='a' and pic[i]<='z')
		{
			int id=pic[i]-'a';
			now=trie[now][id];
			change(l[now],1);
		}
		else if(pic[i]=='B')
		{
			change(l[now],-1);
			now=fa[now];
		}
		else if(pic[i]=='P')
		{
			++cnt;
			if(que[k].y==cnt)
				for(;que[k].y==cnt;k++)
					ans[que[k].id]=qurry(r[local[que[k].x]])-qurry(l[local[que[k].x]]-1);
		}
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
