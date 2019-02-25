#include<iostream>
#include<cstring>
using namespace std;
int pic[204][204],n,m,biao=0;
int vztd[204],cx[204],cy[204];
int dfs(int a){
	for(int i=1;i<=m;i++){
		if(pic[a][i] and !vztd[i]){
			vztd[i]=1;
			if(cy[i]==-1 or dfs(cy[i])){
			/*cx[a]=i;*/cy[i]=a; /*cout<<a<<i<<endl;*/return 1;	
			}
		}
	}
	return 0;
}
int match(){int ans=0;
	memset(cx,-1,sizeof(cx)); 
    memset(cy,-1,sizeof(cy));
    for(int i=1;i<=n;i++){
    	if(cx[i]==-1){
    		memset(vztd,0,sizeof(vztd));
    		ans+=dfs(i);
		}
	}
	return ans;
}
int main(){
	cin>>n>>m;
	memset(pic,0,sizeof(pic));
	for(int i=1;i<=n;i++)
	for(;;){
		int a;
		cin>>a;
		if(a==0) break;
		else pic[i][a]=1;
	} 
	int ans=match();
	cout<<ans<<endl;
	return 0;
}