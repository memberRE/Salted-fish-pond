#include<bits/stdc++.h>// include shuzi,zimu
using namespace std;
const int MAX=1e6+4;
char s[MAX];
int sa[MAX],rank[MAX],num[MAX],sec[MAX];
int M,N; //string 下标从1开始 
void Debug()
{
	printf("*****************\n");
	printf("下标");
	for (int i = 1; i <= N; i++) printf("%d ", i);
	printf("\n");
	printf("sa  ");
	for (int i = 1; i <= N; i++) printf("%d ", sa[i]);
	printf("\n");
	printf("rak ");
	for (int i = 1; i <= N; i++) printf("%d ", rank[i]);
	printf("\n");
	printf("tp  ");
	for (int i = 1; i <= N; i++) printf("%d ", sec[i]);
	printf("\n");
}
void binsort()
{
	for(int i=0;i<=M;i++)	num[i]=0;
	for(int i=1;i<=N;i++)	num[rank[i]]++;
	for(int i=1;i<=M;i++)	num[i]+=num[i-1];
	for(int i=N;i>=1;i--)		sa[num[rank[sec[i]]]--]=sec[i];
}
void suffix_array()
{
	M='z';
	for(int i=1;i<=N;i++)	rank[i]=s[i]-'0'+1,sec[i]=i;
	binsort();
	for(int w=1,p=0;p<N;w<<=1,M=p)
	{
		p=0;
		for(int i=1;i<=w;i++)	sec[++p]=N-w+i;
		for(int i=1;i<=N;i++)	if(sa[i]>w)	sec[++p]=sa[i]-w;
		binsort();
		swap(rank,sec);
		rank[sa[1]]=p=1;
		for(int i=2;i<=N;i++)//重排rank 
			rank[sa[i]]=(sec[sa[i-1]]==sec[sa[i]] and sec[sa[i-1]+w]==sec[sa[i]+w]) ? p : ++p;
	}
	for(int i=1;i<=N;i++)
		printf("%d ",sa[i]);
}
int main()
{
	scanf("%s",s+1);
	N=strlen(s+1);
	suffix_array();
	return 0;
}
