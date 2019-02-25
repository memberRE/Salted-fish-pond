#include<iostream>
using namespace std;
int k,a1,b1,ax,bx,a2,b2,x,y;
int Exgcd(int a,int b)
{
	if(!b)
	{
		x=1;y=0;
		return a;
	}
	int r=Exgcd(b,a%b);
	int t=x;x=y;y=t-a/b*y;
	return r;
}
int main()
{
	cin>>k>>a1>>b1>>ax>>bx>>a2>>b2;
	int r=Exgcd(ax,-bx);
	if((b2-a2)%r)
	{
		cout<<"no answer";
		return 0;
	}
	k=(b2-a2)/r;
	cout<<x<<" "<<y<<endl;
	x*=k;y*=k,r*=k;
	if(x<0||y<0)
	{
		cout<<"no answer";
		return 0;
	}
	cout<<x*ax+a2;
	return 0;
}
