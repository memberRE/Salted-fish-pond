#include<bits/stdc++.h>
using namespace std;
const int MAX=1e5+10;
char pic[MAX],s1[MAX<<1],s2[MAX<<1];
int p1[MAX<<1],p2[MAX<<1],cnt=2;
int ans1[MAX<<1] ,ans2[MAX<<1],len;
void manachar(char * s,int * p,int * ans)
{
	int mid=0,mr=0;
	for(int i=0;i<cnt;i++)
	{
		p[i]=i<mr?min(p[mid*2-i],mr-i):1;
		for(;s[p[i]+i]==s[i-p[i]];p[i]++)
			if(i+p[i]>mr)
			{
				mr=i+p[i];
				ans[mr]=p[i];
				mid=i;
			}
	}
}
int main()
{
	scanf("%s",pic);
	len=strlen(pic);
	s1[0]=s2[0]='$';
	s1[1]=s2[1]='#';
	for(int i=0;i<len;i++)
	{
		s1[cnt]=pic[i];
		s2[cnt]=pic[len-i-1];
		s1[++cnt]='#';
		s2[cnt++]='#';
	}
	cnt++;
	s1[cnt]=s2[cnt]='\0';
	manachar(s1,p1,ans1);
	manachar(s2,p2,ans2);
	int j=cnt-4,ans=2;
	for(int i=3;i<cnt-2;i++)
	{
		if(s1[i]=='#')
			ans=max(ans,ans1[i]+ans2[j]);
		j--;
	}
	cout<<ans<<endl;
	return 0;
}
