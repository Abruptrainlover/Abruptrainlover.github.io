
/***** 这里以字符串进行展示  字符串可泛化性好 ******/
 
#include<iostream>
#include<vector>
#include<string>
#define N 100
using namespace std;
 
/*******打出1-n的阶乘表*******/
int f[N];
void jie_cheng(int n)
{
    f[0] =1; f[1] = 1; // 0的阶乘为1
    for(int i = 2; i <= n; i++) f[i] = f[i - 1] * i;
}
 
/**************康托展开****************/

int Cantor(string str)
{
    int ans = 1;  //注意，因为 12345 是算作0开始计算的，最后结果要把12345看作是第一个
    int len = str.length();
    for(int i = 0; i < len; i++){
        int tmp = 0;//用来计数的
 
        for(int j = i + 1; j < len; j++){
            if(str[i] > str[j]) tmp++;
            //计算str[i]是第几大的数，或者说计算有几个比他小的数
        }
 
        ans += tmp * f[len - i - 1];
    }
    return ans;
}
 
int main(void)
{
    jie_cheng(10);
    string str;
    cin>>str;
    cout<<Cantor(str)<<endl;
    return 0;
}