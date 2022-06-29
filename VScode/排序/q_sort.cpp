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