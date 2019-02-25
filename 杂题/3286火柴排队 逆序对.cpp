#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
int aa[100002],lin[100002];
struct ppp{
	int x;
	int cut;
}A[100002],B[100002];
unsigned long long ans=0;
bool cam(ppp a,ppp b)
{
	return a.x<b.x;
}
void marge(int l,int m,int r)
{
	int i=l,j=m+1,k=l;
	while(i<=m and j<=r)
	{
		if(aa[i]>aa[j])
		{
			lin[k]=aa[j];
			k++;j++;
			ans+= m-i+1;
			ans%=99999997;
		}
		else
		{
			lin[k]=aa[i];
			k++;i++;
		}
	}
	while(i<=m) lin[k++]=aa[i++];
	while(j<=r) lin[k++]=aa[j++];
	for(i=l;i<=r;i++)
		aa[i]=lin[i];
}
/*void marge(int l,int mid,int r)    
{    
    int i=l,j=mid+1,k;    
    for(k=l;k<=r;k++)    
        if((i<=mid)&&((j>r)||(aa[i]<=aa[j])))    
            lin[k]=aa[i++];    
        else{   
            lin[k]=aa[j++];   
            ans+=mid-i+1;   
            ans%=99999997;  
        }      
    for(i=l;i<=r;i++)    
        aa[i]=lin[i];    
} */   
void marge_sort(int l,int r)
{
	if(l<r)
	{
		int m=(l+r)>>1;
		marge_sort(l,m);
		marge_sort(m+1,r);
		marge(l,m,r);
	}
}
/*void margef(int l,int r)  
{  
    if(l<r)  
    {  
        int mid=(l+r)/2;  
        margef(l,mid);  
        margef(mid+1,r);  
        marge(l,mid,r);  
    }  
}  */
int main()
{
	int n,jkl=2;
	cin>>n;
	for(int i=1;i<=n;i++)
		{
			scanf("%d",&A[i].x);
			A[i].cut=i;
		}
	for(int i=1;i<=n;i++)
		{
			scanf("%d",&B[i].x);
			B[i].cut=i;
		}
	sort(A+1,A+n+1,cam);
	sort(B+1,B+n+1,cam);
	for(int i=1;i<=n;i++)
	{
		aa[A[i].cut]=B[i].cut;
	}	
	marge_sort(1,n);
//	for(int i=1;i<=n;i++)
//		cout<<aa[i]<<" ";
//		cout<<endl;
	cout<<ans%99999997<<endl;
	return 0;
}