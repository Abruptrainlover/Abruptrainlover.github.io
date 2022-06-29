#include<bits/stdc++.h>
const int max=1001;
int a[max];
int main(void){
    int cnt,mnt,num;
    scanf("%d %d",&cnt,&mnt);
    for(int i=1;i<=mnt;i++)  {
        scanf("%d",&num);
        a[num]++;
    }
    for(int i=1;i<=cnt;i++) 
        if(a[i]!=0)
            for(int j=0;j<a[i];j++)
                printf("%d ",i);
    return 0;
        
}