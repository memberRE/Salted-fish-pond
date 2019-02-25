#include<cstdio>
#include<algorithm>
#include<string>
#include<iostream>
#include<cstring>
#include<map>
#include<vector>
#include<cmath>
#define MAX 100005
using namespace std;
struct ppp{
	int v,l,r,fa,disc;
}tree[MAX];
int n,m;
int find(int x)
{
	return tree[x].fa==x?x:find(tree[x].fa);
}
int merge_tree(int a,int b)
{
	if(a==0)	return b;
	if(b==0)	return a;
	if(tree[a].v<tree[b].v)	swap(a,b);
	tree[a].r=merge_tree(tree[a].r,b);
	if(tree[tree[a].r].disc>tree[tree[a].l].disc)	swap(tree[a].l,tree[a].r);
	if(tree[a].r==0)	tree[a].disc=0;
		else			tree[a].disc=tree[tree[a].r].disc+1;
	tree[tree[a].l].fa=a;tree[tree[a].r].fa=a;
	return a;
}
int solve(int x,int y)
{
	ppp a=tree[x],b=tree[y];
/*	tree[tree[x].l].fa=tree[x].l;
	tree[tree[x].r].fa=tree[x].r;
	tree[tree[y].l].fa=tree[y].l;
	tree[tree[y].r].fa=tree[y].r;*/
	merge_tree(tree[x].l,tree[x].r);
	merge_tree(tree[y].l,tree[y].r);
	
	if(tree[tree[x].l].v>tree[tree[x].r].v)
		tree[tree[x].l].fa=tree[x].l;
	else
		tree[tree[x].r].fa=tree[x].r;
	if(tree[tree[y].l].v>tree[tree[y].r].v)
		tree[tree[y].l].fa=tree[y].l;
	else
		tree[tree[y].r].fa=tree[y].r;
	
	merge_tree(find(tree[x].l),find(tree[y].l));
	
	tree[x].l=tree[x].r=tree[y].l=tree[y].r=tree[x].disc=tree[y].disc=0;
	tree[x].v/=2;
	tree[y].v/=2;
	merge_tree(x,find(a.l));
	merge_tree(find(x),y);
	return tree[find(x)].v;
}
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		memset(tree,0,sizeof(tree));
		tree[0].disc=-1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&tree[i].v);
			tree[i].fa=i;
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			
		/*	cout<<"--------------------"<<endl;
			for(int j=1;j<=n;j++)
				cout<<tree[j].v<<" ";
			cout<<endl;
			for(int j=1;j<=n;j++)
				cout<<tree[j].l<<" ";
			cout<<endl;
			for(int j=1;j<=n;j++)
				cout<<tree[j].r<<' ';
			cout<<endl;
			for(int j=1;j<=n;j++)
				cout<<tree[j].fa<<' ';
			cout<<endl<<"----------------------"<<endl;*/
			int h1=find(x),h2=find(y);
			if(h1==h2)
				printf("-1\n");
			else
				printf("%d\n",solve(h1,h2));
			
		}
	}
	return 0;
}

