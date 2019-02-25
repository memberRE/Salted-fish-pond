#include<bits/stdc++.h>
using namespace std;
const int MAX=3e5+100,INF=0x7fffffff;
struct ppp{
    int ch[2],rnd,size,l,r,fa;
}treap[MAX];
map<int,int> f;
int n,m,a,tot,root,lnow=INF,cnt=0;
 void update(int p)
{
    treap[p].size=treap[treap[p].ch[0]].size+treap[treap[p].ch[1]].size+treap[p].r-treap[p].l+1;
    treap[treap[p].ch[0]].fa=treap[treap[p].ch[1]].fa=p;
    treap[0]=(ppp){0,0,0,0,0,0,0};
}
 int divide(int now,int k)//now保留前k个 
{
    if(k==treap[now].r-treap[now].l+1)	return 0;
    if(k==0)	return now; 
    tot++;
    treap[tot]=(ppp){0,0,rand(),0,treap[now].l+k,treap[now].r,0};
    
    f[treap[now].r]=tot;
    f[treap[now].l+k-1]=now;

    treap[now].r=treap[now].l+k-1;
    treap[tot].ch[1]=treap[now].ch[1];
    if(treap[now].rnd<treap[tot].rnd)//tot防在右下角 
    {
        treap[now].ch[1]=tot;
        update(tot);
        update(now);
    }
    else
    {
        treap[now].ch[1]=0;
        treap[tot].ch[0]=now;
        treap[tot].fa=treap[now].fa;
        treap[treap[now].fa].ch[treap[treap[now].fa].ch[1]==now?1:0]=tot;
        update(now);
        update(tot);
        update(treap[tot].fa);
    }
    if(treap[tot].fa==0)	root=tot;
    return tot;
}
 int merge(int x,int y)
{
    if(x==0 or y==0)
        return x+y;
    if(treap[x].rnd>treap[y].rnd)
    {
        treap[y].ch[0]=merge(x,treap[y].ch[0]);
        update(y);
        return y;
    }
    else
    {
        treap[x].ch[1]=merge(treap[x].ch[1],y);
        update(x);
        return x;
    }
}
 void split(int now,int &x,int &y,int rank)
{   
	if(rank==0)
    {
        treap[now].fa=treap[y].fa;
        x=0,y=now;
        return ;
    }
    if(rank>=treap[now].size)
    {
        treap[now].fa=treap[x].fa;
        x=now,y=0;
        return ;
    }
    if(treap[treap[now].ch[0]].size>=rank)
    {
        treap[now].fa=treap[y].fa;
        y=now;
        split(treap[now].ch[0],x,treap[now].ch[0],rank);
        update(now);
    }
    else if(treap[treap[now].ch[0]].size+treap[now].r-treap[now].l+1<=rank)
    {
        treap[now].fa=treap[x].fa;
        x=now;
        split(treap[now].ch[1],treap[now].ch[1],y,rank-(treap[treap[now].ch[0]].size+treap[now].r-treap[now].l+1));
        update(now);
    }
    else
    {
        int ori_fa=treap[now].fa; 
        int k=divide(now,rank-treap[treap[now].ch[0]].size-1);
        int q=divide(k,1);
        while(treap[now].fa!=ori_fa)
            now=treap[now].fa;
        split(now,x,y,rank);
    }
}
 void init()
{
    root=++tot;
    treap[root]=(ppp){0,0,rand(),n,1,n,0};
    f[n]=root;
}
 int find(int p)
{
	int fa=treap[p].fa;
    if(fa==0 or p==0 or p==fa)	return 0;
    int son=treap[fa].ch[1]==p;
    if(son)	return treap[treap[fa].ch[0]].size+treap[fa].r-treap[fa].l+1+find(fa);
    else	return find(fa);
}
 int getrank(int x)
{
    map<int,int>::iterator it=f.lower_bound(x);
    int p=it->second;
    return find(p)+treap[treap[p].ch[0]].size+x-treap[p].l+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    init();
    for(int i=1;i<=m;i++)
    {
        int opt,x1,y1;
        scanf("%d%d",&opt,&x1);
        x1-=a;
        if(opt==1)
        {
            scanf("%d",&y1);
            y1-=a;
            int rank=getrank(x1);
            printf("%d\n",rank);
            a=rank;
            int x=0,y=0,z=0;
            split(root,x,y,rank-1);
            split(y,z,y,1);
            treap[z].l=treap[z].r=y1;
            f[y1]=z;
            f.erase(x1);
            root=merge(merge(x,z),y);
        }
        else if(opt==2)
        {
			int rank=getrank(x1);
            printf("%d\n",rank);
            a=rank;
            int x=0,y=0,z=0;
            split(root,x,y,rank-1);
            split(y,z,y,1);
            root=merge(merge(z,x),y);
        }
        else if(opt==3)
        {
			int rank=getrank(x1);
            printf("%d\n",rank);
            a=rank;
            int x=0,y=0,z=0;
            split(root,x,y,rank-1);
            split(y,z,y,1);
            root=merge(merge(x,y),z);
        }
        else if(opt==4)
        {
            int x=0,y=0,z=0;
            split(root,x,y,x1-1);
            split(y,z,y,1);
            a=treap[z].l;
            printf("%d\n",a);
            root=merge(merge(x,z),y);
        }
    }
    return 0;
}
