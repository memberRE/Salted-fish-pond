#include<bits/stdc++.h>//xiao gen dui
using namespace std;
const int MAX=1e6+20;
int heap[MAX];
int n,cnt;
void update(int k)
{
	while(k>1)
	{
		if(heap[k]<heap[k>>1])
			swap(heap[k],heap[k>>1]);
		k>>=1;
	}
}
void insert(int k)
{
	cnt++;
	heap[cnt]=k;
	update(cnt);
}
void down(int k)
{
	while((k<<1)<=cnt)
	{
		int son=k<<1;
		if(son+1<=cnt and heap[son+1]<heap[son])	son++;
		if(heap[k]>heap[son])	swap(heap[k],heap[son]);
		else break;
		k=son;
	}
}
void del()
{
	if(cnt==0)	return ;
	heap[1]=heap[cnt];
	cnt--;
	if(cnt==0)	return ;
	down(1);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		if(k==1)
		{
			int m;
			scanf("%d",&m);
			insert(m);
		}
		if(k==2)
			printf("%d\n",heap[1]);
		if(k==3)
			del();
	}
	return 0;
}
