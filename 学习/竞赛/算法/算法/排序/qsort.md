# 快排

[快排分析]: https://blog.csdn.net/insistGoGo/article/details/7785038	"三种快速排序以及快速排序的优化"

快速排序（英语：Quicksort），又称分区交换排序（英语：partition-exchange sort），简称快排，是一种被广泛运用的排序算法。

## 基本原理与实现

### 原理

快速排序的工作原理是通过 [分治](https://oi-wiki.org/basic/divide-and-conquer/) 的方式来将一个数组排序。

快速排序分为三个过程：

1. 将数列划分为两部分（要求保证相对大小关系）；
2. 递归到两个子序列中分别进行快速排序；
3. 不用合并，因为此时数列已经完全有序。

和归并排序不同，第一步并不是直接分成前后两个序列，而是在分的过程中要保证相对大小关系。具体来说，第一步要是要把数列分成两个部分，然后保证前一个子数列中的数都小于后一个子数列中的数。为了保证平均时间复杂度，一般是随机选择一个数 来当做两个子数列的分界。

之后，维护一前一后两个指针 和 ，依次考虑当前的数是否放在了应该放的位置（前还是后）。如果当前的数没放对，比如说如果后面的指针 遇到了一个比 小的数，那么可以交换 和 位置上的数，再把 向后移一位。当前的数的位置全放对后，再移动指针继续处理，直到两个指针相遇。

其实，快速排序没有指定应如何具体实现第一步，不论是选择 的过程还是划分的过程，都有不止一种实现方法。

第三步中的序列已经分别有序且第一个序列中的数都小于第二个数，所以直接拼接起来就好了。

## 迭代法

```c
typedef struct _Range {
    int start, end;
} Range;

Range new_Range(int s, int e) {
    Range r;
    r.start = s;
    r.end = e;
    return r;
}

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void quick_sort(int arr[], const int len) {
    if (len <= 0)
        return; // 避免len等於負值時引發段錯誤（Segment Fault）
    // r[]模擬列表,p為數量,r[p++]為push,r[--p]為pop且取得元素
    Range r[len];
    int p = 0;
    r[p++] = new_Range(0, len - 1);
    while (p) {
        Range range = r[--p];
        if (range.start >= range.end)
            continue;
        int mid = arr[(range.start + range.end) / 2]; // 選取中間點為基準點
        int left = range.start, right = range.end;
        do {
            while (arr[left] < mid) ++left;   // 檢測基準點左側是否符合要求
            while (arr[right] > mid) --right; //檢測基準點右側是否符合要求
            if (left <= right) {
                swap(&arr[left], &arr[right]);
                left++;
                right--;               // 移動指針以繼續
            }
        } while (left <= right);
        if (range.start < right) r[p++] = new_Range(range.start, right);
        if (range.end > left) r[p++] = new_Range(left, range.end);
    }
}
```

## 递归法

```c
void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}

void quick_sort_recursive(int arr[], int start, int end) {
    if (start >= end)
        return;
    int mid = arr[end];
    int left = start, right = end - 1;
    while (left < right) {
        while (arr[left] < mid && left < right)
            left++;
        while (arr[right] >= mid && left < right)
            right--;
        swap(&arr[left], &arr[right]);
    }
    if (arr[left] >= arr[end])
        swap(&arr[left], &arr[end]);
    else{
        left++;
        swap(&arr[left], &arr[end]);
    }
    if (left)
        quick_sort_recursive(arr, start, left - 1);
    quick_sort_recursive(arr, left + 1, end);
}

void quick_sort(int arr[], int len) {
    quick_sort_recursive(arr, 0, len - 1);
}
```

这道题用传统快排（如下所示）的结果就是最后三个点TLE：

```cpp
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    int i = left, j = right;
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
            j--;
        while (i < j && a[i] <= a[left])
            i++;
        swap(a[i], (i == j) ? a[left] : a[j]);  //i和j相遇则与枢轴元素交换，否则a[i]与a[j]交换
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}
```

因为快排对于一些特殊的情况（例如序列原本就有序、有大量重复元素等等）会进行很多完全不必要的操作，耗费大量时间。为此，我们基于上述普通快速排序算法一步步进行优化。

### 一、随机化

如果永远取第一个元素作为枢轴的话，在数组已经有序的情况下每次划分都将得到最坏的结果，时间复杂度退化为O(n^2)。因为其中一个子序列每次都只比原序列少一个元素，该侧的递归深度将达到最大。
然而，我们可以通过随机选取枢轴元素来打破这种固定模式，这样每次都是最坏划分的概率就非常小了。实现起来只需要先将随机选中的元素和第一个元素交换一下位置作为枢轴元素，然后就可以接着用原来的方法进行排序了。

```cpp
void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    **int i = left, j = right, pivot = rand() % (right - left + 1) + left;**
    **swap(a[left], a[pivot]);**
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
            j--;
        while (i < j && a[i] <= a[left])
            i++;
        swap(a[i], (i == j) ? a[left] : a[j]);
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}
```

### 二、小区间插入排序

当序列长度分割到足够小后，继续使用快速排序递归分割的效率反而没有直接插入排序高。因此我们可以增加一个判断，当区间长度小于10以后改为使用插入排序。

```cpp
void insertSort(int a[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    **if (right - left + 1 < 10)
    {
        insertSort(a, left, right);
        return;
    }**
    int i = left, j = right, pivot = rand() % (right - left + 1) + left;
    swap(a[left], a[pivot]);
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
            j--;
        while (i < j && a[i] <= a[left])
            i++;
        swap(a[i], (i == j) ? a[left] : a[j]);
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}
```

### 三、聚拢重复元素

完成了前两步优化后，代码成功AC了前四个点，但最后一个点还是TLE了。下载输入数据一看，竟然是100000个完全一样的数字……对于这种情况，如果还让程序傻傻地分割的确没有必要。于是我想出了一种聚拢重复元素的办法，专治这种变态的数据。
这种方法的主要思想是，在j向前扫描的过程中，每次遇到和枢轴元素相同的元素，就将其与前方第一个异于枢轴元素的元素交换位置，然后继续原本的工作。如果在i之前没有找到任何一个异于枢轴元素的元素，说明此时i与j之间已经全部都是与枢轴元素相同的重复元素了，这就把重复的元素都聚拢到了中间。这时我们再想办法把枢轴元素也加入到这个重复序列中，然后就不必继续向中间扫描了，直接以这个重复序列的两端作为分割线即可。同理，i向后扫描的过程中也可以运用这种思想。
思路应该还是比较好理解的，但是具体实现起来有些麻烦，有不少细节需要考虑到，为了解释方便我把它们都写在注释里。

```cpp
void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    if (right - left + 1 < 10)
    {
        insertSort(a, left, right);
        return;
    }
    int i = left, j = right, k, flag = 0, pivot = rand() % (right - left + 1) + left;
    swap(a[left], a[pivot]);
    //到这以前都和原来一样，主要就是下面的两个子while循环里分别增加了一个大的if判断
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
        {
            if (a[j] == a[left])  //如果当前扫描到的元素等于枢轴元素
            {
                for (k = j-1; k > i; k--)  //向前寻找第一个和枢轴元素不同的元素
                    if (a[k] != a[j])
                    {
                        swap(a[k], a[j]);  //如果找到了则交换，这样和枢轴元素相同的元素都往中间去了
                        break;
                    }
                if (k == i)  //如果k等于i，说明没找到，这时i和j之间都是重复元素了
                {
                    //我们想把枢轴元素也加进来，这时要分两种情况考虑
                    if (a[left] >= a[i])  //如果枢轴元素大等于a[i]，则直接交换后大小关系不会出问题，而枢轴元素会接在重复序列的左端
                        swap(a[left], a[i]);
                    else  //否则操作要复杂一些，建议认真体会模拟一下
                    {
                        swap(a[i], a[j]);  //较大的a[i]应该先和a[j]交换到重复序列右端，a[j]接到左端
                        swap(a[left], a[i-1]);  //然后再让枢轴元素继续接到左端，而a[i-1]因为一定比枢轴元素小所以可以换到更左边
                        i--;  //调整左右分割线的位置
                        j--;
                    }
                    flag = 1;  //标记表明聚拢已完成
                    break;
                }
                else continue;  //如果找到了一个异于枢轴元素的元素完成了交换，那么继续向前扫描
            }
            j--;
        }
        if (flag) break;  //如果聚拢已完成，则直接跳出大循环进行分割，i无需再向后扫描
        while (i < j && a[i] <= a[left])  //i向后扫描的过程基本类似
        {
            if (a[i] == a[left] && i != left)  //增加i!=left条件以跳过枢轴元素本身
            {
                for (k = i+1; k < j; k++)
                {
                    if (a[k] != a[i])
                    {
                        swap(a[k], a[i]);
                        break;
                    }
                }
                if (k == j)
                {
                	//这里比j向前扫描对应的地方简单一些，因为a[j]一定小于枢轴元素，无需分情况讨论
                    swap(a[left], a[j]);
                    flag = 1;
                    break;
                }
                else continue;
            }
            i++;
        }
        if (flag) break;
        //这里以后也和原来一样
        swap(a[i], (i == j) ? a[left] : a[j]);
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}
```

为了追求更快的速度，建议用scanf()和printf()来进行输入输出。经过这几步优化，最后快排终于也能顺利通过了！

完整AC代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int n, a[100010];

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void insertSort(int a[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
        for (int j = i; j > 0 && a[j] < a[j-1]; j--)
            swap(a[j], a[j-1]);
}

void quickSort(int a[], int left, int right)
{
    if (left >= right)
        return;
    if (right - left + 1 < 10)
    {
        insertSort(a, left, right);
        return;
    }
    int i = left, j = right, k, flag = 0, pivot = rand() % (right - left + 1) + left;
    swap(a[left], a[pivot]);
    while (i < j)
    {
        while (j > i && a[j] >= a[left])
        {
            if (a[j] == a[left])
            {
                for (k = j-1; k > i; k--)
                    if (a[k] != a[j])
                    {
                        swap(a[k], a[j]);
                        break;
                    }
                if (k == i)
                {
                    if (a[left] >= a[i])
                        swap(a[left], a[i]);
                    else
                    {
                        swap(a[i], a[j]);
                        swap(a[left], a[i-1]);
                        i--;
                        j--;
                    }
                    flag = 1;
                    break;
                }
                else continue;
            }
            j--;
        }
        if (flag) break;
        while (i < j && a[i] <= a[left])
        {
            if (a[i] == a[left] && i != left)
            {
                for (k = i+1; k < j; k++)
                {
                    if (a[k] != a[i])
                    {
                        swap(a[k], a[i]);
                        break;
                    }
                }
                if (k == j)
                {
                    swap(a[left], a[j]);
                    flag = 1;
                    break;
                }
                else continue;
            }
            i++;
        }
        if (flag) break;
        swap(a[i], (i == j) ? a[left] : a[j]);
    }
    quickSort(a, left, i-1);
    quickSort(a, j+1, right);
}

int main()
{
    srand((int)time(NULL));
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    quickSort(a, 0, n-1);
    for (int i = 0; i < n-1; i++)
        printf("%d ", a[i]);
    printf("%d\n", a[n-1]);
    return 0;
}
```