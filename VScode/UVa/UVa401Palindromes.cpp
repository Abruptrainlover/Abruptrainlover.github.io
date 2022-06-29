#include<stdio.h>
#include<string.h>
#include<ctype.h>
const char* rev="A   3  HIL JM O   2TUVWXY51SE Z  8 ";  //标准结果数组，前二十六为字母
const char* msg[]={"is not a palindrome.","is a regular palindrome.","is a mirrored string.","is a mirrored palindrome"};
char r(char s){
    if(isalpha(s))  return rev[s-'A'];      //如果为字母，就在直接从零开始查找
    return rev[s-'0'+25];                   //如果不是字母，就是数字，数组的镜像储存在25-34，所以这样写
}
int main(){
    
    
    char s[30];
    
    while (scanf("%s",s)==1)
    {   int rs=1,m=1;
        int len=strlen(s);
        for(int i=0;i<(len+1)/2;i++){
            if(s[i]!=s[len-1-i])    rs=0;
            if(r(s[i])!=s[len-i-1]) m=0;    //绝妙的判断，直接载入结果，然后自动在结果里面查找，
        }
       printf("%s -- %s",s,msg[m*2+rs]);    //前两个是关于回文数的，后两个是关于镜像数的，所以这样写
        
    }
    return 0;
}