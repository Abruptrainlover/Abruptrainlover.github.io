#include<bits/stdc++.h>
const int N=100000;
// C++ Version
int a[N];
void shell_sort(int a[], int length) {
  int h = 1;
  while (h < length / 3) {
    h = 3 * h + 1;
  }
  while (h >= 1) {
    for (int i = h; i < length; i++) {
      for (int j = i; j >= h && a[j] < a[j - h]; j -= h) {
        std::swap(a[j], a[j - h]);
      }
    }
    h = h / 3;
  }
}
  int main(void){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) std::cin>>a[i];
    shell_sort(a,n);
    for(int i=0;i<n;i++) std::cout<<a[i]<<" ";
    return 0;
  }
