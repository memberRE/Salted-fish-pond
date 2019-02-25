#include<bits/stdc++.h>
using namespace std;
const int MAX=1e6+20;
char s[MAX],t[MAX];
int next[MAX];
void getnext(int m)//m=strlen(t)
{
	next[0]=next[1]=0;
	for(int i=1;i<m;i++)
	{
		int j=next[i];
		while(j and t[i]!=t[j])	j=next[j];
		next[i+1]=t[j]==t[i]?j+1:0;
	}
}
void find(int n,int m)//n=strlen(s); m is the same
{
	int j=0;
	getnext(m);
	for(int i=0;i<n;i++)
	{
		while(j and s[i]!=t[j])	j=next[j];
		if(s[i]==t[j])	j++;
		if(j==m)	printf("%d\n",i-m+1+1);
	}
}
int main()
{
	scanf("%s%s",s,t);
	int n=strlen(s),m=strlen(t);
	find(n,m);
	for(int i=1;i<=m;i++)
		printf("%d ",next[i]);
	return 0;
}
