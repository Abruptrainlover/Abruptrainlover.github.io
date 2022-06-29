// #include<iostream>
// #include<algorithm>
#include<bits/stdc++.h>
using namespace std;
int a[10];
int main(void){
    for(int i=0;i<10;i++){
        cin>>a[i];
    }
    sort(a,a+10);
    for(int i=0;i<10;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}