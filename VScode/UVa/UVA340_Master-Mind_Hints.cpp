#include<stdio.h>
#define M 1010
int main(){
    int n,a[M],b[M];                //a记录输入，b记录正确答案
    int kase=0;                     //用来输出第几次game，计次器
    while (scanf("%d",&n)==1 && n)  //当n为零输入结束，此例在输入时兼顾结束，在该做的地方去做该做的事，逻辑清晰，值得学习
    {
        printf("Game %d:",++kase);
        for(int i=0;i<n;i++)    scanf("%d",&a[i]);
        for(;;){
            int A=0,B=0;
            for(int i=0;i<n;i++){
                scanf("%d",&b[i]);
                if(a[i]==b[i])  A++;}
            if(b[0]==0) break;      //当输入第一个为0时直接结束，因为范围没有0
            for(int d=1;d<=9;d++){
                int c1=0,c2=0;
                for(int i=0;i<n;i++){       //该 for计算a b中每个元素出现的最少次数，（有没出现就是0），因为最少的说明两个共同里面都有，
                    if(a[i]==d) c1++;
                    if(b[i]==d) c2++;       
                }
                if(c1>=c2)   B +=c2;
                else B +=c1;
            }
            printf("(%d,%d)",A,B-A);        //B-A说明不在对应的个数，因为A是对应的，B是都有的，都有但是不对应就是位置不对的
        }
    }
    return 0;
}