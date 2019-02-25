#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
struct ppp {
	int x,y,k;
}pic[100006];
int p[100005],n,m;
long long ans=0;
bool cam(ppp a,ppp b){
	return a.k<b.k;
}
int find(int x){
	if(p[x]==x) return x;
	else 
	{
		p[x]=find(p[x]);
		return find(p[x]);
	}

}
int main(){
//	mamset(p,0,sizeof(p));
	cin>>n>>m;
	   for(int i=0;i<m;i++) {
	   	cin>>pic[i].x>>pic[i].y>>pic[i].k;
	   	p[i]=i;
	   } 
	sort(pic,pic+m,cam);
	for(int i=0;i<m;i++)
	{
		int aa=find(pic[i].x),bb=find(pic[i].y);
		if(aa!=bb)
		{
			ans+=pic[i].k;
			p[aa]=bb;
		}
	}
	cout<<ans<<endl;
	return 0;
}
