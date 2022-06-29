#include<bits/stdc++.h>
static const int LEN = 1004;

int a[LEN], b[LEN], c[LEN];

void read(int a[]) {
  static char s[LEN + 1];     //��̬
  scanf("%s", s);

  int len = strlen(s);
   // ��ת
  for (int i=0; i<len; ++i) 
    a[len - i - 1] = s[i] - '0';      // s[i] - '0' ���� s[i] ����ʾ����ֵ
}

void print(int a[]) {
  int i;
  for (i=LEN-1;i>=1;--i)              //�����ж������޶�Ϊi>=0;�����Ļ�ִ����i=-1,�ᵼ�������
    if (a[i] != 0) break;
  for (; i>=0;--i) 
    putchar(a[i] + '0');
  putchar('\n');
}
int judge(int a[],int b[]){
  int i,j,k;
  //�ֱ����λ
  for(i=LEN-1; i>=0;--i)
    if(a[i]!=0) 
      break;
  
  for(j=LEN-1; j>=0; --j)
    if(b[j] != 0)   break;
  //�ֱ��ж�
  if(i < j)   
    return 0;
  else if(i>j) 
    return 1;
  for(; i>= 0;--i){
    if(a[i]<b[i]) return 0;
  }
  return 1;
}
void add(int a[], int b[], int c[]) {


  for (int i = 0; i < LEN - 1; ++i) {
    c[i]+=a[i]+b[i];    // ����Ӧλ�ϵ��������
    if (c[i] >= 10) {
      c[i + 1]+=1;
      c[i]-=10;
    }
  }
}
void sub(int a[], int b[], int c[]) {
  
  for (int i=0;i<LEN-1;++i) {
    c[i]+=a[i]-b[i];    // ��λ���
    if (c[i]<0) {
      c[i+1]-=1;
      c[i]+=10;
    }
  }
}
int main() {
  printf("Please make sure the first num is larger than the second.\nAnd make sure the maximum number of digits is 1000 \n");
  read(a);  read(b);

  printf(" the result of add is: ");
  add(a, b, c);
  print(c);
  for (int i=0; i<LEN; ++i) 
    c[i] = 0;
  printf(" the result of sub is: ");
  if(judge(a,b)) sub(a,b,c);
  else {  putchar('-'); sub(b,a,c);}
  
  print(c);
  return 0;
}