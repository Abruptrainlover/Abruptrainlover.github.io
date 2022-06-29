#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
const int W = 100010;

int n, w, a[N], cnt[W], b[N]; //cnt存储对应元素的个数

void counting_sort(int n) {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i]];
  for (int i = 1; i <=N ; ++i) cnt[i] += cnt[i - 1]; //叠加
  for (int i = n; i >= 1; --i) b[cnt[a[i]]--] = a[i];
}
int main(void){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)  cin>>a[i];
  counting_sort(n);
  for(int i=1;i<=N;i++)  if(b[i]) cout<<b[i]<<" ";
  return 0;
}