#include<bits/stdc++.h>
#define MAX 205
int c[MAX],b[MAX]={1};
void mul(int a[],int e){
    for(int j=0;j<MAX;j++)
        b[j] *=e;
    for(int j=0;j<MAX;j++)
        if(b[j]>9){
            b[j+1]+=b[j]/10;
            b[j]%=10;
        }
    
}
void add(int a[]){
    for(int i=0;i<MAX;i++){
        c[i] += a[i];
        if(c[i]>9){
            c[i+1]++;
            c[i]-=10;
        }
    }
}
int main(void){
    int q;int len=MAX-1;
    b[0]=1;
    scanf("%d",&q);
    for(int i=1;i<=q;++i){
        mul(b,i);
        add(b);
    }
    for(int i=len;i>0;i--)  
        if(c[i]==0 && len>0) len--;
        else break;
    for(int i=len;i>=0;--i)
        printf("%d",c[i]);
    return 0;
}