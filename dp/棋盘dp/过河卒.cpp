#include<iostream>
#include<cstring>
using namespace std;
int n,m,x,y;
long long a[100][100];
int main()
{
	cin>>m>>n>>x>>y;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=n;j++)
			a[i][j]=1; 
a[x][y]=0;a[x-1][y-2]=0;a[x-1][y+2]=0;a[x-2][y-1]=0;a[x-2][y+1]=0;a[x+2][y+1]=0;a[x+1][y-2]=0;a[x+1][y+2]=0;a[x+2][y-1]=0;
	for (int i=0;i<=m;i++)
	for (int j=0;j<=n;j++)
{ 
	if(a[i][j]!=0)
	  { if(i==0 and j==0) continue;
	  	if (i>0 and j>0)a[i][j]=a[i-1][j]+a[i][j-1];
	  else if (i>0) a[i][j]=a[i-1][j];
		    else  a[i][j]=a[i][j-1];
	  }
}	
   cout<<a[m][n];
   return 0;
}
