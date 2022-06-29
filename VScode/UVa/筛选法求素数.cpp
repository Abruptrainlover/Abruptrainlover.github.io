#include<iostream>
#include<string.h>
#define N 10000005
int vis[N],prime[N];
int count=0;
void isPrime()
{
	int cnt=0;
	for(int i=2;i<=N;i++)
    {
        if(!vis[i]) {prime[cnt++]=i;count++;}
        for(int j=0;j<cnt&&i*prime[j]<=N;j++)
        {
            vis[i*prime[j]]=i;
            //if(i%prime[j]==0) break;
        }
    
}
}
int main(void){
    memset(vis,0,N*sizeof(int));
    vis[0]=1;vis[1]=1;
    isPrime();
    for(int i=0;i<count;i++){
       
        printf(" %d",prime[i]);
    }
    printf("\n%d",count);
    return 0;
}