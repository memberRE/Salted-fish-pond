#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<set>
#include<cmath>
#include<vector>
using namespace std;
struct pp
{
    int height;
    int name;
    bool operator < ( const pp  &b)const {
        return (this->height<b.height);
    }
}pic[100003];
vector<pp> linshi;
set<pp> s;
set<pp>::iterator it,mkl;
long long n,nea[2][100003],g[100003][21],f[100003][21][2],m;
long long li[4],lin,x0;
void que(int s,int x,long long &da,long long &db)
{
	for(int i=20;i>=0;i--)
		if(f[s][i][0]+f[s][i][1]<=x and g[s][i])
		{
			da+=f[s][i][0];
			db+=f[s][i][1];
			x-=f[s][i][0]+f[s][i][1];
			s=g[s][i];
		}
	if(nea[1][s] and s and abs(pic[s].height-pic[nea[1][s]].height)<=x)
		da+=abs(pic[s].height-pic[nea[1][s]].height);
}
bool cam(pp a,pp b)
{
	if(abs(a.height)<abs(b.height))
		return true;
	if(abs(a.height)==abs(b.height))
		return a.height>b.height;
	else return false;
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		{
			scanf("%d",&pic[i].height);
			pic[i].name=i;
		}
	for(int i=n;i>=1;i--)
	{
		it=s.lower_bound(pic[i]);
		if(s.size()==1)
			{
				pp k=*(s.begin());
				nea[0][i]=k.name;
			}
		else if(it==s.end())
		{
			if(s.size()>=2)
			{
				pp k1,k2;
				k1=*(--it);
				k2=*(--it);
				nea[0][i]=k1.name;
				nea[1][i]=k2.name;
			}
		}
		else if(it==s.begin())
		{
			if(s.size()>=2)
			{
				pp k1,k2;
				k1=*(it);
				k2=*(++it);
				nea[0][i]=k1.name;
				nea[1][i]=k2.name;
			}
		}
		else
		{
			if(s.size()>=2)
			{
				int jishu=0;
				pp k1=*it;
				mkl=it;
				k1.height=pic[i].height-k1.height;
				linshi.push_back(k1);
				while(--it!=s.begin() and jishu<2)
				{
					k1=*it;
					k1.height=pic[i].height-k1.height;
					linshi.push_back(k1);
					jishu++;
				}
				k1=*s.begin();
				k1.height=pic[i].height-k1.height;
				linshi.push_back(k1);
				if(++mkl!=s.end())
				{
					k1=*mkl;
					k1.height=pic[i].height-k1.height;
					linshi.push_back(k1);
				}
				sort(linshi.begin(),linshi.end(),cam);
			/*	for(int j=0;j<=linshi.size();j++)
					cout<<i<<" "<<linshi[j].height<<" "<<linshi[j].name<<endl;
				cout<<endl;*/
				nea[0][i]=linshi[0].name;
				nea[1][i]=linshi[1].name;
				linshi.clear();
			}
		}
		s.insert(pic[i]);
	}
	//****************************
	for(int i=1;i<=n;i++)
	{
		g[i][0]=nea[0][nea[1][i]];
		if(nea[1][i])			f[i][0][0]=abs(pic[i].height-pic[nea[1][i]].height);//!?!?!?!?!?!
		if(nea[0][nea[1][i]] and nea[1][i])	f[i][0][1]=abs(pic[nea[1][i]].height-pic[nea[0][nea[1][i]]].height);
	}
	for(int j=1;j<=20;j++)
		for(int i=1;i<=n;i++)
		{
			g[i][j]=g[g[i][j-1]][j-1];
			f[i][j][0]=f[g[i][j-1]][j-1][0]+f[i][j-1][0];
			f[i][j][1]=f[g[i][j-1]][j-1][1]+f[i][j-1][1];
		}
/*	for(int j=0;j<=21;j++)
		{
			for(int i=1;i<=n;i++)
			cout<<g[i][j]<<" "<<f[i][j][0]<<" "<<f[i][j][1]<<endl;

		}*/
	//---------------
	cin>>x0;
	long long a=99999999999,b=0;
	int jkl=0;
	for(int i=1;i<=n;i++)
	{
		long long da=0,db=0;
		que(i,x0,da,db);
		if(db and (!jkl or a*db>b*da))
		{
			jkl=i;
			a=da;
			b=db;
		}
	}
	cout<<jkl<<endl;
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		int s,x;
		scanf("%d%d",&s,&x);
		long long da=0,db=0;
		que(s,x,da,db);
		cout<<da<<" "<<db<<endl;
	}
	return 0;
}