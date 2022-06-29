
#include <algorithm>
#include <iostream>
#include <utility>

void radix_sort(int n, int a[]) {
  int *b = new int[n];  // 临时空间
  int *cnt = new int[1 << 8];
  int mask = (1 << 8) - 1;
  int *x = a, *y = b;
  for (int i = 0; i < 32; i += 8) {
    for (int j = 0; j != (1 << 8); ++j) cnt[j] = 0;//初始化
    for (int j = 0; j != n; ++j) ++cnt[x[j] >> i & mask];
    for (int sum = 0, j = 0; j != (1 << 8); ++j) {
      // 等价于 std::exclusive_scan(cnt, cnt + (1 << 8), cnt, 0);
      sum += cnt[j],cnt[j] = sum - cnt[j];
    }
    for (int j = 0; j != n; ++j) y[cnt[x[j] >> i & mask]++] = x[j];
    std::swap(x, y);
  }
  delete[] cnt;
  delete[] b;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  int *a = new int[n];
  for (int i = 0; i < n; ++i) std::cin >> a[i];
  radix_sort(n, a);
  for (int i = 0; i < n; ++i) std::cout << a[i] << ' ';
  delete[] a;
  return 0;
}

// #include<bits/stdc++.h>
// const int N = 100010;
// const int W = 100010;
// const int K = 100;

// int n, w[K], k, cnt[W];
// char Char_a[N][K];
// struct Element {
//   int key[K];

//   bool operator<(const Element& y) const {
//     // 两个元素的比较流程
//     for (int i = 0; i < k; ++i) {
//       if (key[i] == y.key[i]) continue;
//       return key[i] < y.key[i];
//     }
//     return false;
//   }
// } a[N], b[N];

// void counting_sort(int p) {
//   memset(cnt, 0, sizeof(cnt));
//   for (int i = 0; i < n; ++i) ++cnt[a[i].key[p]];
//   for (int i = 0; i < w[p]; ++i) cnt[i] += cnt[i - 1];
//   // 为保证排序的稳定性，此处循环i应从n到1
//   // 即当两元素关键字的值相同时，原先排在后面的元素在排序后仍应排在后面
//   for (int i = n-1; i >= 0; --i) b[cnt[a[i].key[p]]--] = a[i];
//   memcpy(a, b, sizeof(a));
// }

// void Trans(char* char_a,Element New_b){
//       for(int j=0;j<k;j++)
//         New_b.key[j]=char_a[j]-'0';
    
// }
// void radix_sort() {
//   for (int i = k-1; i >= 0; --i) {
//     // 借助计数排序完成对关键字的排序
//     counting_sort(i);
//   }
// }
// int main(void){
//   scanf("%d %d",&n,&k);
//   for(int i=0;i<n;i++)
//     scanf("%s",Char_a[i]);
//   for(int i=0;i<n;i++)
//     Trans(Char_a[i],a[i]);
//   radix_sort();
//   for(int i=0;i<n;i++){
//     for(int j=0;j<k;j++)
//       printf("%d",a[i].key[j]);
//     printf(" ");
//   }
//   return 0;
// }
