#include<bits/stdc++.h>
#define F(i,n,m) for(int i=n;i<=m;i++)
using namespace std;
int main()
{
	priority_queue<int,vector<int>,greater<int> > q;//Ð¡¸ù¶Ñ
	int n,x;
	cin>>n;
	F(i,1,n)
	{
		cin>>x;
		q.push(x);
	}
	F(i,1,n)
	{
		cout<<q.top()<<' ';
		q.pop();
	}
	return 0;
}