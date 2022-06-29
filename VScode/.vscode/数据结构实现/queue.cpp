#include<bits/stdc++.h>
const int N=100000;
int a[N];
int pl=1,pr=0;
int empty(void){
    if(pr==pl)  return 1;
    return 0;
}
void push(int n){
    //if((++pr)%N==pr)    printf("ERROR");
    a[(++pr)%N]=n;
}
void pop(void){
    pl=(++pl)%N;
}

int front(void){
    if(!empty())
    return a[pl];
    printf("empty"); return 0;
}

int back(void){
    if(!empty()) return a[pr];
    printf(" empty");
    return 0;
}
int size(void){
    return pr-pl+1;
}
void clear(void){
    pr=0;pl=1;
}

int main(void){
    int n,a;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a);
        push(a);
    }
    printf("f:%d b:%d s:%d",front(),back(),size());
    return 0;
}