#include<deque>
#include<iostream>
using namespace std;
void PrintD(deque<int>d){
    for(deque<int>::iterator it=d.begin();it!=d.end();it++)
        cout<<*it<<" ";
    cout<<endl;
}
int main(int argc,char argv[]){
    printf("hello world");
    return 0;
}