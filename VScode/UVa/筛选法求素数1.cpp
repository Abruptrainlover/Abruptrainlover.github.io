
//������˹����ɸ��
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
#define MAX 8099999
//��1��Ƿ�����
bool prime[MAX];
//p���鴢������������tot
int p[MAX],tot;
void getPrime(int n)
{
    int i,j;
    memset(prime,0,sizeof(prime));
    tot=0;
    prime[1]=1;
    for(i=2;i<=n;i++)
    {
        if(prime[i]==0)
            p[tot++]=i;
        for(j=i*i;j<=n;j+=i)
            prime[j]=1;
    }
}
int main()
{
    int i,n;
    while(scanf("%d",&n))
    {
        getPrime(n);
        //�������[1,n]֮�����������
        for(i=0;i<tot;i++)
            printf("%d ",p[i]);
        printf("%d",tot);
    }
    return 0;
}