#include<stdio.h>
//��Ҫ�����ļ�����������ҽ�ֹ���ض���ʱ�� fopen��������
//������fopen��ĳɱ�׼���������ֻ�踳ֵ fin=stdin��fout=stdout��ͬʱ������fclose
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