# STL

STL 的基本观念就是将数据和操作分离。数据由容器进行管理，操作则由算法进行，而迭代器在两者之间充当粘合剂，使任何算法都可以和任何容器交互运作.

<!-more>

## STL基本组成

- **容器**（Containers）：用来管理某类对象的集合。各种数据结构，如vector、list、deque、set、map等,用来存放数据，从实现角度来看，STL容器是一种class template。
- **算法**（Algorithms）：用来处理对象集合中的元素，各种常用的算法，如sort、find、copy、for_each。从实现的角度来看，STL算法是一种function template。
- **迭代器**（Iterators）：用来在一个对象集合的元素上进行遍历动作。扮演了容器与算法之间的胶合剂，共有五种类型，从实现角度来看，迭代器是一种将operator* , operator-> , operator++, operator–等指针相关操作予以重载的class template。所有STL容器都附带有自己专属的迭代器，只有容器的设计者才知道如何遍历自己的元素。原生指针(native pointer)也是一种迭代器。
- **仿函数**：行为类似函数，可作为算法的某种策略。从实现角度来看，仿函数是一种重载了operator()的class 或者class template。
- **适配器**：一种用来修饰容器或者仿函数或迭代器接口的东西。
- **空间配置器**：负责空间的配置与管理。从实现角度看，配置器是一个实现了动态空间配置、空间管理、空间释放的class tempalte。

### STL头文件

| <iterator> | <functional> | <vector>  | <deque>  |
| ---------- | ------------ | --------- | -------- |
| <list>     | <queue>      | <stack>   | <set>    |
| <map>      | <algorithm>  | <numeric> | <memory> |
| <utility>  |              |           |          |

### STL容器

#### 序列式容器

> 每个元素均有固定位置—取决于插入时机和地点，和元素值无关。如果你以追加方式对一个群集插入六个元素，它们的排列次序将和插入次序一致。

主要包括 vector 向量容器、list 列表容器以及 deque 双端队列容器。之所以被称为序列容器，是因为元素在容器中的位置同元素的值无关，即容器不是排序的。将元素插入容器时，指定在什么位置，元素就会位于什么位置。

- array<T,N>（数组容器）：表示可以存储 N 个 T 类型的元素，是 [C++](http://c.biancheng.net/cplus/) 本身提供的一种容器。此类容器一旦建立，其长度就是固定不变的，这意味着不能增加或删除元素，只能改变某个元素的值；

- vector<T>（向量容器）：用来存放 T 类型的元素，是一个长度可变的序列容器，即在存储空间不足时，会自动申请更多的内存。使用此容器，在尾部增加或删除元素的效率最高（时间复杂度为 O(1) 常数阶），在其它位置插入或删除元素效率较差（时间复杂度为 O(n) 线性阶，其中 n 为容器中元素的个数）；

- deque<T>（双端队列容器）：和 vector 非常相似，区别在于使用该容器不仅尾部插入和删除元素高效，在头部插入或删除元素也同样高效，时间复杂度都是 O(1) 常数阶，但是在容器中某一位置处插入或删除元素，时间复杂度为 O(n) 线性阶；

- list<T>（链表容器）：是一个长度可变的、由 T 类型元素组成的序列，它以双向链表的形式组织元素，在这个序列的任何地方都可以高效地增加或删除元素（时间复杂度都为常数阶 O(1)），但访问容器中任意元素的速度要比前三种容器慢，这是因为 list<T> 必须从第一个元素或最后一个元素开始访问，需要沿着链表移动，直到到达想要的元素。

- forward_list<T>（正向链表容器）：和 list 容器非常类似，只不过它以单链表的形式组织元素，它内部的元素只能从第一个元素开始访问，是一类比链表容器快、更节省内存的容器。

  ![2-1P911110REB](C:\Users\杨志伟\OneDrive\桌面\2-1P911110REB.jpg)

  来源：[[C++序列式容器（STL序列式容器）是什么 (biancheng.net)](http://c.biancheng.net/view/409.html)]:

  | 函数成员         | 函数功能                                                     | array<T,N> | vector<T> | deque<T> |
  | ---------------- | ------------------------------------------------------------ | ---------- | --------- | -------- |
  | begin()          | 返回指向容器中第一个元素的迭代器。                           | 是         | 是        | 是       |
  | end()            | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 | 是         | 是        | 是       |
  | rbegin()         | 返回指向最后一个元素的迭代器。                               | 是         | 是        | 是       |
  | rend()           | 返回指向第一个元素所在位置前一个位置的迭代器。               | 是         | 是        | 是       |
  | cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
  | cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
  | crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
  | crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
  | assign()         | 用新元素替换原有内容。                                       | -          | 是        | 是       |
  | operator=()      | 复制同类型容器的元素，或者用初始化列表替换现有内容。         | 是         | 是        | 是       |
  | size()           | 返回实际元素个数。                                           | 是         | 是        | 是       |
  | max_size()       | 返回元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 | 是         | 是        | 是       |
  | capacity()       | 返回当前容量。                                               | -          | 是        | -        |
  | empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 | 是         | 是        | 是       |
  | resize()         | 改变实际元素的个数。                                         | -          | 是        | 是       |
  | shrink _to_fit() | 将内存减少到等于当前元素实际所使用的大小。                   | -          | 是        | 是       |
  | front()          | 返回第一个元素的引用。                                       | 是         | 是        | 是       |
  | back()           | 返回最后一个元素的引用。                                     | 是         | 是        | 是       |
  | operator[]()     | 使用索引访问元素。                                           | 是         | 是        | 是       |
  | at()             | 使用经过边界检査的索引访问元素。                             | 是         | 是        | 是       |
  | push_back()      | 在序列的尾部添加一个元素。                                   | -          | 是        | 是       |
  | insert()         | 在指定的位置插入一个或多个元素。                             | -          | 是        | 是       |
  | emplace()        | 在指定的位置直接生成一个元素。                               | -          | 是        | 是       |
  | emplace_back()   | 在序列尾部生成一个元素。                                     | -          | 是        | 是       |
  | pop_back()       | 移出序列尾部的元素。                                         | -          | 是        | 是       |
  | erase()          | 移出一个元素或一段元素。                                     | -          | 是        | 是       |
  | clear()          | 移出所有的元素，容器大小变为 0。                             | -          | 是        | 是       |
  | swap()           | 交换两个容器的所有元素。                                     | 是         | 是        | 是       |
  | data()           | 返回指向容器中第一个元素的[指针](http://c.biancheng.net/c/80/)。 | 是         | 是        | -        |

| 函数成员        | 函数功能                                                     | list<T> | forward_list<T> |
| --------------- | ------------------------------------------------------------ | ------- | --------------- |
| begin()         | 返回指向容器中第一个元素的迭代器。                           | 是      | 是              |
| end()           | 返回指向容器最后一个元素所在位置后一个位置的迭代器。         | 是      | 是              |
| rbegin()        | 返回指向最后一个元素的迭代器。                               | 是      | -               |
| rend()          | 返回指向第一个元素所在位置前一个位置的迭代器。               | 是      | -               |
| cbegin()        | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | 是              |
| before_begin()  | 返回指向第一个元素前一个位置的迭代器。                       | -       | 是              |
| cbefore_begin() | 和 before_begin() 功能相同，只不过在其基础上，增加了 const 属性，即不能用该指针修改元素的值。 | -       | 是              |
| cend()          | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | 是              |
| crbegin()       | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | -               |
| crend()         | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | -               |
| assign()        | 用新元素替换原有内容。                                       | 是      | 是              |
| operator=()     | 复制同类型容器的元素，或者用初始化列表替换现有内容。         | 是      | 是              |
| size()          | 返回实际元素个数。                                           | 是      | -               |
| max_size()      | 返回元素个数的最大值，这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 | 是      | 是              |
| resize()        | 改变实际元素的个数。                                         | 是      | 是              |
| empty()         | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 | 是      | 是              |
| front()         | 返回容器中第一个元素的引用。                                 | 是      | 是              |
| back()          | 返回容器中最后一个元素的引用。                               | 是      | -               |
| push_back()     | 在序列的尾部添加一个元素。                                   | 是      | -               |
| push_front()    | 在序列的起始位置添加一个元素。                               | 是      | 是              |
| emplace()       | 在指定位置直接生成一个元素。                                 | 是      | -               |
| emplace_after() | 在指定位置的后面直接生成一个元素。                           | -       | 是              |
| emplace_back()  | 在序列尾部生成一个元素。                                     | 是      | -               |
| cmplacc_front() | 在序列的起始位生成一个元索。                                 | 是      | 是              |
| insert()        | 在指定的位置插入一个或多个元素。                             | 是      | -               |
| insert_after()  | 在指定位置的后面插入一个或多个元素。                         | -       | 是              |
| pop_back()      | 移除序列尾部的元素。                                         | 是      | -               |
| pop_front()     | 移除序列头部的元素。                                         | 是      | 是              |
| reverse()       | 反转容器中某一段的元素。                                     | 是      | 是              |
| erase()         | 移除指定位置的一个元素或一段元素。                           | 是      | -               |
| erase_after()   | 移除指定位置后面的一个元素或一段元素。                       | -       | 是              |
| remove()        | 移除所有和参数匹配的元素。                                   | 是      | 是              |
| remove_if()     | 移除满足一元函数条件的所有元素。                             | 是      | 是              |
| unique()        | 移除所有连续重复的元素。                                     | 是      | 是              |
| clear()         | 移除所有的元素，容器大小变为 0。                             | 是      | 是              |
| swap()          | 交换两个容器的所有元素。                                     | 是      | 是              |
| sort()          | 对元素进行排序。                                             | 是      | 是              |
| merge()         | 合并两个有序容器。                                           | 是      | 是              |
| splice()        | 移动指定位置前面的所有元素到另一个同类型的 list 中。         | 是      | -               |
| splice_after()  | 移动指定位置后面的所有元素到另一个同类型的 list 中。         | -       | 是              |

#### 关联式容器

> 元素位置取决于特定的排序准则以及元素值，和插入次序无关。如果你将六个元素置入这样的群集中，它们的位置取决于元素值，和插入次序无关。

##### 排序容器

包括 set 集合容器、multiset多重集合容器、map映射容器以及 multimap 多重映射容器。排序容器中的元素默认是由小到大排序好的，即便是插入元素，元素也会插入到适当位置。所以关联容器在查找时具有非常好的性能。

##### 哈希容器

[C++](http://c.biancheng.net/cplus/) 11 新加入 4 种关联式容器，分别是 unordered_set 哈希集合、unordered_multiset 哈希多重集合、unordered_map 哈希映射以及 unordered_multimap 哈希多重映射。和排序容器不同，哈希容器中的元素是未排序的，元素的位置由哈希函数确定。

### 迭代器

#### 迭代器类型

输入迭代器、输出迭代器、前向迭代器、双向迭代器、随机访问迭代器

> 容器的迭代器的功能强弱，决定了该容器是否支持 STL 中的某种算法。

\1) 前向迭代器（forward iterator）
假设 p 是一个前向迭代器，则 p 支持 ++p，p++，*p 操作，还可以被复制或赋值，可以用 == 和 != 运算符进行比较。此外，两个正向迭代器可以互相赋值。

\2) 双向迭代器（bidirectional iterator）
双向迭代器具有正向迭代器的全部功能，除此之外，假设 p 是一个双向迭代器，则还可以进行 --p 或者 p-- 操作（即一次向后移动一个位置）。

\3) 随机访问迭代器（random access iterator）
随机访问迭代器具有双向迭代器的全部功能。除此之外，假设 p 是一个随机访问迭代器，i 是一个整型变量或常量，则 p 还支持以下操作：

- p+=i：使得 p 往后移动 i 个元素。
- p-=i：使得 p 往前移动 i 个元素。
- p+i：返回 p 后面第 i 个元素的迭代器。
- p-i：返回 p 前面第 i 个元素的迭代器。
- p[i]：返回 p 后面第 i 个元素的引用。


此外，两个随机访问迭代器 p1、p2 还可以用 <、>、<=、>= 运算符进行比较。另外，表达式 p2-p1 也是有定义的，其返回值表示 p2 所指向元素和 p1 所指向元素的序号之差（也可以说是 p2 和 p1 之间的元素个数减一）

| 容器                               | 对应的迭代器类型 |
| ---------------------------------- | ---------------- |
| array                              | 随机访问迭代器   |
| vector                             | 随机访问迭代器   |
| deque                              | 随机访问迭代器   |
| list                               | 双向迭代器       |
| set / multiset                     | 双向迭代器       |
| map / multimap                     | 双向迭代器       |
| forward_list                       | 前向迭代器       |
| unordered_map / unordered_multimap | 前向迭代器       |
| unordered_set / unordered_multiset | 前向迭代器       |
| stack                              | 不支持迭代器     |
| queue                              | 不支持迭代器     |

#### 迭代器定义

| 迭代器定义方式 | 具体格式                                   |
| -------------- | ------------------------------------------ |
| 正向迭代器     | 容器类名::iterator 迭代器名;               |
| 常量正向迭代器 | 容器类名::const_iterator 迭代器名;         |
| 反向迭代器     | 容器类名::reverse_iterator 迭代器名;       |
| 常量反向迭代器 | 容器类名::const_reverse_iterator 迭代器名; |

注意，以上 4 种定义迭代器的方式，并不是每个容器都适用。有一部分容器同时支持以上 4 种方式，比如 array、deque、vector；而有些容器只支持其中部分的定义方式，例如 forward_list 容器只支持定义正向迭代器，不支持定义反向迭代器。

## STL容器用法

### vector容器

单端数组

emplace_back()是 [C++](http://c.biancheng.net/cplus/) 11 新增加的，其功能和 push_back() 相同，都是在 vector 容器的尾部添加一个元素。

emplace_back() 和 push_back() 的区别，就在于底层实现的机制不同。push_back() 向容器尾部添加元素时，首先会创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）；而 emplace_back() 在实现时，则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。

[emplace_back()和push_back区别](https://zhuanlan.zhihu.com/p/183861524)



| 函数成员         | 函数功能                                                     |
| ---------------- | ------------------------------------------------------------ |
| begin()          | 返回指向容器中第一个元素的迭代器。                           |
| end()            | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 |
| rbegin()         | 返回指向最后一个元素的迭代器。                               |
| rend()           | 返回指向第一个元素所在位置前一个位置的迭代器。               |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| size()           | 返回实际元素个数。                                           |
| max_size()       | 返回元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| resize()         | 改变实际元素的个数。                                         |
| capacity()       | 返回当前容量。                                               |
| empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| reserve()        | 增加容器的容量。                                             |
| shrink _to_fit() | 将内存减少到等于当前元素实际所使用的大小。                   |
| operator[ ]      | 重载了 [ ] 运算符，可以向访问数组中元素那样，通过下标即可访问甚至修改 vector 容器中的元素。 |
| at()             | 使用经过边界检查的索引访问元素。                             |
| front()          | 返回第一个元素的引用。                                       |
| back()           | 返回最后一个元素的引用。                                     |
| data()           | 返回指向容器中第一个元素的指针。                             |
| assign()         | 用新元素替换原有内容。                                       |
| push_back()      | 在序列的尾部添加一个元素。                                   |
| pop_back()       | 移出序列尾部的元素。                                         |
| insert()         | 在指定的位置插入一个或多个元素。                             |
| erase()          | 移出一个元素或一段元素。                                     |
| clear()          | 移出所有的元素，容器大小变为 0。                             |
| swap()           | 交换两个容器的所有元素。                                     |
| emplace()        | 在指定的位置直接生成一个元素。                               |
| emplace_back()   | 在序列尾部生成一个元素。                                     |

#### vector操作实例

```c++
#include<vector>
#include<iostream>
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
    //  insert(const_iterator pos,ele)  迭代器指向位置前插入元素ele
    //  insert(const_iterator pos,int count ,ele)   //迭代器指向位置前插入count个ele
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
    //  2:at()		at()会先检查是否越界,推荐使用
    //  3:front()
    //  4:back()

    //容器互换
    //  swap()          可以用来收缩内存大小
    //	remove()	删除容器中所有和指定元素值相等的元素，并返回指向最后一个元素下一个位置的迭代器。值得一提的是，调用该函数不会改变容器的大小和容量。
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
    cout<<"不预留时扩容次数num= "<<num<<endl;
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
```

输出结果:

```c++
默认构造v1:5 5 5 5 5 5 5 5 5 5 
拷贝构造v2:5 5 5 5 5 5 5 5 5 5
赋值构造v3:5 5 5 5 5 5 5 5 5 5
拷贝构造v4:5 5 5 5 5 5 5 5 5 5
 v1容器是否为空0
v1 的容量: 16
v1的大小: 10
将v1重新指定大小为15后:
5 5 5 5 5 5 5 5 5 5 0 0 0 0 0
将v1指定大小为20,且指定补充100
5 5 5 5 5 5 5 5 5 5 0 0 0 0 0 100 100 100 100 100    
此时v1的容量大小为: 30
插入后的v2:
1000 1000 100 5 5 5 5 5 5 5 5 5 5 100
删除后的v2

v2 容器大小为:20
互换前v1,v3容器:
v1
5 5 5 5 5 5 5 5 5 5 0 0 0 0 0 100 100 100 100 100    
5 5 5 5 5 5 5 5 5 5
交换后:
5 5 5 5 5 5 5 5 5 5
5 5 5 5 5 5 5 5 5 5 0 0 0 0 0 100 100 100 100 100 
重新定义大小前v3的容量:10
定义大小为3并收缩后v3的容量:3
不预留时扩容次数num= 14
预留空间后扩容次数num= 1
v1预留空间后容量大小:100010
```



### deque

双端队列类，实现为可以从两端增长的动态数组

**列表**是一种特殊类型的序列容器，称为双重链接列表，其中容器中的每个元素都包含指向列表中下一个和上一个元素的指针。列表仅提供对列表的开头和结尾的访问 - 不提供随机访问。如果你想在中间找到一个值，你必须从一端开始，"遍历列表"，直到你到达你想要找到的元素。列表的优点是，如果您已经知道要将元素插入到列表中的位置，则将元素插入到列表中的速度非常快。通常，迭代器用于遍历列表。

表 1 中罗列了 deque 容器提供的所有成员函数。



| 函数成员         | 函数功能                                                     |
| ---------------- | ------------------------------------------------------------ |
| begin()          | 返回指向容器中第一个元素的迭代器。                           |
| end()            | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 |
| rbegin()         | 返回指向最后一个元素的迭代器。                               |
| rend()           | 返回指向第一个元素所在位置前一个位置的迭代器。               |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| size()           | 返回实际元素个数。                                           |
| max_size()       | 返回容器所能容纳元素个数的最大值。这通常是一个很大的值，一般是 232-1，我们很少会用到这个函数。 |
| resize()         | 改变实际元素的个数。                                         |
| empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| shrink _to_fit() | 将内存减少到等于当前元素实际所使用的大小。                   |
| at()             | 使用经过边界检查的索引访问元素。                             |
| front()          | 返回第一个元素的引用。                                       |
| back()           | 返回最后一个元素的引用。                                     |
| assign()         | 用新元素替换原有内容。                                       |
| push_back()      | 在序列的尾部添加一个元素。                                   |
| push_front()     | 在序列的头部添加一个元素。                                   |
| pop_back()       | 移除容器尾部的元素。                                         |
| pop_front()      | 移除容器头部的元素。                                         |
| insert()         | 在指定的位置插入一个或多个元素。                             |
| erase()          | 移除一个元素或一段元素。                                     |
| clear()          | 移出所有的元素，容器大小变为 0。                             |
| swap()           | 交换两个容器的所有元素。                                     |
| emplace()        | 在指定的位置直接生成一个元素。                               |
| emplace_front()  | 在容器头部生成一个元素。和 push_front() 的区别是，该函数直接在容器头部构造元素，省去了复制移动元素的过程。 |
| emplace_back()   | 在容器尾部生成一个元素。和 push_back() 的区别是，该函数直接在容器尾部构造元素，省去了复制移动元素的过程。 |

> 和 vector 相比，额外增加了实现在容器头部添加和删除元素的成员函数，同时删除了 capacity()、reserve() 和 data() 成员函数。

除此之外，当向 deque 容器添加元素时，deque 容器会申请更多的内存空间，同时其包含的所有元素可能会被复制或移动到新的内存地址（原来占用的内存会释放），这会导致之前创建的迭代器失效。

```c++
#include <iostream>
#include <deque>
using namespace std;
int main()
{
    deque<int>d;
    d.push_back(1);
    auto first = d.begin();
    cout << *first << endl;
    //添加元素，会导致 first 失效
    d.push_back(1);
    cout << *first << endl;
    return 0;
}
```

程序中第 12 行代码，会导致程序运行崩溃，其原因就在于在创建 first 迭代器之后，deque 容器做了添加元素的操作，导致 first 失效。

> 在对容器做添加元素的操作之后，如果仍需要使用之前以创建好的迭代器，为了保险起见，一定要重新生成。

样例:

评委评分:去除最大最小求平均值

```c++
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
```



### stack容器

```c++
![2-1P912134314345](C:\Users\杨志伟\OneDrive\桌面\2-1P912134314345.jpg)#include<iostream>
#include<stack>
using namespace std;
int main(int argc,char argv[]){
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
    return 0;
}
```



queue容器

### list容器

list 容器，又称双向链表容器，即该容器的底层是以双向链表的形式实现的。这意味着，list 容器中的元素可以分散存储在内存空间里，而不是必须存储在一整块连续的内存空间中。

![](C:\Users\杨志伟\OneDrive\桌面\学习\images\2-1P912134314345.jpg)

基于这样的存储结构，list 容器具有一些其它容器（array、vector 和 deque）所不具备的优势，即它可以在序列已知的任何位置快速插入或删除元素（时间复杂度为`O(1)`）。并且在 list 容器中移动元素，也比其它容器的效率高。

使用 list 容器的缺点是，它不能像 array 和 vector 那样，通过位置直接访问元素。举个例子，如果要访问 list 容器中的第 6 个元素，它不支持`容器对象名[6]`这种语法格式，正确的做法是从容器中第一个元素或最后一个元素开始遍历容器，直到找到该位置。



> 实际场景中，如何需要对序列进行大量添加或删除元素的操作，而直接访问元素的需求却很少，这种情况建议使用 list 容器存储序列。

#### list成员函数

| 成员函数        | 功能                                                         |
| --------------- | ------------------------------------------------------------ |
| begin()         | 返回指向容器中第一个元素的双向迭代器。                       |
| end()           | 返回指向容器中最后一个元素所在位置的下一个位置的双向迭代器。 |
| rbegin()        | 返回指向最后一个元素的反向双向迭代器。                       |
| rend()          | 返回指向第一个元素所在位置前一个位置的反向双向迭代器。       |
| cbegin()        | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()          | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crbegin()       | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| crend()         | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| empty()         | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| size()          | 返回当前容器实际包含的元素个数。                             |
| max_size()      | 返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| front()         | 返回第一个元素的引用。                                       |
| back()          | 返回最后一个元素的引用。                                     |
| assign()        | 用新元素替换容器中原有内容。                                 |
| emplace_front() | 在容器头部生成一个元素。该函数和 push_front() 的功能相同，但效率更高。 |
| push_front()    | 在容器头部插入一个元素。                                     |
| pop_front()     | 删除容器头部的一个元素。                                     |
| emplace_back()  | 在容器尾部直接生成一个元素。该函数和 push_back() 的功能相同，但效率更高。 |
| push_back()     | 在容器尾部插入一个元素。                                     |
| pop_back()      | 删除容器尾部的一个元素。                                     |
| emplace()       | 在容器中的指定位置插入元素。该函数和 insert() 功能相同，但效率更高。 |
| insert()        | 在容器中的指定位置插入元素。                                 |
| erase()         | 删除容器中一个或某区域内的元素。                             |
| swap()          | 交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。 |
| resize()        | 调整容器的大小。                                             |
| clear()         | 删除容器存储的所有元素。                                     |
| splice()        | 将一个 list 容器中的元素插入到另一个容器的指定位置。         |
| remove(val)     | 删除容器中所有等于 val 的元素。                              |
| remove_if()     | 删除容器中满足条件的元素。                                   |
| unique()        | 删除容器中相邻的重复元素，只保留一个。                       |
| merge()         | 合并两个事先已排好序的 list 容器，并且合并之后的 list 容器依然是有序的。 |
| sort()          | 通过更改容器中元素的位置，将它们进行排序。                   |
| reverse()       | 反转容器中元素的顺序。                                       |

![](C:\Users\杨志伟\OneDrive\桌面\学习\images\2-191219135239561.gif)

forward_list 是 [C++](http://c.biancheng.net/cplus/) 11 新添加的一类容器，其底层实现和 list 容器一样，采用的也是链表结构，只不过 forward_list 使用的是单链表，而 list 使用的是双向链表（如图 1 所示)。

通过图 1 不难看出，使用链表存储数据最大的特点在于，其并不会将数据进行集中存储（向数组那样），换句话说，链表中数据的存储位置是分散的、随机的，整个链表中数据的线性关系通过[指针](http://c.biancheng.net/c/80/)来维持。

因此，forward_list 容器具有和 list 容器相同的特性，即擅长在序列的任何位置进行插入元素或删除元素的操作，但对于访问存储的元素，没有其它容器（如 array、vector）的效率高。

另外，由于单链表没有双向链表那样灵活，因此相比 list 容器，forward_list 容器的功能受到了很多限制。比如，由于单链表只能从前向后遍历，而不支持反向遍历，因此 forward_list 容器只提供前向迭代器，而不是双向迭代器。这意味着，forward_list 容器不具有 rbegin()、rend() 之类的成员函数。

#### forward_list容器

表 2 中罗列出了 forward_list 模板类提供的所有成员函数以及各自的功能。



| 成员函数        | 功能                                                         |
| --------------- | ------------------------------------------------------------ |
| before_begin()  | 返回一个前向迭代器，其指向容器中第一个元素之前的位置。       |
| begin()         | 返回一个前向迭代器，其指向容器中第一个元素的位置。           |
| end()           | 返回一个前向迭代器，其指向容器中最后一个元素之后的位置。     |
| cbefore_begin() | 和 before_begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cbegin()        | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| cend()          | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 |
| empty()         | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 |
| max_size()      | 返回容器所能包含元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 |
| front()         | 返回第一个元素的引用。                                       |
| assign()        | 用新元素替换容器中原有内容。                                 |
| push_front()    | 在容器头部插入一个元素。                                     |
| emplace_front() | 在容器头部生成一个元素。该函数和 push_front() 的功能相同，但效率更高。 |
| pop_front()     | 删除容器头部的一个元素。                                     |
| emplace_after() | 在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。和 insert_after() 的功能相同，但效率更高。 |
| insert_after()  | 在指定位置之后插入一个新元素，并返回一个指向新元素的迭代器。 |
| erase_after()   | 删除容器中某个指定位置或区域内的所有元素。                   |
| swap()          | 交换两个容器中的元素，必须保证这两个容器中存储的元素类型是相同的。 |
| resize()        | 调整容器的大小。                                             |
| clear()         | 删除容器存储的所有元素。                                     |
| splice_after()  | 将某个 forward_list 容器中指定位置或区域内的元素插入到另一个容器的指定位置之后。 |
| remove(val)     | 删除容器中所有等于 val 的元素。                              |
| remove_if()     | 删除容器中满足条件的元素。                                   |
| unique()        | 删除容器中相邻的重复元素，只保留一个。                       |
| merge()         | 合并两个事先已排好序的 forward_list 容器，并且合并之后的 forward_list 容器依然是有序的。 |
| sort()          | 通过更改容器中元素的位置，将它们进行排序。                   |
| reverse()       | 反转容器中元素的顺序。                                       |


除此之外，C++ 11 标准库还新增加了 begin() 和 end() 这 2 个函数，和 forward_list 容器包含的 begin() 和 end() 成员函数不同，标准库提供的这 2 个函数的操作对象，既可以是容器，还可以是普通数组。当操作对象是容器时，它和容器包含的 begin() 和 end() 成员函数的功能完全相同；如果操作对象是普通数组，则 begin() 函数返回的是指向数组第一个元素的指针，同样 end() 返回指向数组中最后一个元素之后一个位置的指针（注意不是最后一个元素）。

forward_list 容器还有一个`std::swap(x , y)`非成员函数（其中 x 和 y 是存储相同类型元素的 forward_list 容器），它和 swap() 成员函数的功能完全相同，仅使用语法上有差异。

## 关联式容器

通过学习所有的序列式容器不难发现，无论是哪种序列式容器，其存储的都是 C++ 基本数据类型（诸如 int、double、float、string 等）或使用结构体自定义类型的元素。例如，如下是一个存储 int 类型元素的 vector 容器：

std::vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19};


关联式容器则大不一样，此类容器在存储元素值的同时，还会为各元素额外再配备一个值（又称为“键”，其本质也是一个 C++ 基础数据类型或自定义类型的元素），它的功能是在使用关联式容器的过程中，如果已知目标元素的键的值，则直接通过该键就可以找到目标元素，而无需再通过遍历整个容器的方式。

> 弃用序列式容器，转而选用关联式容器存储元素，往往就是看中了关联式容器可以快速查找、读取或者删除所存储的元素，同时该类型容器插入元素的效率也比序列式容器高。

也就是说，使用关联式容器存储的元素，都是一个一个的“键值对”（ <key,value> ），这是和序列式容器最大的不同。除此之外，序列式容器中存储的元素默认都是未经过排序的，而使用关联式容器存储的元素，默认会根据各元素的键值的大小做升序排序。

C++ STL 标准库提供了 4 种关联式容器，分别为 map、set、multimap、multiset，其各自的特点如表 1 所示。



| 关联式容器名称 | 特点                                                         |
| -------------- | ------------------------------------------------------------ |
| map            | 定义在 <map> 头文件中，使用该容器存储的数据，其各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序（调用 std::less<T>）。 |
| set            | 定义在 <set> 头文件中，使用该容器存储的数据，各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）。该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序（调用 std::less<T>）。 |
| multimap       | 定义在 <map> 头文件中，和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复。 |
| multiset       | 定义在 <set> 头文件中，和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的）。 |

> 除此之外，C++ 11 还新增了 4 种哈希容器，即 unordered_map、unordered_multimap 以及 unordered_set、unordered_multiset。严格来说，它们也属于关联式容器，但由于哈希容器底层采用的是哈希表，而不是红黑树，因此本教程将它们分开进行讲解（有关哈希容器，将放在后续章节做详细讲解）。

### pair模板

我们知道，关联式容器存储的是“键值对”形式的数据，比如：

 <"C语言教程", "http://c.biancheng.net/c/">
		<"[Python](http://c.biancheng.net/python/)教程", "http://c.biancheng.net/python/">
		<"[Java](http://c.biancheng.net/java/)教程", "http://c.biancheng.net/java/">

如上所示，每行都表示一个键值对，其中第一个元素作为键（key），第二个元素作为值（value）。

> 注意，基于各个关联式容器存储数据的特点，只有各个键值对中的键和值全部对应相等时，才能使用 set 和 multiset 关联式容器存储，否则就要选用 map 或者 multimap 关联式容器。

考虑到“键值对”并不是普通类型数据，[C++](http://c.biancheng.net/cplus/) [STL](http://c.biancheng.net/stl/) 标准库提供了 pair 类模板，其专门用来将 2 个普通元素 first 和 second（可以是 C++ 基本数据类型、结构体、类自定的类型）创建成一个新元素`<first, second>`。通过其构成的元素格式不难看出，使用 pair 类模板来创建“键值对”形式的元素，再合适不过。

注意，pair 类模板定义在`<utility>`头文件中，所以在使用该类模板之前，需引入此头文件。另外值得一提的是，在 C++ 11 标准之前，pair 类模板中提供了以下 3 种构造函数：

```c++
#1) 默认构造函数，即创建空的 pair 对象
pair();
#2) 直接使用 2 个元素初始化成 pair 对象
pair (const first_type& a, const second_type& b);
#3) 拷贝（复制）构造函数，即借助另一个 pair 对象，创建新的 pair 对象
template<class U, class V> pair (const pair<U,V>& pr);
```

在 C++ 11 标准中，在引入[右值引用](http://c.biancheng.net/view/439.html)的基础上，pair 类模板中又增添了如下 2 个构造函数：

```c++
#4) 移动构造函数
template<class U, class V> pair (pair<U,V>&& pr);
#5) 使用右值引用参数，创建 pair 对象
template<class U, class V> pair (U&& a, V&& b);
```

> 除此之外，C++ 11 标准中 pair 类模板还新增加了如下一种构造函数：`pair (piecewise_construct_t pwc, tuple<Args1...> first_args, tuple<Args2...> second_args);`
>
> ，该构造 pair 类模板的方式很少用到，因此本节不再对其进行详细介绍，感兴趣的读者可自行查阅资料。

下面程序演示了以上几种创建 pair 对象的方法：

```c++
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    // 调用构造函数 1，也就是默认构造函数
    pair <string, double> pair1;
    // 调用第 2 种构造函数
    pair <string, string> pair2("STL教程","http://c.biancheng.net/stl/");  
    // 调用拷贝构造函数
    pair <string, string> pair3(pair2);
    //调用移动构造函数
    pair <string, string> pair4(make_pair("C++教程", "http://c.biancheng.net/cplus/"));
    // 调用第 5 种构造函数
    pair <string, string> pair5(string("Python教程"), string("http://c.biancheng.net/python/"));  
   
    cout << "pair1: " << pair1.first << " " << pair1.second << endl;
    cout << "pair2: "<< pair2.first << " " << pair2.second << endl;
    cout << "pair3: " << pair3.first << " " << pair3.second << endl;
    cout << "pair4: " << pair4.first << " " << pair4.second << endl;
    cout << "pair5: " << pair5.first << " " << pair5.second << endl;
    return 0;
}
```

上面程序在创建 pair4 对象时，调用了 make_pair() 函数，它也是 <utility> 头文件提供的，其功能是生成一个 pair 对象。因此，当我们将 make_pair() 函数的返回值（是一个临时对象）作为参数传递给 pair() 构造函数时，其调用的是移动构造函数，而不是拷贝构造函数。

在上面程序的基础上，C++ 11 还允许我们手动为 pair1 对象赋值，比如：

```
pair1.first = "Java教程";
pair1.second = "http://c.biancheng.net/java/";
cout << "new pair1: " << pair1.first << " " << pair1.second << endl;
```

执行结果为：

new pair1: Java教程 http://c.biancheng.net/java/

同时，上面程序中 pair4 对象的创建过程，还可以写入如下形式，它们是完全等价的：

```c++
pair <string, string> pair4 = make_pair("C++教程", "http://c.biancheng.net/cplus/");
cout << "pair4: " << pair4.first << " " << pair4.second << endl;
```

`<utility>`头文件中除了提供创建 pair 对象的方法之外，还为 pair 对象重载了 <、<=、>、>=、==、!= 这 6 的运算符，其运算规则是：对于进行比较的 2 个 pair 对象，先比较 pair.first 元素的大小，如果相等则继续比较 pair.second 元素的大小。

> 注意，对于进行比较的 2 个 pair 对象，其对应的键和值的类型比较相同，否则将没有可比性，同时编译器提示没有相匹配的运算符，即找不到合适的重载运算符。

```c++
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("STL教程", 20);
    pair <string, int> pair2("C++教程", 20);
    pair <string, int> pair3("C++教程", 30);
    //pair1和pair2的key不同，value相同
    if (pair1 != pair2) {
        cout << "pair != pair2" << endl;
    }
    //pair2和pair3的key相同，value不同
    if (pair2 != pair3) {
        cout << "pair2 != pair3" << endl;
    }
    return 0;
}
```

结果：

>  pair != pair2
> 		pair2 != pair3

最后需要指出的是，pair类模板还提供有一个 swap() 成员函数，能够互换 2 个 pair 对象的键值对，其操作成功的前提是这 2 个 pair 对象的键和值的类型要相同。例如：

```c++
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("pair", 10);                   
    pair <string, int> pair2("pair2", 20);
    //交换 pair1 和 pair2 的键值对
    pair1.swap(pair2);
    cout << "pair1: " << pair1.first << " " << pair1.second << endl;
    cout << "pair2: " << pair2.first << " " << pair2.second << endl;
    return 0;
}

```

### map容器

作为关联式容器的一种，**map 容器存储的都是 pair 对象，也就是用 pair 类模板创建的键值对**。其中，**各个键值对的键和值可以是任意数据类型**，包括 [C++](http://c.biancheng.net/cplus/) 基本数据类型（int、double 等）、使用结构体或类自定义的类型。

> 通常情况下，map 容器中存储的各个键值对都选用 string 字符串作为键的类型。

与此同时，在使用 map 容器存储多个键值对时，该容器会自动根据各键值对的键的大小，按照既定的规则进行排序。默认情况下，map 容器选用`std::less<T>`排序规则（其中 T 表示键的数据类型），其会根据键的大小对所有键值对做**升序排序**。当然，根据实际情况的需要，我们可以手动指定 map 容器的排序规则，既可以选用 [STL](http://c.biancheng.net/stl/) 标准库中提供的其它排序规则（比如`std::greater<T>`），也可以自定义排序规则。

另外需要注意的是，使用 map 容器存储的各个键值对，**键的值既不能重复也不能被修改**。换句话说，map 容器中存储的各个键值对不仅键的值独一无二，键的类型也会用 const 修饰，这意味着只要键值对被存储到 map 容器中，其键的值将不能再做任何修改。

> 前面提到，map 容器存储的都是 pair 类型的键值对元素，更确切的说，该容器存储的都是 pair<const K, T> 类型（其中 K 和 T 分别表示键和值的数据类型）的键值对元素。

map容器模板定义:

```c++
template < class Key,                                     // 指定键（key）的类型
           class T,                                       // 指定值（value）的类型
           class Compare = less<Key>,                     // 指定排序规则
           class Alloc = allocator<pair<const Key,T> >    // 指定分配器对象的类型
           > class map;
```

#### 创建C++ map容器的几种方法

map 容器的模板类中包含多种构造函数，因此创建 map 容器的方式也有多种，下面就几种常用的创建 map 容器的方法，做一一讲解。

\1) 通过调用 map 容器类的默认构造函数，可以创建出一个空的 map 容器，比如：

```
std::map<std::string, int>myMap;
```

> 如果程序中已经默认指定了 std 命令空间，这里可以省略 `std::`。

通过此方式创建出的 myMap 容器，初始状态下是空的，即没有存储任何键值对。鉴于空 map 容器可以根据需要随时添加新的键值对，因此创建空 map 容器是比较常用的。

\2) 当然在创建 map 容器的同时，也可以进行初始化，比如：

```
std::map<std::string, int>myMap{ {"C语言教程",10},{"STL教程",20} };
```

由此，myMap 容器在初始状态下，就包含有 2 个键值对。

再次强调，map 容器中存储的键值对，其本质都是 pair 类模板创建的 pair 对象。因此，下面程序也可以创建出一模一样的 myMap 容器：

```
std::map<std::string, int>myMap{std::make_pair("C语言教程",10),std::make_pair("STL教程",20)};
```


\3) 除此之外，在某些场景中，可以利用先前已创建好的 map 容器，再创建一个新的 map 容器。例如：

```
std::map<std::string, int>newMap(myMap);
```

由此，通过调用 map 容器的拷贝（复制）构造函数，即可成功创建一个和 myMap 完全一样的 newMap 容器。

C++ 11 标准中，还为 map 容器增添了移动构造函数。当有临时的 map 对象作为参数，传递给要初始化的 map 容器时，此时就会调用移动构造函数。举个例子：

```
#创建一个会返回临时 map 对象的函数std::map<std::string,int> disMap() {    std::map<std::string, int>tempMap{ {"C语言教程",10},{"STL教程",20} };    return tempMap;}//调用 map 类模板的移动构造函数创建 newMap 容器std::map<std::string, int>newMap(disMap());
```

> 注意，无论是调用复制构造函数还是调用拷贝构造函数，都必须保证这 2 个容器的类型完全一致。


\4) map 类模板还支持取已建 map 容器中指定区域内的键值对，创建并初始化新的 map 容器。例如：

```
std::map<std::string, int>myMap{ {"C语言教程",10},{"STL教程",20} };std::map<std::string, int>newMap(++myMap.begin(), myMap.end());
```

这里，通过调用 map 容器的双向迭代器，实现了在创建 newMap 容器的同时，将其初始化为包含一个 {"STL教程",20} 键值对的容器。


\5) 当然，在以上几种创建 map 容器的基础上，我们都可以手动修改 map 容器的排序规则。默认情况下，map 容器调用 std::less<T> 规则，根据容器内各键值对的键的大小，对所有键值对做升序排序。

因此，如下 2 行创建 map 容器的方式，其实是等价的：

```
std::map<std::string, int>myMap{ {"C语言教程",10},{"STL教程",20} };std::map<std::string, int, std::less<std::string> >myMap{ {"C语言教程",10},{"STL教程",20} };
```

以上 2 中创建方式生成的 myMap 容器，其内部键值对排列的顺序为：

<"C语言教程", 10>
<"STL教程", 20>


下面程序手动修改了 myMap 容器的排序规则，令其作降序排序：

```
std::map<std::string, int, std::greater<std::string> >myMap{ {"C语言教程",10},{"STL教程",20} };
```

此时，myMap 容器内部键值对排列的顺序为：

 <"STL教程", 20>
		<"C语言教程", 10>

#### map成员函数

表 1 列出了 map 容器提供的常用成员方法以及各自的功能。



| 成员方法         | 功能                                                         |
| ---------------- | ------------------------------------------------------------ |
| begin()          | 返回指向容器中第一个（注意，是已排好序的第一个）键值对的双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| end()            | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| rbegin()         | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| rend()           | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的键值对。 |
| find(key)        | 在 map 容器中查找键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| lower_bound(key) | 返回一个指向当前 map 容器中第一个大于或等于 key 的键值对的双向迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| upper_bound(key) | 返回一个指向当前 map 容器中第一个大于 key 的键值对的迭代器。如果 map 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| equal_range(key) | 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的键为 key 的键值对（map 容器键值对唯一，因此该范围最多包含一个键值对）。 |
| empty()          | 若容器为空，则返回 true；否则 false。                        |
| size()           | 返回当前 map 容器中存有键值对的个数。                        |
| max_size()       | 返回 map 容器所能容纳键值对的最大个数，不同的操作系统，其返回值亦不相同。 |
| operator[]       | map容器重载了 [] 运算符，只要知道 map 容器中某个键值对的键的值，就可以向获取数组中元素那样，通过键直接获取对应的值。 |
| at(key)          | 找到 map 容器中 key 键对应的值，如果找不到，该函数会引发 out_of_range 异常。 |
| insert()         | 向 map 容器中插入键值对。                                    |
| erase()          | 删除 map 容器指定位置、指定键（key）值或者指定区域内的键值对。后续章节还会对该方法做重点讲解。 |
| swap()           | 交换 2 个 map 容器中存储的键值对，这意味着，操作的 2 个键值对的类型必须相同。 |
| clear()          | 清空 map 容器中所有的键值对，即使 map 容器的 size() 为 0。   |
| emplace()        | 在当前 map 容器中的指定位置处构造新键值对。其效果和插入键值对一样，但效率更高。 |
| emplace_hint()   | 在本质上和 emplace() 在 map 容器中构造新键值对的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示键值对生成位置的迭代器，并作为该方法的第一个参数。 |
| count(key)       | 在当前 map 容器中，查找键为 key 的键值对的个数并返回。注意，由于 map 容器中各键值对的键的值是唯一的，因此该函数的返回值最大为 1。 |

### Set

和 map、multimap 容器不同，使用 set 容器存储的各个键值对，要求键 key 和值 value 必须相等。

举个例子，如下有 2 组键值对数据：

{<'a', 1>, <'b', 2>, <'c', 3>}
{<'a', 'a'>, <'b', 'b'>, <'c', 'c'>}

显然，第一组数据中各键值对的键和值不相等，而第二组中各键值对的键和值对应相等。对于 set 容器来说，只能存储第 2 组键值对，而无法存储第一组键值对。

基于 set 容器的这种特性，当使用 set 容器存储键值对时，只需要为其提供各键值对中的 value 值（也就是 key 的值）即可。仍以存储上面第 2 组键值对为例，只需要为 set 容器提供 {'a','b','c'} ，该容器即可成功将它们存储起来。

通过前面的学习我们知道，map、multimap 容器都会自行根据键的大小对存储的键值对进行排序，set 容器也会如此，只不过 set 容器中各键值对的键 key 和值 value 是相等的，根据 key 排序，也就等价为根据 value 排序。

另外，使用 set 容器存储的各个元素的值必须各不相同。更重要的是，从语法上讲 set 容器并没有强制对存储元素的类型做 const 修饰，即 set 容器中存储的元素的值是可以修改的。但是，C++ 标准为了防止用户修改容器中元素的值，对所有可能会实现此操作的行为做了限制，使得在正常情况下，用户是无法做到修改 set 容器中元素的值的。

> 对于初学者来说，切勿尝试直接修改 set 容器中已存储元素的值，这很有可能破坏 set 容器中元素的有序性，最正确的修改 set 容器中元素值的做法是：先删除该元素，然后再添加一个修改后的元素。

值得一提的是，set 容器定义于`<set>`头文件，并位于 std 命名空间中。因此如果想在程序中使用 set 容器，该程序代码应先包含如下语句：

```
#include <set>using namespace std;
```

注意，第二行代码不是必需的，如果不用，则后续程序中在使用 set 容器时，需手动注明 std 命名空间（强烈建议初学者使用）。

#### set模板

set 容器的类模板定义如下：

```c++
template < class T,                        // 键 key 和值 value 的类型          
		  class Compare = less<T>,        // 指定 set 容器内部的排序规则      
	      class Alloc = allocator<T>      // 指定分配器对象的类型           
         > class set;
```

注意，由于 set 容器存储的各个键值对，其键和值完全相同，也就意味着它们的类型相同，因此 set 容器类模板的定义中，仅有第 1 个参数用于设定存储数据的类型。

> 对于 set 类模板中的 3 个参数，后 2 个参数自带默认值，且几乎所有场景中只需使用前 2 个参数，第 3 个参数不会用到。

#### set函数

| 成员方法         | 功能                                                         |
| ---------------- | ------------------------------------------------------------ |
| begin()          | 返回指向容器中第一个（注意，是已排好序的第一个）元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| end()            | 返回指向容器最后一个元素（注意，是已排好序的最后一个）所在位置后一个位置的双向迭代器，通常和 begin() 结合使用。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| rbegin()         | 返回指向最后一个（注意，是已排好序的最后一个）元素的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| rend()           | 返回指向第一个（注意，是已排好序的第一个）元素所在位置前一个位置的反向双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的反向双向迭代器。 |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改容器内存储的元素值。 |
| find(val)        | 在 set 容器中查找值为 val 的元素，如果成功找到，则返回指向该元素的双向迭代器；反之，则返回和 end() 方法一样的迭代器。另外，如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| lower_bound(val) | 返回一个指向当前 set 容器中第一个大于或等于 val 的元素的双向迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| upper_bound(val) | 返回一个指向当前 set 容器中第一个大于 val 的元素的迭代器。如果 set 容器用 const 限定，则该方法返回的是 const 类型的双向迭代器。 |
| equal_range(val) | 该方法返回一个 pair 对象（包含 2 个双向迭代器），其中 pair.first 和 lower_bound() 方法的返回值等价，pair.second 和 upper_bound() 方法的返回值等价。也就是说，该方法将返回一个范围，该范围中包含的值为 val 的元素（set 容器中各个元素是唯一的，因此该范围最多包含一个元素）。 |
| empty()          | 若容器为空，则返回 true；否则 false。                        |
| size()           | 返回当前 set 容器中存有元素的个数。                          |
| max_size()       | 返回 set 容器所能容纳元素的最大个数，不同的操作系统，其返回值亦不相同。 |
| insert()         | 向 set 容器中插入元素。                                      |
| erase()          | 删除 set 容器中存储的元素。                                  |
| swap()           | 交换 2 个 set 容器中存储的所有元素。这意味着，操作的 2 个 set 容器的类型必须相同。 |
| clear()          | 清空 set 容器中所有的元素，即令 set 容器的 size() 为 0。     |
| emplace()        | 在当前 set 容器中的指定位置直接构造新元素。其效果和 insert() 一样，但效率更高。 |
| emplace_hint()   | 在本质上和 emplace() 在 set 容器中构造新元素的方式是一样的，不同之处在于，使用者必须为该方法提供一个指示新元素生成位置的迭代器，并作为该方法的第一个参数。 |
| count(val)       | 在当前 set 容器中，查找值为 val 的元素的个数，并返回。注意，由于 set 容器中各元素的值是唯一的，因此该函数的返回值最大为 1。 |

### priority_queue容器

priority_queue 容器适配器模拟的也是队列这种存储结构，即使用此容器适配器存储元素只能“从一端进（称为队尾），从另一端出（称为队头）”，且每次只能访问 priority_queue 中位于队头的元素。

但是，priority_queue 容器适配器中元素的存和取，遵循的并不是 “First in,First out”（先入先出）原则，而是“First in，Largest out”原则。直白的翻译，指的就是先进队列的元素并不一定先出队列，而是优先级最大的元素最先出队列。

> 注意，“First in，Largest out”原则是笔者为了总结 priority_queue 存取元素的特性自创的一种称谓，仅为了方便读者理解。

那么，priority_queue 容器适配器中存储的元素，优先级是如何评定的呢？很简单，每个 priority_queue 容器适配器在创建时，都制定了一种排序规则。根据此规则，该容器适配器中存储的元素就有了优先级高低之分。

举个例子，假设当前有一个 priority_queue 容器适配器，其制定的排序规则是按照元素值从大到小进行排序。根据此规则，自然是 priority_queue 中值最大的元素的优先级最高。

priority_queue 容器适配器为了保证每次从队头移除的都是当前优先级最高的元素，每当有新元素进入，它都会根据既定的排序规则找到优先级最高的元素，并将其移动到队列的队头；同样，当 priority_queue 从队头移除出一个元素之后，它也会再找到当前优先级最高的元素，并将其移动到队头。

基于 priority_queue 的这种特性，因此该容器适配器有被称为优先级队列。

#### priority_queue模板

```c++
template <typename T,
        typename Container=std::vector<T>,
        typename Compare=std::less<T> >
class priority_queue{
    //......
}
```

可以看到，priority_queue 容器适配器模板类最多可以传入 3 个参数，它们各自的含义如下：

- typename T：指定存储元素的具体类型；

- typename Container：指定 priority_queue 底层使用的基础容器，默认使用 vector 容器。

  > 作为 priority_queue 容器适配器的底层容器，其必须包含 empty()、size()、front()、push_back()、pop_back() 这几个成员函数，[STL](http://c.biancheng.net/stl/) 序列式容器中只有 vector 和 deque 容器符合条件。

- typename Compare：指定容器中评定元素优先级所遵循的排序规则，默认使用

  ```
  std::less<T>
  ```

  按照元素值从大到小进行排序，还可以使用

  ```
  std::greater<T>
  ```

  按照元素值从小到大排序，但更多情况下是使用自定义的排序规则。

  > 其中，std::less<T> 和 std::greater<T> 都是以函数对象的方式定义在 <function> 头文件中。

priority_queue函数

| 成员函数                       | 功能                                                         |
| ------------------------------ | ------------------------------------------------------------ |
| empty()                        | 如果 priority_queue 为空的话，返回 true；反之，返回 false。  |
| size()                         | 返回 priority_queue 中存储元素的个数。                       |
| top()                          | 返回 priority_queue 中第一个元素的引用形式。                 |
| push(const T& obj)             | 根据既定的排序规则，将元素 obj 的副本存储到 priority_queue 中适当的位置。 |
| push(T&& obj)                  | 根据既定的排序规则，将元素 obj 移动存储到 priority_queue 中适当的位置。 |
| emplace(Args&&... args)        | Args&&... args 表示构造一个存储类型的元素所需要的数据（对于类对象来说，可能需要多个数据构造出一个对象）。此函数的功能是根据既定的排序规则，在容器适配器适当的位置直接生成该新元素。 |
| pop()                          | 移除 priority_queue 容器适配器中第一个元素。                 |
| swap(priority_queue<T>& other) | 将两个 priority_queue 容器适配器中的元素进行互换，需要注意的是，进行互换的 2 个 priority_queue 容器适配器中存储的元素类型以及底层采用的基础容器类型，都必须相同。 |
