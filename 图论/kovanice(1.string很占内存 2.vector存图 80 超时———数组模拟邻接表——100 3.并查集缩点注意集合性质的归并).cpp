#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
//vector<int>pic[300001];
//vector<int>npic[300001];
struct E
{
	int next,x,y;
}e[300001];
struct nE
{
	int next,x,y;
}ne[300001];
int n,m,t,f[300001],vis[300001],nvis[300001],chil[300001],fa[300001],ans[300001],head[300001],nhead[300001],num=0,nnum=0;
void add_e(int a,int b)
{
	e[++num].x=a;
	e[num].y=b;
	e[num].next=head[a];
	head[a]=num;
	return;
}
void add_ne(int a,int b)
{
	ne[++nnum].x=a;
	ne[nnum].y=b;
	ne[nnum].next=nhead[a];
	nhead[a]=nnum;
	return;
}
int find(int u)
{
	if(f[u]==u) return u;
	return f[u]=find(f[u]);
}
void dfs(int u)
{
    int v;
	vis[u]=1;
	/*for(int i=0;i<pic[u].size();i++)
	{
		v=pic[u][i];
		if(!vis[v]) dfs(v);
		chil[u]=max(chil[u],chil[v]+1);
	}*/
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		v=find(e[i].y);
		if(!vis[v]) dfs(v);
		chil[u]=max(chil[u],chil[v]+1);
	}
	return;
}
void ndfs(int u)
{
	int v;
	nvis[u]=1;
	/*for(int i=0;i<npic[u].size();i++)
	{
		v=npic[u][i];
		if(!nvis[v]) ndfs(v);
		fa[u]=max(fa[u],fa[v]+1);
	}*/
	for(int i=nhead[u];i!=-1;i=ne[i].next)
	{
		v=find(ne[i].y);
		if(!nvis[v]) ndfs(v);
		fa[u]=max(fa[u],fa[v]+1);
	}
	return;
}
int main()
{
	freopen("kovanice.in","r",stdin);
	freopen("kovanice.out","w",stdout);
	string a;
	char s;
	int x,y,j,l;
	cin>>n>>m>>t;
	memset(vis,0,sizeof(vis));
	memset(nvis,0,sizeof(nvis));
	memset(chil,0,sizeof(chil));
	memset(ans,0,sizeof(ans));
	memset(fa,0,sizeof(fa));
	memset(head,-1,sizeof(head));
	memset(nhead,-1,sizeof(nhead));
	for(int i=1;i<=m;i++) f[i]=i;
	for(int i=1;i<=t;i++)
	{
		cin>>a;
		x=0;y=0;j=0;
		while(a[j]>='0'&&a[j]<='9')
		{
			x=x*10+a[j]-'0';
			j++;
		}
		s=a[j++];
	    while(j<a.size()&&a[j]>='0'&&a[j]<='9')
		{
			y=y*10+a[j]-'0';
			j++;
		}
		if(s=='=') f[find(y)]=find(x);
		if(s=='>')
		{
			add_e(x,y);
			add_ne(y,x);
			//pic[x].push_back(y);
			//npic[y].push_back(x);
		}
		if(s=='<')
		{
			add_e(y,x);
			add_ne(x,y);
			//pic[y].push_back(x);
			//npic[x].push_back(y);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(f[i]!=i)
		{
			l=find(i);
			for(int r=head[i];r!=-1;r=e[r].next) add_e(l,e[r].y);
			for(int r=nhead[i];r!=-1;r=ne[r].next) add_ne(l,ne[r].y);
			//for(int r=0;r<pic[i].size();r++) pic[l].push_back(pic[i][r]);
			//for(int r=0;r<npic[i].size();r++) npic[l].push_back(npic[i][r]);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(f[i]==i)
		{
			if(!vis[i]) dfs(i);
			if(!nvis[i]) ndfs(i);
			if(chil[i]+fa[i]==n-1) ans[i]=chil[i]+1; 
		}
	}
	for(int i=1;i<=m;i++)
		cout<<ans[i]<<endl;
//	for(int i=1;i<=m;i++)
//	{
//		l=find(i);
//		if(ans[l]) cout<<"K"<<ans[l]<<endl;
//		else cout<<"?"<<endl;
//	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
