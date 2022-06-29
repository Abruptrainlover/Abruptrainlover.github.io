#include<stdio.h>
#include<string.h>
char s[]="`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./";
int main(){
    int i,c;
    while ((c=getchar())!=EOF)
    {
        for(i=1;s[i]&&c!=s[i];i++)  ;
        if(s[i])
            putchar(s[i-1]);
        else putchar(c);
    }
    return 0;
}