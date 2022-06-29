// C++ Version
#include<bits/stdc++.h>
#define N 105
int a[N];
void swap(int *a,int* b){
    int s=*a;
    *a=*b;
    *b=s;
}
void selection_sort(int* a, int n) {
  for (int i = 0; i < n; ++i) {
    for(int j=0;j<i;j++){
        if(a[j]>a[i]){
            swap(&a[j],&a[i]);
        }
    }
  }
}
void Selection_sort(int* a, int n) {
  for (int i = 0; i < n-1; ++i) {
    int ith = i;
    for (int j = i + 1; j < n; ++j) {
      if (a[j] < a[ith]) {
        ith = j;
      }
    }
    int t = a[i];
    a[i] = a[ith];
    a[ith] = t;
  }
}
int main(void){
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    Selection_sort(a,n);
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    return 0;
}