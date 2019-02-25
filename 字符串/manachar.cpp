#include<bits/stdc++.h>
using namespace std;
const int MAX=21000020;
char s[MAX],t[MAX<<1];
int p[MAX<<1],cnt=0,mid,mr;
void manachar()
{
	t[cnt++]='$';
	int len=strlen(s);
	for(int i=0;i<len;i++)
	{
		t[cnt++]='#';
		t[cnt++]=s[i];
	}
	t[cnt++]='#';
	t[cnt]='\0';
	
	for(int i=0;i<cnt;i++)
	{
		p[i]=i<mr?min(p[(mid<<1)-i],mr-i):1;
		for(;t[p[i]+i]==t[i-p[i]] and p[i]+i<cnt;p[i]++)
			if(p[i]+i>mr)
			{
				mid=i;
				mr=p[i]+i;
			}
	}
}
int main()
{
	scanf("%s",s);
	manachar();
	int ans=1;
	for(int i=0;i<cnt;i++)
		ans=max(ans,p[i]);
	printf("%d",ans-1);
	return 0;
}
