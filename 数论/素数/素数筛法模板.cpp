#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define MAX 10000002
using namespace std;
bool prime[10000020];
void isprime()
{
	prime[0]=prime[1]=0;prime[2]=1;
	for(int i=3;i<MAX;i++)
		prime[i]=i%2==0?0:1;
	int t=(int)sqrt(MAX*1.0);
	for(int i=3;i<t;i++)
		if(prime[i])
			for(int j=i*i;j<MAX;j+=(i<<1))
				prime[j]=0;
}
int main()
{
	isprime();
/*	int k;
	cin>>k;
	if(prime[k])
		cout<<"\\t"<<endl;
	else cout<<"\\n"<<endl;*/ 
	return 0;
}
