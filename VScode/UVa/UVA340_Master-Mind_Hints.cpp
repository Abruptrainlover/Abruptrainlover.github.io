#include<stdio.h>
#define M 1010
int main(){
    int n,a[M],b[M];                //a��¼���룬b��¼��ȷ��
    int kase=0;                     //��������ڼ���game���ƴ���
    while (scanf("%d",&n)==1 && n)  //��nΪ���������������������ʱ��˽������ڸ����ĵط�ȥ���������£��߼�������ֵ��ѧϰ
    {
        printf("Game %d:",++kase);
        for(int i=0;i<n;i++)    scanf("%d",&a[i]);
        for(;;){
            int A=0,B=0;
            for(int i=0;i<n;i++){
                scanf("%d",&b[i]);
                if(a[i]==b[i])  A++;}
            if(b[0]==0) break;      //�������һ��Ϊ0ʱֱ�ӽ�������Ϊ��Χû��0
            for(int d=1;d<=9;d++){
                int c1=0,c2=0;
                for(int i=0;i<n;i++){       //�� for����a b��ÿ��Ԫ�س��ֵ����ٴ���������û���־���0������Ϊ���ٵ�˵��������ͬ���涼�У�
                    if(a[i]==d) c1++;
                    if(b[i]==d) c2++;       
                }
                if(c1>=c2)   B +=c2;
                else B +=c1;
            }
            printf("(%d,%d)",A,B-A);        //B-A˵�����ڶ�Ӧ�ĸ�������ΪA�Ƕ�Ӧ�ģ�B�Ƕ��еģ����е��ǲ���Ӧ����λ�ò��Ե�
        }
    }
    return 0;
}