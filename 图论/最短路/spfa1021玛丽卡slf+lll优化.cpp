#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<deque>
#include<cstdio>
using namespace std;
struct edger
{
	vector<int> v,w;
}pic[1001];
short ppp[1001][1001];
deque<int> que;
bool vztd[1001];
int d[1001],p[1001],c[1001];
int m,n,mmax=-1;
double mid=0.0; 
bool spfa(int s,bool a)
{
	memset(d,0x3f,sizeof(d));
	memset(c,0,sizeof(c));
	memset(vztd,0,sizeof(vztd));
	vztd[0]=1;
	que.push_back(s);
	d[s]=0;vztd[s]=1;c[s]++;
	while (!que.empty())
	{	
		while(d[que.front()]>mid)//lll
		{
			que.push_back(que.front());
			que.pop_front();
		}
		int x=que.front();que.pop_front();vztd[x]=0;
		mid=mid*(que.size()+1)-d[x];//lll
		for(int i=0;i<pic[x].v.size();i++)
		if(ppp[x][pic[x].v[i]])
		{
			if(d[x]+pic[x].w[i]<d[pic[x].v[i]] and pic[x].v[i]!=0)
			{
				d[pic[x].v[i]]=d[x]+pic[x].w[i];
				if(a)p[pic[x].v[i]]=x;
				if(!vztd[pic[x].v[i]])
				{
					vztd[pic[x].v[i]]=1;
					c[pic[x].v[i]]++;
					if(!que.empty() and d[pic[x].v[i]]>d[que.front()])//slf
					que.push_back(pic[x].v[i]);
					else 
					que.push_front(pic[x].v[i]);
					mid+=d[pic[x].v[i]];//lll
					if(c[pic[x].v[i]]>n) return false;
				}
			}
		}
		if(!que.empty())mid=(mid+1)/que.size();//lll
	}
	return true;
}
void kkk(int x)
{
    if(x==1) return;
	ppp[x][p[x]]=0;
	ppp[p[x]][x]=0;
	spfa(1,0);
	mmax=max(mmax,d[n]);
	ppp[x][p[x]]=1;
	ppp[p[x]][x]=1;
	kkk(p[x]);
	return;
}
int main()
{
	memset(ppp,0,sizeof(ppp));
	int z,x,y;
	cin>>n>>m;
    memset(p,0,sizeof(p));
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		ppp[x][y]=1;
		ppp[y][x]=1;
		pic[x].v.push_back(y);
		pic[x].w.push_back(z);
		pic[y].v.push_back(x);
		pic[y].w.push_back(z);
	}
	spfa(1,1);
	mmax=max(mmax,d[n]);
	kkk(n);
	cout<<mmax<<endl;
	return 0;
}
 
