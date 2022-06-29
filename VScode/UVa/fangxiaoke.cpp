#include<cstdio>
int f(int x)
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
int main(void){
    int x=0;
    scanf("%d",&x);
    printf("%d",f(x));
    return 0;
}