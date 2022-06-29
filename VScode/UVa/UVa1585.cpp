#include<stdio.h>
#include<string.h>
#define M 85
char s[M];
int main(){
    int i=0;
    int flag=0,sum=0;
    scanf("%s",s);
    int c=strlen(s);
    while (s[i]!=EOF)
    {
        if(s[i]=='O'){
            flag++;
        }
        else    flag=0;
        sum+=flag;
        i++;
    }
    printf("%d",sum);
    return 0;
}