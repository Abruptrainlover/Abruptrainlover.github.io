#include<bits/stdc++.h>
#define f(i,n,m) for(i=n;i<m;i++)
using namespace std;
int a[100001];
void sift_down(int arr[], int start, int end) {
  // ���㸸�����ӽ����±�
  int parent = start;
  int child = parent * 2 + 1;
  while (child <= end) {  // �ӽ���±��ڷ�Χ�ڲ����Ƚ�
    // �ȱȽ������ӽ���С��ѡ������
    if (child + 1 <= end && arr[child] < arr[child + 1]) child++;
    // ����������ӽ��󣬴��������ϣ�ֱ����������
    if (arr[parent] >= arr[child])
      return;
    else {  // ���򽻻��������ݣ��ӽ���ٺ�����Ƚ�
      swap(arr[parent], arr[child]);
      parent = child;
      child = parent * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // �����һ���ڵ�ĸ��ڵ㿪ʼ sift down ����ɶѻ� (heapify)
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // �Ƚ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ�������������µ������յ�����Ԫ��֮ǰ��Ԫ�أ���ֱ���������
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}
int main(void){
    int i,n;
    cin>>n;
    f(i,0,n)    cin>>a[i];
    heap_sort(a,n);
    f(i,0,n)    cout<<a[i]<<" ";
    return 0;
}