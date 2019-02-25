#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int pic[55][55], a[55][55][55]; 
int MAX(int a ,int b ,int c, int d){
	return max(a,max(b,max(c,d)));
}
int main() {
	int m,n;
	cin>>m>>n;
	memset(a,0,sizeof(a));
	memset(pic,0,sizeof(pic));
	for(int i=1;i<=m;i++)
	   for(int j=1;j<=n;j++)
	      cin>>pic[i][j];
	for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++)
	for(int k=1;k<=i+j;k++){
		if(i==k and j==i+j-k) { if(i==m and j==n) a[i][j][k]=MAX(a[i-1][j][k-1],a[i][j-1][k],a[i-1][j][k],a[i][j-1][k-1])+pic[i][j]+pic[k][i+j-k];
		else continue;
		}
		else 	a[i][j][k]=MAX(a[i-1][j][k-1],a[i][j-1][k],a[i-1][j][k],a[i][j-1][k-1])+pic[i][j]+pic[k][i+j-k];
	}
	cout<<a[m][n][m]<<endl;
	return 0;
}