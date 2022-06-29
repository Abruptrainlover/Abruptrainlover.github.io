
/***** �������ַ�������չʾ  �ַ����ɷ����Ժ� ******/
 
#include<iostream>
#include<vector>
#include<string>
#define N 100
using namespace std;
 
/*******���1-n�Ľ׳˱�*******/
int f[N];
void jie_cheng(int n)
{
    f[0] =1; f[1] = 1; // 0�Ľ׳�Ϊ1
    for(int i = 2; i <= n; i++) f[i] = f[i - 1] * i;
}
 
/**************����չ��****************/

int Cantor(string str)
{
    int ans = 1;  //ע�⣬��Ϊ 12345 ������0��ʼ����ģ������Ҫ��12345�����ǵ�һ��
    int len = str.length();
    for(int i = 0; i < len; i++){
        int tmp = 0;//����������
 
        for(int j = i + 1; j < len; j++){
            if(str[i] > str[j]) tmp++;
            //����str[i]�ǵڼ������������˵�����м�������С����
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