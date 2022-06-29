
/***** 这里以字符串进行展示  字符串可泛化性好 ******/
 
#include<iostream>
#include<vector>
#define N 100
using namespace std;
 
/*******打出1-n的阶乘表*******/
int f[N];
int x, num;
 
void jie_cheng(int n)
{
    f[0] = f[1] = 1; // 0的阶乘为1
    for(int i = 2; i <= n; i++) f[i] = f[i - 1] * i;
}
 
/**************康托逆展开**************/
 
vector<char> vec; //存需要排列的字符
void rev_kangtuo(int k) //输出序号为 k 的字符序列
{
    int n = vec.size(), len = 0;
    string ans = "";
    k--; // 算的时候是按 12345 是第0位
    for(int i = 1; i <= n; i++){
        int t = k / f[n - i]; // 第 i 位需要 第 t + 1 大的数
        k %= f[n - i];        //剩下的几位需要提供的排列数
        ans += vec[t] ; //  vec[t] 就是第 t + 1 大的数
        vec.erase(vec.begin() + t); 
//用过就删了，不用vector用暴力也可以，就是说枚举，然后一个一个的比较大小，并记录有几个没用过的字符且字典序比它小
    }
    cout << ans << '\n';
}
 
/***************************************/
// 假设展开后不超过10位
int main()
{
    jie_cheng(10); // 预处里好阶乘
    scanf("%d", &x); // 输入需要逆展开的数字
    /************康托逆展开***********/
    for(int i = 1; i <= 10; i++)
    {
    	if(x / f[i] == 0) // 求出 x 逆展开所需的最小的位数，方便下面的初始化
    	{
    		num = i;
    		break;
    	}
    }
    for(int i = 1; i <= num; i++) vec.push_back(i + '0'); //输入的位数只要不小于num就可以
    rev_kangtuo(x);
    return 0;
}
