#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int pic[2001][2001],h[2001],l[2001],r[2001],n,maxx=-1;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>pic[i][j];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			if(pic[i][j]==0) 
				h[j]++;
			else
				h[j]=0;
		for(int j=1;j<=n;j++)
		{
			l[j]=j;
			while(l[j]>1 and h[j]<=h[l[j]-1])
				l[j]=l[l[j]-1];
		}
		for(int j=n;j>=1;j--)
		{
			r[j]=j;
			while(r[j]<n and h[j]<=h[r[j]+1])
				r[j]=r[r[j]+1];
		}
		for(int j=1;j<=n;j++)
			maxx=max(maxx,h[j]*(r[j]-l[j]+1));
	}
	cout<<maxx<<endl;
	return 0;
}