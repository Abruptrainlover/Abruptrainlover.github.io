#include<stdio.h>
#include<string.h>
#include<ctype.h>
const char* rev="A   3  HIL JM O   2TUVWXY51SE Z  8 ";  //��׼������飬ǰ��ʮ��Ϊ��ĸ
const char* msg[]={"is not a palindrome.","is a regular palindrome.","is a mirrored string.","is a mirrored palindrome"};
char r(char s){
    if(isalpha(s))  return rev[s-'A'];      //���Ϊ��ĸ������ֱ�Ӵ��㿪ʼ����
    return rev[s-'0'+25];                   //���������ĸ���������֣�����ľ��񴢴���25-34����������д
}
int main(){
    
    
    char s[30];
    
    while (scanf("%s",s)==1)
    {   int rs=1,m=1;
        int len=strlen(s);
        for(int i=0;i<(len+1)/2;i++){
            if(s[i]!=s[len-1-i])    rs=0;
            if(r(s[i])!=s[len-i-1]) m=0;    //������жϣ�ֱ����������Ȼ���Զ��ڽ��������ң�
        }
       printf("%s -- %s",s,msg[m*2+rs]);    //ǰ�����ǹ��ڻ������ģ��������ǹ��ھ������ģ���������д
        
    }
    return 0;
}