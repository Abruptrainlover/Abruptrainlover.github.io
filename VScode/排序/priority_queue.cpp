#include<bits/stdc++.h>
#include<cmath>
using namespace std;
typedef long long LL;
const int cof[3]={2,3,5};
int main(void){
    int count=1;
    char str[80];
    sprintf(str,"pi is = %f",3.1415926);
    //puts(str);
    cout<<str;
    priority_queue<LL,vector<LL>,greater<LL>>pq;
    set<LL> s;
    pq.push(1);
    s.insert(1);
    for(int i=1;i<100;i++){
        LL x=pq.top();pq.pop();
        //if(i==1500){
        //    printf("the%d :%d  ",i,x);
        //    break;
        //}
        for(int j=0;j<3;j++){
            LL x2=x*cof[j];
            if(!s.count(x2)) {s.insert(x2);pq.push(x2);}
        }
    }
    // for (auto iter = s.begin(); iter != s.end(); ++iter) {
        
    //     cout <<"the"<<count++ <<":"<< *iter << endl;
    // }
    while (!pq.empty())
    {
        cout<<"the"<<count++<<":"<<pq.top();
        pq.pop();
    }

    
    
    return 0;
}