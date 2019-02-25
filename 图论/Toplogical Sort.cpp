#include<iostream>
#include<cstring>
using namespace std;
int pic[999][999],ind[999],m,n;
int topo(){
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){ //cout<<j; 
			if(ind[j]==0){
		    	ind[j]--;
		    	cout<<j<<" ";
		    	for(int k=1;k<=m;k++){
		    	//	cout<<pic[j][k];
		    		if(pic[j][k]==1) {
		    	   	ind[k]--; //cout<<endl<<k<<ind[k]<<endl;
		    	   }
		    	}
		    	   
		        break;
		    	}
		    if(j==m) return 0;
		}
		if(i==m) return 1;    
		    }
	}

int main(){
	cin>>m>>n;//n bian,m dian;
	memset(pic,0,sizeof(pic));
    memset(ind,0,sizeof(ind));
    for(int i=1;i<=n;i++){
    	int k,l;
    	cin>>k>>l;pic[k][l]=1;
    	ind[l]++;
    }
   /* cout<<"³õÊ¼ind";
    for(int g=1;g<=n;g++){
    	cout<<ind[g]; 
    }
    cout<<endl;*/
    int hj=topo();
    if(hj==0) cout<<endl<<"false";
    else cout<<endl<<"true";
    return 0;
}
