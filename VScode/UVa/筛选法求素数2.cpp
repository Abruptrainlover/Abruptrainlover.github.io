#include<iostream>
#include<cstdio>
#define MAXN 10000005
using namespace std;
int prime[MAXN];
bool pp[MAXN];
int vis[MAXN];
bool pd_h(int x)
{

    int y=x,num=0;//int y=x,防止x被改变
    while (y!=0)
    {
        num=num*10+y%10;//上一次数字的记录进位再加上下一位数
        y/=10;
    } 
    if (num==x) return 1;
    else return 0;
}
int main()
{
    int a,b;
    cin>>a>>b;
    int cnt=0;
    if(b>10000000) b=10000000;
    for(int i=2;i<=b;i++)
    {
        if(!vis[i]) prime[cnt++]=i,pp[i]=1;
        for(int j=0;j<cnt&&i*prime[j]<=b;j++)
        {
            vis[i*prime[j]]=i;
            //if(i%prime[j]==0) break;
        }
    }
    for(int i=a;i<=b;i++)
    {
        if(i>10000000) break;
        if(pd_h(i)&&pp[i]) printf("%d\n",i);
    }
}