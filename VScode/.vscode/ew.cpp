#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct student{
     string name;
    int sum;
    int score;
}student;
int main(void){
    int n;
     cin >> n;
     vector<student> a;
     for(int i=0;i<n;i++){
     student b;
     cin >> b.name;
     int sum=0;
     int score;
     int t;
     for(int j=0;j<5;j++){
     cin >> t;
    sum+=t;
}
     cin >> score;
    sum+=score;
    b.score=score;
     b.sum=sum;
    a.push_back(b);
     }
     vector<int> index(a.size());
    for(int i=0;i<a.size();i++){
    index[i]=i;
}
    for(int i=0;i<a.size();i++){
    for(int j=i+1;j<a.size();j++){
     int n1=index[i];
    int n2=index[j];
    if(a[n1].sum>a[n2].sum||(a[n1].sum==a[n2].sum&&a[n1].score>a[n2].score)){
    swap(index[i],index[j]);
     }
     }
     }
     for(int i=index.size()-1;i>=0;i--){
    int so=index[i];
    cout << a[so].name << " " << a[so].sum << " " << a[so].score << endl;
    }
    return 0;
    }