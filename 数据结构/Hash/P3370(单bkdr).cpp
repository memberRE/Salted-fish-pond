#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
typedef unsigned long long ull;
const int MOD=19260817,base=131;
string s;
ull a[10002];
ull bkdrhash()
{
	ull hash=0;
	for(int i=0;i<s.length();i++)
		hash=hash*base+s[i];
	return hash;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	ull ans=1;
	for(int i=1;i<=n;i++)
	{
		s.clear();
		cin>>s;
		a[i]=bkdrhash();
	}
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i++)
		if(a[i]!=a[i-1]) 
			ans++;
	cout<<ans<<endl;
	return 0;
}
