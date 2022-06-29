#include<stdio.h>
#include<string.h>
typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start,size_t len){
    size_t i;
    for(i=0;i<len;i++){
        printf("%.2x",start[i]);
    }
    printf("\n");
}
void show_int(int x){
    show_bytes((byte_pointer)&x,sizeof(int));
}
void show_float(float x){
    show_bytes((byte_pointer)&x,sizeof(float));
}
void show_pointer(void *x){
    show_bytes((byte_pointer)&x,sizeof(void *));
}
int main(int val){
    // val=12345;
    // int ival=val;
    // float fval=(float)val;
    // int *pval=&ival;
    // show_int(ival);
    // show_float(fval);
    // show_pointer(pval);

    // val=0x87654321;
    // byte_pointer valp=(byte_pointer) &val;
    // show_bytes(valp,1);
    // show_bytes(valp,2);
    // show_bytes(valp,3);
    val=3510593;
    float fval =3510593.00;
    const char *s="abcdef";
    show_bytes((byte_pointer)s,strlen(s));
    show_int(val);
    show_float(fval);
    return 0;
}