#include<bits/stdc++.h>
#define F(i,n,m) for(int i=n;i<=m;i++)
using namespace std;
int main()
{
	map<int,int> a;
	int n;
	cin>>n;
	F(i,1,n)
	{
		int x;
		cin>>x;
		a[x]++;
	}
	map<int,int>::iterator it=a.begin();
	for(it;it!=a.end();it++)
	{
		aa:;
		if(it->second==0) continue;
		cout<<it->first<<' '; it->second--; goto aa;
	}
	return 0;
}