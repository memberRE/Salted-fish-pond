#include<cstdio>
#include<algorithm>
#include<string>
#include<iostream>
#include<cstring>
#include<map>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
struct ppp{
	int v,to,next;
}pic[500007];
inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=(X<<3)+(X<<1)+c-'0',c=getchar();
    return X*w;
}
struct pp{
	long long sum;
	int node;
	bool operator <(const pp &a) const
	{
		return a.sum<sum;
	}
};
int head[100005],num=0,m,n;
long long d[100005];
bool vztd[100005];
priority_queue<pp>	q;
void add(int x,int y,int z)
{
	num++;
	pic[num].v=z;
	pic[num].to=y;
	pic[num].next=head[x];
	head[x]=num;
}
inline void djstla(int s)
{
	for(int i=1;i<=n;i++)
		d[i]=0x7fffffff;
	memset(vztd,0,sizeof(vztd));
	d[s]=0;
	q.push(pp{0,s});
	while(!q.empty())
	{
		pp k=q.top();
		q.pop();
		int start =k.node;
		if(vztd[start])
			continue;
		vztd[start]=1;
		for(int j=head[start];j;j=pic[j].next)
			if(d[pic[j].to]>d[start]+pic[j].v)
			{
				d[pic[j].to]=d[start]+pic[j].v;
				if(!vztd[pic[j].to])
				q.push(pp{d[pic[j].to],pic[j].to});
			}
	}
}
int main()
{
	int s;
	n=read();m=read();s=read();
	for(register int i=1;i<=m;i++)
	{
		register int x,y,z;
		x=read();y=read();z=read();
		add(x,y,z);
	}
	djstla(s);
	for(register int i=1;i<=n;i++)
		printf("%d ",d[i]);
	return 0;
}
