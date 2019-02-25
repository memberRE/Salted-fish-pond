#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
int qpower(int a,int b,int c)
{
	int ans=1;
	a%=c;
	while(b)
	{
		if(b&1)
			ans=(ans*a)%c;
		b=b>>1;
		a=(a*a)%c;
	}
	return ans;
}
int main()
{
	int m,n,k,x;
	cin>>n>>m>>k>>x;
	int modd=qpower(10,k,n);
//	cout<<modd<<endl;
	cout<<(modd * m + x) % n<<endl;
	return 0;
}