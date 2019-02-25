#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,pic[10005],sum=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>pic[i];
		sum+=pic[i];
	}
	sum/=n;
	int ans=0;
	for(int i=1;i<=n;i++)
		if(pic[i]!=sum)
		{
			pic[i+1]+=(pic[i]-sum);
			ans++;
		}
	cout<<ans<<endl;
	return 0;
}
