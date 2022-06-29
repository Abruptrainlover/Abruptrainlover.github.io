#include<bits/stdc++.h>
const int MAX=1010;
int TOP=0;
int stack[MAX]={0};
int Push(int e){
    if(stack[TOP]==MAX){
        return 0;
    }
    stack[++stack[TOP]]=e;
    return 1;
}
int Pop(int *e){
    if(stack[TOP]==0)
        return 0;
    (*e)=stack[stack[TOP]--];
    return 0;
}
void PopAll(void){
    while(stack[TOP]!=0){
        printf("%d ",stack[stack[TOP]--]);
    }
}
int main(void){
    int *E;
    Push(10);
    Push(7);
    PopAll();
    return 0;
}