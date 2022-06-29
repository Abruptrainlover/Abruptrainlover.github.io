#include<bits/stdc++.h>
#define N 105
int a[N];
void Input(int *a,int n){
    int i;
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
}
void Print(int *a,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%d ",a[i]);
    }
}
void insertion_sort(int* a, int n) {
  for (int i = 1; i < n; ++i) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
}
int main(void){
    int n,i;
    scanf("%d",&n);
    Input(a,n);
    insertion_sort(a,n);
    Print(a,n);
    return 0;
}