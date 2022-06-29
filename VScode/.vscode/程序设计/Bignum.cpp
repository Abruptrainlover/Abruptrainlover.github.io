#include<bits/stdc++.h>
using namespace std;
static const int LEN = 1004;
int a[LEN],b[LEN],c[LEN],d[LEN];
void clear(int a[]) {
  for (int i = 0; i < LEN; ++i) a[i] = 0;
}

void read(int a[]) {
  static char s[LEN + 1];
  scanf("%s", s);

  clear(a);

  int len = strlen(s);
  // ������������ת
  for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
  // s[i] - '0' ���� s[i] ����ʾ������
  // ��Щͬѧ���ܸ�ϰ���� ord(s[i]) - ord('0') �ķ�ʽ����
}
void print(int a[]) {
  int i;
  for (i = LEN - 1; i >= 1; --i)
    if (a[i] != 0) break;
  for (; i >= 0; --i) putchar(a[i] + '0');
  putchar('\n');
}

void add(int a[], int b[], int c[]) {
  clear(c);

  // �߾���ʵ���У�һ�����������󳤶� LEN �ȿ��ܵ������һЩ
  // Ȼ����ȥĩβ�ļ���ѭ��������һ������ʡȥ���ٱ߽�����Ĵ���
  // ��Ϊʵ�����벻�ᳬ�� 1000 λ�����ڴ�ѭ���� LEN - 1 = 1003 �Ѿ��㹻
  for (int i = 0; i < LEN - 1; ++i) {
    // ����Ӧλ�ϵ��������
    c[i] += a[i] + b[i];
    if (c[i] >= 10) {
      // ��λ
      c[i + 1] += 1;
      c[i] -= 10;
    }
  }
}
void sub(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // ��λ���
    c[i] += a[i] - b[i];
    if (c[i] < 0) {
      // ��λ
      c[i + 1] -= 1;
      c[i] += 10;
    }
  }
}

void mul(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];
    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10;
      c[i] %= 10;
    }
  }
}

// ������ a ���±� last_dg Ϊ���λ���Ƿ�����ټ�ȥ���� b �����ַǸ�
// len �ǳ��� b �ĳ��ȣ����ⷴ������
inline bool greater_eq(int a[], int b[], int last_dg, int len) {
  // �п��ܱ�����ʣ��Ĳ��ֱȳ�������������������� 1 λ��������жϼ���
  if (a[last_dg + len] != 0) return true;
  // �Ӹ�λ����λ����λ�Ƚ�
  for (int i = len - 1; i >= 0; --i) {
    if (a[last_dg + i] > b[i]) return true;
    if (a[last_dg + i] < b[i]) return false;
  }
  // ��ȵ�������Ҳ�ǿ��е�
  return true;
}
void div(int a[], int b[], int c[], int d[]) {
  clear(c);
  clear(d);

  int la, lb;
  for (la = LEN - 1; la > 0; --la)
    if (a[la - 1] != 0) break;
  for (lb = LEN - 1; lb > 0; --lb)
    if (b[lb - 1] != 0) break;
  if (lb == 0) {
    puts("> <");
    return;
  }  // ��������Ϊ��

  // c ����
  // d �Ǳ�������ʣ�ಿ�֣��㷨��������Ȼ��Ϊ����
  for (int i = 0; i < la; ++i) d[i] = a[i];
  for (int i = la - lb; i >= 0; --i) {
    // �����̵ĵ� i λ
    while (greater_eq(d, b, i, lb)) {
      // �����Լ������
      // ��һ����һ���߾��ȼ���
      for (int j = 0; j < lb; ++j) {
        d[i + j] -= b[j];
        if (d[i + j] < 0) {
          d[i + j + 1] -= 1;
          d[i + j] += 10;
        }
      }
      // ʹ�̵���һλ���� 1
      c[i] += 1;
      // ����ѭ����ͷ�����¼��
    }
  }
}

int main(void){
    read(a);
    read(b);
    add(a,b,c);
    printf("add:");
    print(c);
    sub(a,b,c);
    printf("sub:");
    print(c);
    mul(a,b,c);
    printf("mul:");
    print(c);
    div(a,b,c,d);
    printf("div:");
    print(c);
    return 0;
}