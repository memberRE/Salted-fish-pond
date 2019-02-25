#include<iostream>
#include<cstring>
using namespace std;
int p[5006],a[5006],tot,ans=0;
int main()
{  cin>>tot;
 for(int i=1;i<=tot;i++)
{
	cin>>a[i];p[i]=1;
}     

for(int i=2;i<=tot;i++)
	for(int j=i-1;j>=1;j--){
		if(a[j]<a[i] and p[i]<=p[j]+1)
		   p[i]=p[j]+1; 
	}
for(int i=1;i<=tot;i++)
    if(ans<=p[i])  ans=p[i];
cout<<ans;
return 0;
} 
