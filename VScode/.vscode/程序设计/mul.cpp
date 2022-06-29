#include<bits/stdc++.h>
#define LEN 5001
int a[LEN],b[LEN],c[LEN+LEN];
void read(int a[]){
    char s[LEN];
    int i;
    scanf("%s",s);
    int len=strlen(s);
    for(int j=0;j<len;j++)
        a[j]=s[len-j-1]-'0';
}
void print(int a[]){
    int i;
    for(i=2*LEN-1;i>0;i--)
        if(a[i]!=0) break;
    for(int j=i;j>=0;j--)   printf("%d",a[j]);
}
void mul(void) {
  for (int i = 0; i < LEN-1; ++i) {
    
    for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];

    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10;
      c[i] %= 10;
    }
  }
}
int main(void){
    read(a);read(b);
    mul();
    print(c);
    return 0;
}