#include<stdio.h>
void swap(int *a,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}
int main(void){
    int a,b;
    scanf("%d %d",&a,&b);
    printf("%d %d\n",a,b);
    swap(&a,&b);
    printf("%d %d",a,b);
    return 0;
}