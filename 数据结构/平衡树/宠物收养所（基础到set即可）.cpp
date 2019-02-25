#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<set>
#include<cmath>
using namespace std;
set<int> s;//0 pets ;1 people
set<int>::iterator it;
int main()
{
	int n,now,ans=0;cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a,b;
		cin>>a>>b;
		if(!s.size())	now=a,s.insert(b);
		else if(a==now)	s.insert(b);
		else
		{
			it=s.lower_bound(b);
			if(it==s.end())
			ans=(ans+abs(*(--it)-b))%1000000,s.erase(it);
			else if(it==s.begin())
			ans=(ans+abs(*it-b))%1000000,s.erase(it);
			else
			{
				int k1=abs(*it-b);int k2=abs(*(--it)-b);
				if(k2<=k1)
				ans=(ans+abs(*(it)-b))%1000000,s.erase(it);
				else 
				ans=(ans+abs(*(++it)-b))%1000000,s.erase(it);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}