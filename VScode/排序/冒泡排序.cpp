
// C++ Version
// ��������Ĵ�С��n+1��ð������������±�1��ʼ
#include<bits/stdc++.h>
#define N 105
int a[N];
void bubble_sort(int *a, int n) {
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < n-1; ++i) {
      if (a[i] <a[i + 1]) {
        flag = true;
        int t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  }
}
int main(void){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    bubble_sort(a,n);
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}