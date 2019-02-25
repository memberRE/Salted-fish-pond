#include<bits/stdc++.h>
using namespace std;
const int MAXA=1e4+3,MAXN=1000040;
int head[MAXA],next[MAXN<<1],to[MAXN<<1],tot,n;
bool used[MAXN];
int linked[MAXN];
inline int dfs(int u)
{
    for(int i=head[u];i;i=next[i])
    {
        int v=to[i];
        if(!used[v])
        {
            used[v]=1;
            if(!linked[v] or dfs(linked[v]))
            {
                linked[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
void add(int atk,int id)
{
    tot++;
    to[tot]=id;
    next[tot]=head[atk];
    head[atk]=tot;
}
int km()
{
    int res=0;
    for(int i=1;i<=1e4;i++)
    {
        memset(used,0,sizeof(used));
        if(dfs(i))
            res++;
        else
            break;
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int s1,s2;
        scanf("%d%d",&s1,&s2);
        add(s1,i);
        add(s2,i);
    }
    printf("%d",km());
    return 0;
}
