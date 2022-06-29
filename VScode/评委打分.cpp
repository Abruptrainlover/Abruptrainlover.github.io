#include<iostream>
#include<vector>
#include<deque>
#include<string>
#include<algorithm>
#include<ctime>
using namespace std;
class Person{
    public:
    Person(string name,int score){
        this->m_Name=name;
        this->m_Score=score;
    }
    string m_Name;
    int m_Score;    //平均分
};
void creatPerson(vector<Person>&v){
    string nameSeed="ABCDE";
    for(int i=0;i<5;i++){
        string name ="选手";
        name+=nameSeed[i];
        int score =0;
        Person p(name,score);
        v.push_back(p); 
    }
}
void setScore(vector<Person>&v){
    for(vector<Person>::iterator it=v.begin();it!=v.end();it++){
        deque<int>d;
        int sum=0;
        for(int i=0;i<10;i++){
            int score=rand()%41+60;
            d.push_back(score);
        }
        cout<<"选手: "<<it->m_Name<<" 得分:"<<it->m_Score<<endl;
        for(deque<int>::iterator dit=d.begin();dit!=d.end();dit++){
            cout<<*dit<<" ";
        }
        cout<<endl;
        sort(d.begin(),d.end());
        d.pop_back();
        d.pop_front();
        for(deque<int>::iterator dit=d.begin();dit!=d.end();dit++){
            sum+=*dit;
        }
        int avg=sum/d.size();
        (*it).m_Score=avg;
    }
}
void showScore(vector<Person>&v){
     for(vector<Person>::iterator it=v.begin();it!=v.end();it++){
         cout<<"选手: "<<it->m_Name<<" 得分:"<<it->m_Score<<endl;
     }
}
int main(int argc,char argv[]){
    srand((int)time(NULL));
    vector<Person>v;
    creatPerson(v);
    // for(vector<Person>::iterator it=v.begin();it!=v.end();it++){
    //     cout<<"name= "<<(*it).m_Name<<" score= "<<(*it).m_Score<<endl;

    // }
    
    setScore(v);
    showScore(v);
    return 0;
}