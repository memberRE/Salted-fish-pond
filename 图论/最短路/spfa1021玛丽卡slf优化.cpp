#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<deque>
#include<cstdio>
using namespace std;
struct edger
{
	vector<int>v,w;
}pic[30];
deque<int>que;
bool vztd[30];
int d[30],c[30],n,num[30],r[30],x[30];
bool spfa(int s,int a)
{
	memset(d,0x3f,sizeof(d));
	memset(c,0,sizeof(c));
	memset(vztd,0,sizeof(vztd));
	vztd[0]=1;
	que.push_back(s);
	d[s]=0;vztd[s]=1;c[s]++;
	while (!que.empty())
	{
		int x=que.front();que.pop_front();vztd[x]=0;
		for(int i=0;i<pic[x].v.size();i++)
			if(d[x]+pic[x].w[i]<d[pic[x].v[i]] and pic[x].v[i]!=0)
			{
				d[pic[x].v[i]]=d[x]+pic[x].w[i];
				if(!vztd[pic[x].v[i]])
				{
					vztd[pic[x].v[i]]=1;
					c[pic[x].v[i]]++;
					if(!que.empty() and d[pic[x].v[i]]>d[que.front()])
					que.push_back(pic[x].v[i]);
					else 
					que.push_front(pic[x].v[i]);
					if(c[pic[x].v[i]]>n) 
					   return false;
				}
			}
	}
	if(d[24]==a) return true;
		return false;
}
void build(int a)
{	
	pic[24].v.push_back(0);
	pic[24].w.push_back(-a);
	for(int i=1;i<=24;i++)
	{
		pic[i].v.push_back(i-1);
		pic[i].w.push_back(0);
		pic[i-1].v.push_back(i);
		pic[i-1].w.push_back(num[i]);
	}
	for(int i=8;i<=24;i++)
	{
		pic[i].v.push_back(i-8);
		pic[i].w.push_back(-r[i]);
	}
	for(int i=1;i<=7;i++)
	{
		pic[i].v.push_back(i+16);
		pic[i].w.push_back(a-r[i]);
	}
}
int main()
{
	int T;
	cin>>T;
	for(int hjkl=1;hjkl<=T;hjkl++)
	{	int biao=1;  
		for(int i=1;i<=24;i++) cin>>r[i];
		cin>>n;
		for(int i=1;i<=n;i++) 
		{
			int t;
			cin>>t;
			num[t+1]++;
		}
		for(int i=1;i<=n;i++)
		{
			build(i);
			if(spfa(0,i))
			{
				biao=0;
				cout<<i<<endl;
				break;
			}
			for(int i=0;i<=25;i++){
				pic[i].v.clear();
				pic[i].w.clear();
			}
		}
		if(biao) cout<<"No Solution"<<endl;
	}
	return 0;
}
 
