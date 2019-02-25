#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
void read(long long &x)
{
    long long f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
void print(int x)
{
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		long long n;
		read(n);
		int ans=0;
		for(;n;ans++)
			n &= (n-1);
		if(ans==1)
			{
				print(222);
				printf("\n");
			}
		else
			{
				print(ans);
				printf("\n");
			}
	}
	return  0;
}
