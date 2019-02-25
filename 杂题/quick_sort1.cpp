#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100002];
void quick_sort(int l,int r)
{
	int i=l,j=r;
	ll mid =a[l];
	if(l>=r)	return ;
	while(i<j)
	{
		while(i<j and  a[j]>=mid)
			j--;
		if(i<j)	a[i++]=a[j];
		while(i<j and a[i]<=mid)
			i++;
		if(i<j)	a[j--]=a[i]; 
	}
	a[i]=mid;
	quick_sort(l,i-1);
	quick_sort(i+1,r);
	return ;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	quick_sort(1,n);
	for(int i=1;i<=n;i++)
		printf("%lld ",a[i]);
	return 0;
}
