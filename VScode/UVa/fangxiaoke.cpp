#include<cstdio>
int f(int x)
{

    int y=x,num=0;//int y=x,��ֹx���ı�
    while (y!=0)
    {
        num=num*10+y%10;//��һ�����ֵļ�¼��λ�ټ�����һλ��
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