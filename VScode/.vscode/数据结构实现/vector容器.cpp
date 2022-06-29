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
    //vector 构造函数
    //  1：vector<T>v; 默认构造
    //  2：vector(.begin(),v.end())  将v.begin()到v.end()区间的数拷贝给本身
    //  3：vector(n,elem) n个elem给本身
    //  4: vector(const vector *vec)拷贝构造函数

    vector<int>v1;
    for(int i=0;i<10;i++){
        v1.push_back(5);
    }
    cout<<"默认构造v1:";
    Print(v1);
    vector<int>v2(v1.begin(),v1.end());
    cout<<"拷贝构造v2:";
    Print(v2);
    vector<int>v3(10,5);
    cout<<"赋值构造v3:";
    Print(v3);
    vector<int>v4(v1);
    cout<<"拷贝构造v4:";
    Print(v4);
    //vector 赋值操作
    //  1: operator=
    //  2: assign(begin,end)
    //  3: assign(n,elem)

    //vector 容器是否为空及其大小
    //  empty()
    //  capacity()          capacity大小会根据size大小而改变,并保存capacity永远比size大,但当size减小时capacity不会减小
    //  size()
    //  resize(int num)
    //  resize(int num,elem)
    cout<<" v1容器是否为空"<<v1.empty()<<endl;
    cout<<"v1 的容量: "<<v1.capacity()<<endl;
    cout<<"v1的大小: "<<v1.size()<<endl;
    cout<<"将v1重新指定大小为15后:"<<endl;
    v1.resize(15);
    Print(v1);
    v1.resize(20,100);
    cout<<"将v1指定大小为20,且指定补充100"<<endl;
    Print(v1);
    cout<<"此时v1的容量大小为: "<<v1.capacity()<<endl;
    //vector插入和删除
    //  push_back() 尾部插入元素ele
    //  pop_back()  删除最后一个元素
    //  insert(const_iterator pos,ele)  迭代器指向位置插入元素ele
    //  insert(const_iterator pos,int count ,ele)   //迭代器指向位置插入count个ele
    //  erase(const_iterator pos)   删除迭代器指向位置的元素
    //  erase(const_iterator start,const_iterator end)  删除迭代器从start到end之间的元素
    //  clear() //删除容器中所有元素

    v2.push_back(100);
    v2.insert(v2.begin(),100);
    v2.insert(v2.begin(),2,1000);
    cout<<"插入后的v2:"<<endl;
    Print(v2);
    cout<<"删除后的v2"<<endl;
    v2.erase(v2.begin(),v2.end());
    Print(v2);
    cout<<"v2 容器大小为:"<<v2.capacity()<<endl;
    //元素访问
    //  1:[]
    //  2:at()
    //  3:front()
    //  4:back()

    //容器互换
    //  swap()          可以用来收缩内存大小
    cout<<"互换前v1,v3容器:"<<endl;
    cout<<"v1"<<endl;
    Print(v1);
    Print(v3);
    
    cout<<"交换后:"<<endl;
    v1.swap(v3);
    Print(v1);
    Print(v3);
    v3.resize(3);
    cout<<"重新定义大小前v3的容量:"<<v1.capacity()<<endl;
    vector<int>(v3).swap(v3);
    cout<<"定义大小为3并收缩后v3的容量:"<<v3.capacity()<<endl;
    //vector预留空间
    int num=0,num1=0;
    int *p=NULL;
    for(int i=0;i<100000;i++){
        v4.push_back(i);
        if(p!=&v4.at(0)){
            p=&v4.at(0);
            num++;
        }
        
    }
    cout<<"不预留是扩容次数num= "<<num<<endl;
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
    cout<<"预留空间后扩容次数num= "<<num<<endl;
    cout<<"v1预留空间后容量大小:"<<v1.capacity()<<endl;
    
    return 0;
}