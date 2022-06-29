#include<stdio.h>
//当要求是文件输入输出，且禁止用重定向时用 fopen（）方法
//如果想把fopen版改成标准输入输出，只需赋值 fin=stdin；fout=stdout；同时不调用fclose
int main(void){
    int x;
    FILE *fin;
    FILE *flout;
    fin=fopen64("data.in","rb");
    flout=fopen64("data.out","wb");
    double i;
    for(i=0;i!=10;i+=0.1){
        printf("%.lf\n",i);
    }
    fscanf(fin,"%d",&x);
    fprintf(flout,"%d",x);
    fclose(fin);
    fclose(flout);
    return 0;
}