#include<iostream>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
const int root=0;
const int typnum=62;
struct ppp{
	int son[typnum];
	bool mark;
}trie[26009];
string s;
int ans=0,num=1;
int coding(char a)
{
	if(a>='a' and a<='z')
		return (int)a-'a';
	if(a>='0' and a<='9')
		return 26+(a-'0');
	return 36+(a-'A');
}
int insert_check()
{
	int noww=root;
	int e=s.length();
	for(int i=0;i<e;i++)
	{
		int k=coding(s[i]);
		if(!trie[noww].son[k])
			trie[noww].son[k]=num++;
		noww=trie[noww].son[k];
	}
	int tmp=trie[noww].mark;
	trie[noww].mark=1;
	return !tmp;
}
int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		s.clear();
		cin>>s;
		ans+=insert_check();
	}
	cout<<ans<<endl;
	return 0;
}
