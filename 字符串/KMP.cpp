#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int next[200002]={0},ans[200002];
char s[200002],t[200002];
int N,M,K;
void makenext()
{
	int q=1,k=0;
	for(;q<M;q++)
	{
		while(k>0 and t[q]!=t[k])  
		    k=next[k-1];
		if(t[q]==t[k]) 
			k++;
		next[q]=k;
	}
}
void kmp()
{
	int i=0,j=0,longt=M-1;
	for(;i<N;i++)
	{
	while(j&&s[i]!=t[j])	j=next[j];
	if(s[i]==t[j])j++;
	ans[j]++;
	}
/*	for(;j<N;j++)
	{
		if(s[j]==t[i])
		{
			if(i==longt)
			{
				i=next[i];
			}
			else
			i++;
		}
		else{
			if(i!=0)
			j--;
			ans[i]++;
		//	if(i==0) cout<<j<<"  "<<i<<endl; 
		//	ans[i]+=i-next[i];
			i=next[i];
			
		}
			
	}*/
}
int main()
{

	cin>>N>>M>>K;
	scanf("\n");
	cin.getline(s,10000);
	scanf("\n");
	cin.getline(t,10000);
	makenext();
	kmp();
	for(int i=M-1;i>0;i--)	ans[next[i]]+=ans[i];
	for(int i=0;i<M;i++)	ans[i]-=ans[i+1];
	for(int i=1;i<=K;i++)
	{
		int hjk;
		cin>>hjk;
		//if(hjk)
		cout<<ans[hjk]<<endl;
	}
	return 0;
}
