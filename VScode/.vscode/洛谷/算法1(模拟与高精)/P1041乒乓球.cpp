
#include<iostream>
using namespace std;
char a[62525];
void cmp(int k){
    int i=0;
    int H=0,D=0;
    while(a[i]!='E'){
        if(a[i]=='W') H++;
        else if(a[i]=='L')  D++;
        if(H<(k-1)||D<(k-1)){
            if(H==(k)){
                printf("%d:%d\n",H,D);
                H=0;D=0;
            }
            if(D==(k)){
                printf("%d:%d\n",H,D);
                H=0;D=0;
            }
        }
        else {
            if(H-D>1){
               printf("%d:%d\n",H,D);
                H=0;D=0;
            }
            if(D-H>1){
                printf("%d:%d\n",H,D);
                H=0;D=0;
            }
        }
        i++;
    }
    printf("%d:%d\n\n",H,D);
}
int main(void){
    int i;
    char s;
    for(i=0; cin >> s && s!='E';i++){
        a[i]=s;
    }
    a[i]='E';
    cmp(11);
    cmp(21);
    return 0;
}