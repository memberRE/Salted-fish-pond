#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<deque>
#include<cstdio>
using namespace std;
struct edger{
	vector<int> v,w;
}pic[1001];
short ppp[1001][1001];
queue<int> que;
bool vztd[1001];
int d[1001],p[1001],c[1001];
int m,n,mmax=-1;
bool spfa(int s,bool a){
	memset(d,0x3f,sizeof(d));
	memset(c,0,sizeof(c));
	memset(vztd,0,sizeof(vztd));
	vztd[0]=1;
	que.push(s);
	d[s]=0;vztd[s]=1;c[s]++;
	while (!que.empty()){
		int x=que.front();que.pop();vztd[x]=0;
		for(int i=0;i<pic[x].v.size();i++)if(ppp[x][pic[x].v[i]]){
			if(d[x]+pic[x].w[i]<d[pic[x].v[i]] and pic[x].v[i]!=0){
				d[pic[x].v[i]]=d[x]+pic[x].w[i];
				if(a)p[pic[x].v[i]]=x;
				if(!vztd[pic[x].v[i]]){
					vztd[pic[x].v[i]]=1;
					c[pic[x].v[i]]++;
					que.push(pic[x].v[i]);
					if(c[pic[x].v[i]]>n) return false;
				}
			}
		}
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
/*	int i,j;
	for(i=0;i<pic[x].v.size();i++)
	{
		if(pic[x].v[i]==p[x])
		{
		     int a=pic[x].v[i],s=pic[x].w[i],a2,s2;
			 pic[x].v[i]=0;
			 pic[x].w[i]=999999;
			 for(j=0;j<pic[p[x]].v.size();j++)
			 {
			 	if(pic[p[x]].v[j]==x)
				 {
			     a2=pic[p[x]].v[j],s2=pic[p[x]].w[j];
			     pic[p[x]].v[j]=0;
			     pic[p[x]].w[j]=999999;
			     }
			 
			 //for(int j=n;j>=1;j--) cout<<d[j]<<" ";cout<<endl;
			 pic[x].v[i]=a;
			 pic[x].w[i]=s;
			 pic[p[x]].v[j]=a2;
			 pic[p[x]].w[j]=s2;
			 kkk(p[x]);
			 return;
		     }
	    }
	}*/
}
/*	for(int i=0;i<pic[p[x]].v.size();i++){
		if(pic[p[x]].v[i]==x){
			int a=pic[p[x]].v[i],s=pic[p[x]].w[i];
			pic[p[x]].v[i]=0;
			 pic[p[x]].w[i]=10000;
			 spfa(1,0);
			 mmax=max(mmax,d[n]);//for(int j=n;j>=1;j--) cout<<d[j]<<" ";cout<<endl;
			 pic[p[x]].v[i]=a;
			 pic[p[x]].w[i]=s;
			 kkk(p[x]);
			 return;
		}
	}*/

int main(){
	memset(ppp,0,sizeof(ppp));
	int z,x,y;
	cin>>n>>m;
    memset(p,0,sizeof(p));
	for(int i=1;i<=m;i++){
		cin>>x>>y>>z;
		ppp[x][y]=1;
		ppp[y][x]=1;
		pic[x].v.push_back(y);
		pic[x].w.push_back(z);
		pic[y].v.push_back(x);
		pic[y].w.push_back(z);
	}
	spfa(1,1);
	mmax=max(mmax,d[n]);//cout<<" 00main  "<<d[n]<<endl;
	kkk(n);
	cout<<mmax<<endl;
	return 0;
}
 