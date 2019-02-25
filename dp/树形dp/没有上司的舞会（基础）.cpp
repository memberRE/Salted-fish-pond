#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int r[6005],pic[6005],star[12005],N,s[6005];//r[i]: i has r[i] sons.
int dp[2][6005];
bool vztd[2][6005];
struct ppp{
	short a,b;
}lin[6005];
bool cam(ppp a,ppp b){
	if(a.b<b.b or a.b>b.b) return a.b<b.b;
	else return a.a<b.a;
}
int dfs(int bo,int w){
	if(vztd[bo][w]) return dp[bo][w];
	vztd[bo][w]=1;
	if(r[w]==0) return dp[bo][w]=bo*pic[w];
	if(bo==1){int sum=0;
		for(int i=s[w]+1;i<=s[w]+r[w];i++) sum+=dfs(0,star[i]);
		return dp[bo][w]+=sum; 
	 }
	if(bo==0){
		int sum=0;
		for(int i=s[w]+1;i<=s[w]+r[w];i++) sum+=max(dfs(1,star[i]),dfs(0,star[i]));
		return dp[bo][w]+=sum;
	}
}
int main(){
	cin>>N;
	memset(pic,0xff,sizeof(pic));
	memset(dp,0,sizeof(dp));//0x3f=1061109567
	memset(r,0,sizeof(r));
	memset(vztd,0,sizeof(vztd));
	memset(star,0,sizeof(star));
	for(int i=1;i<=N;i++){
		cin>>dp[1][i];pic[i]=dp[1][i];
	} 
	for(int i=1;i<=N;i++) {
		cin>>lin[i].a>>lin[i].b;
		r[lin[i].b]++;
		vztd[1][lin[i].a]=1;
	}
	sort(lin+1,lin+N,cam);//jiu shi lin+n
	int l=0,k=0,zu=N;
	for(int i=1;i<N;i++){if(vztd[1][i]==0) zu=i;
		if(l!=lin[i].b){
			l=lin[i].b;
			s[l]=i+k;
			star[i+k]=lin[i].b;
			k++;
			star[i+k]=lin[i].a;
		}
		else
			star[i+k]=lin[i].a;
	}//qian xiang xing
		memset(vztd,0,sizeof(vztd));
	cout<<max(dfs(1,zu),dfs(0,zu))<<endl;
	return 0;
}