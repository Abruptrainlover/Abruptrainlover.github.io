#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
void Print(vector<int>v){
    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    cout<<endl;
}
int main(int argc,char argv[]){
    //vector ���캯��
    //  1��vector<T>v; Ĭ�Ϲ���
    //  2��vector(.begin(),v.end())  ��v.begin()��v.end()�����������������
    //  3��vector(n,elem) n��elem������
    //  4: vector(const vector *vec)�������캯��

    vector<int>v1;
    for(int i=0;i<10;i++){
        v1.push_back(5);
    }
    cout<<"Ĭ�Ϲ���v1:";
    Print(v1);
    vector<int>v2(v1.begin(),v1.end());
    cout<<"��������v2:";
    Print(v2);
    vector<int>v3(10,5);
    cout<<"��ֵ����v3:";
    Print(v3);
    vector<int>v4(v1);
    cout<<"��������v4:";
    Print(v4);
    //vector ��ֵ����
    //  1: operator=
    //  2: assign(begin,end)
    //  3: assign(n,elem)

    //vector �����Ƿ�Ϊ�ռ����С
    //  empty()
    //  capacity()          capacity��С�����size��С���ı�,������capacity��Զ��size��,����size��Сʱcapacity�����С
    //  size()
    //  resize(int num)
    //  resize(int num,elem)
    cout<<" v1�����Ƿ�Ϊ��"<<v1.empty()<<endl;
    cout<<"v1 ������: "<<v1.capacity()<<endl;
    cout<<"v1�Ĵ�С: "<<v1.size()<<endl;
    cout<<"��v1����ָ����СΪ15��:"<<endl;
    v1.resize(15);
    Print(v1);
    v1.resize(20,100);
    cout<<"��v1ָ����СΪ20,��ָ������100"<<endl;
    Print(v1);
    cout<<"��ʱv1��������СΪ: "<<v1.capacity()<<endl;
    //vector�����ɾ��
    //  push_back() β������Ԫ��ele
    //  pop_back()  ɾ�����һ��Ԫ��
    //  insert(const_iterator pos,ele)  ������ָ��λ�ò���Ԫ��ele
    //  insert(const_iterator pos,int count ,ele)   //������ָ��λ�ò���count��ele
    //  erase(const_iterator pos)   ɾ��������ָ��λ�õ�Ԫ��
    //  erase(const_iterator start,const_iterator end)  ɾ����������start��end֮���Ԫ��
    //  clear() //ɾ������������Ԫ��

    v2.push_back(100);
    v2.insert(v2.begin(),100);
    v2.insert(v2.begin(),2,1000);
    cout<<"������v2:"<<endl;
    Print(v2);
    cout<<"ɾ�����v2"<<endl;
    v2.erase(v2.begin(),v2.end());
    Print(v2);
    cout<<"v2 ������СΪ:"<<v2.capacity()<<endl;
    //Ԫ�ط���
    //  1:[]
    //  2:at()
    //  3:front()
    //  4:back()

    //��������
    //  swap()          �������������ڴ��С
    cout<<"����ǰv1,v3����:"<<endl;
    cout<<"v1"<<endl;
    Print(v1);
    Print(v3);
    
    cout<<"������:"<<endl;
    v1.swap(v3);
    Print(v1);
    Print(v3);
    v3.resize(3);
    cout<<"���¶����Сǰv3������:"<<v1.capacity()<<endl;
    vector<int>(v3).swap(v3);
    cout<<"�����СΪ3��������v3������:"<<v3.capacity()<<endl;
    //vectorԤ���ռ�
    int num=0,num1=0;
    int *p=NULL;
    for(int i=0;i<100000;i++){
        v4.push_back(i);
        if(p!=&v4.at(0)){
            p=&v4.at(0);
            num++;
        }
        
    }
    cout<<"��Ԥ�������ݴ���num= "<<num<<endl;
    v1.reserve(100000+v1.size());
    p=NULL;
    num=0;
    for(int i=0;i<100000;i++){
        v1.push_back(i);
        if(p!=&v4.at(0)){
            p=&v4.at(0);
            num++;
        }
        
    }
    cout<<"Ԥ���ռ�����ݴ���num= "<<num<<endl;
    cout<<"v1Ԥ���ռ��������С:"<<v1.capacity()<<endl;
    
    return 0;
}