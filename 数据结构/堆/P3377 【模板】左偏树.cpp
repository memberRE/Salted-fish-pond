#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAX 100005
using namespace std;
struct ppp{
	int v,l,r,fa,disc;
}tree[MAX];
int n,m;
int find(int x)// the way should not be ya_suo-ed
{
	return tree[x].fa==x?x:find(tree[x].fa);
}
int merge_tree(int a,int b)
{
	if(a==0)	return b;//if(a==0 or b==0 )	return a+b; 
	if(b==0)	return a;
	if(tree[b].v<tree[a].v)	swap(a,b);
	if(tree[b].v==tree[a].v and a>b)	swap(a,b);
	tree[a].r=merge_tree(tree[a].r,b);
	if(tree[tree[a].r].disc>tree[tree[a].l].disc)	swap(tree[a].l,tree[a].r);
	if(tree[a].r==0)	tree[a].disc=0;
		else			tree[a].disc=tree[tree[a].r].disc+1;
	tree[tree[a].l].fa=a;tree[tree[a].r].fa=a;
	return a;
}
//当堆里有多个最小值时，优先删除原序列的靠前的，否则会影响后续操作1；
void erase(int k)
{
	tree[k].fa=-1;	// k is died
	tree[tree[k].l].fa=tree[k].l;
	tree[tree[k].r].fa=tree[k].r;
	merge_tree(tree[k].l,tree[k].r);
} 
int main()
{
	scanf("%d%d",&n,&m);
	memset(tree,0,sizeof(tree));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&tree[i].v);
		tree[i].fa=i;
	}
	for(int i=1;i<=m;i++)
	{
		int k;
		scanf("%d",&k);
		if(k==1)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			if(tree[x].fa!=-1 and tree[y].fa!=-1 and find(x)!=find(y))
				merge_tree(find(x),find(y));
		}
		if(k==2)
		{
			int x;
			scanf("%d",&x);
			if(tree[x].fa!=-1)
			{
				int k=find(x);
				printf("%d\n",tree[k].v);
				erase(k);
			}	
			else
			printf("-1\n");
		}
	}
	return 0;
}
