#include<iostream>
#include<stack>
using namespace std;
int main(int argc,char argv[]){
    int a=(1+2)/2;
    stack<int>s;
    for(int i=0;i<5;i++){
        s.push(i);
    }
    while (!s.empty())
    {   
        cout<<s.top()<<endl;
        s.pop();
    }
    cout<<"此时栈的大小为: "<<s.size()<<endl;
    cout<<a<<endl;
    return 0;
}