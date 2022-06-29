# 动态链表ADT

### 要求

**1.**   **复杂数据结构-动态链表**

a)    涉及知识点：内存管理、结构体定义、指针运用、函数

b)   要求：

链表是一种重要的数据结构，需要动态的进行存储分配，要求通过函数分别实现动态链表的建立、结点的插入、结点的删除以及链表的输出。

### 实现过程(带头结点的单向链表为例)

单向链表数据结构实现:类型    函数

```c
typedef struct Node
{
    int data;
    struct Node *next;
}Node;
```

单向链表中包含数据域和指针域，其中数据域用于存放数据，指针域用来连接当前结点和下一节点。

### 函数实现

通常创建方法有头插法和尾插法

![image-20220512203557846](C:\Users\杨志伟\AppData\Roaming\Typora\typora-user-images\image-20220512203557846.png)

头插法和尾插法的区别是:

头插法 插入在头结点后面,尾插法 插入在链表的尾部

对于修改内容,我们需要传递地址,参见 值传递和地址传递的区别,所以本题中修改链表的都采用了地址传递,而不修改内容的都采用了值传递.

```c
void CreatListHead(LinkList *L,int n){    //头插法创建
    LinkList p;
    int j;
    (*L)=(LinkList)malloc(sizeof(Node));          //可以加上返回值判断,如果内存不够,动态分配不了空间,则会无法创建
    (*L)->next=NULL;
    for(int i=0;i<n;i++){
        p=(LinkList)malloc(sizeof(Node));
        scanf("%d",&j);
        p->data=j;
        p->next=(*L)->next;
        (*L)->next=p;
    }
}
```

```c
void CreatListTail(LinkList *L,int n,int a){    //尾插法创建
    LinkList p,r;
    *L=(LinkList)malloc(sizeof(Node));		//同理
    (*L)->next=NULL;
    r=*L;
    for(int i=0;i<n;i++){
        p=(LinkList)malloc(sizeof(Node));
        p->data=a;
        r->next=p;
        r=p;
    }
    r->next=NULL;
}
```

也可以在后面加上判断链表结点数量来判断初始化是否成功。

我们也可以采用链表反转来消除这个影响

```c
LinkList ReverseWH(LinkList L){     //倒序法,n来保存往后的一个节点,让p,s倒指,用n来查询后面的数,一直保持,最后赋值   带头结点的反转
    LinkList p=L->next,p0=L;
    LinkList s=p->next;
    p->next=NULL;
    LinkList n=NULL;
    while(s->next!=NULL){
        n=s->next;
        s->next=p;
        p=s;
        s=n;
    }
    L->next=s;
    s->next=p;
    return L;
}
```

![image-20220512220055813](C:\Users\杨志伟\AppData\Roaming\Typora\typora-user-images\image-20220512220055813.png)

例 判断链表是否为空 等等函数

```c
//只需要判断头结点后面结点是否为NULL就可以了
bool isEmpty(LinkList L){
    if(L->next==NULL){
        return 1;
    }
    return 0;
}
//查找n是否在链表内,往后找,类迭代器的写法
int EnsureElem(LinkList L,int n){     
    for(LinkList p=L;p!=NULL;p=p->next){
        if(p->data==n{
            return 1;
        }
    }
    return 0;
}
//找就可以了
int Length(LinkList L){
    if(isEmpty(L)){
        return 0;
    }
    int cnt=0;
    while (L)
    {
        L=L->next;
        cnt++;
    }
    return cnt;
}
//       返回在i位置的元素;
int GetElem(LinkList L,int i){
    int j=1;
    L=L->next;			//删除头节点的影响
    while (L && j<i)
    {
        L=L->next;
        j++;
    }
    if(!L||j>i){
        return NULL;
    }
    return L->data;
}
```

### 链表的插入:

```c
//在i位置前插入e
LinkList ListInsert(LinkList *L,int i,int e){
    int j=1;
    LinkList p,s;
    p=*L;
    while (p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i){				//找不到或者链表节点数不允许
        return NULL;
    }
    s=(LinkList)malloc(sizeof(Node));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return *L;
}
```

### 链表的删除:

链表的节点的删除有两个要点，一是要找到该节点，二是要拿到该结点的值（传地址）

```c
LinkList ListDelete(LinkList *L,int i,int *e){//返回删除后的链表,并且用e来储存该节点值
    int j=1;
    LinkList p,q;
    p=*L;
    while (p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i){		//找不到或着链表节点不允许
        return NULL;
    }
    q=p->next;
    p->next=q->next;
    *e=q->data;
    free(q);
    return *L;
}
```



### 链表的输出

```c
void PrintList(LinkList L){
    LinkList p=L->next;
    while (p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
```

### 主程序:

```c
int main(void){
    LinkList L,K;
    int i,j,e;
    printf("Please input the number of the list creat by CreatListHead:\n");
    scanf("%d",&i);
    CreatListHead(&L,i);
    PrintList(L);
    printf("Please input the number of the list creat by CreatListTail:\n");
    scanf("%d",&i);
    CreatListTail(&K,i,0);
    PrintList(K);
    printf("Please input the position of the list you want to insert and intput the number:\n");
    scanf("%d %d",&i,&j);
    if(ListInsert(&L,i,j))
        PrintList(L);
    else
        printf("Insert is wrong.");
    printf("Please input the position of the list you want to delete:\n");
    scanf("%d",&j);
    if(ListDelete(&L,j,&e)){
        printf("the number is:%d\n",e);
        PrintList(L);
    }
    else printf("Delete is wrong");
    printf("the reverse of list is:\n");
    PrintList(ReverseWH(L));
    return 0;
}
```

