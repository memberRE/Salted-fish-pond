#include<cstdio>
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
int gcd(int x,int y)
{
    return y==0?x:gcd(y,x%y);
}
int a[22];
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<1<<n;i++)
	{
		int k=i,cnt=0,num=1,lastgcd;
		while(k)
		{
			if(k&1)
			{
				cnt++;
				if(cnt==1)
					lastgcd=a[num];
				else
					lastgcd=gcd(lastgcd,a[num]);
			}
			num++;
			k>>=1;
		}
		if(cnt&1)
			ans+=lastgcd;
		else
			ans-=lastgcd;
	}
	cout<<ans<<endl;
	return 0;
}
