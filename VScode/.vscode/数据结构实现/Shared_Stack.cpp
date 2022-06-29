#include<bits/stdc++.h>
const int MAX=1010;
int stack[MAX]={0};
int TOP_S=0,TOP_B=MAX;
int Push(int e,bool SLT){
    if(TOP_S+1==TOP_B){
        return 0;
    }
    if(SLT==0)  stack[++TOP_S]=e;
    
    if(SLT==1)  stack[--TOP_B]=e;
    return 1;

}
int Pop(int *E,bool SLT ){
    if(TOP_B==MAX||TOP_S==0){
        return 0;
    }
    if(SLT==0) *E=stack[TOP_S--];
    if(SLT==1) *E=stack[TOP_B++];
    return 1;
}
void Pop_All(bool SLT){
    if(SLT==0){
        printf("Stack2:");
        while(TOP_S!=0)     printf("%d ",stack[TOP_S--]);
        
    }
    if(SLT==1){
        printf("Stack2:");
        while(TOP_B!=MAX) printf("%d ",stack[TOP_B++]);
        
    }
}
int main(void){
    Push(19,0);
    Push(12,0);
    Push(10,0);
    Push(1,0);
    Push(8,1);
    Push(6,1);
    Push(4,1);
    Push(2,1);
    Pop_All(0);
    Pop_All(1);
    return 0;
}


