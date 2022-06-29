#include<stdio.h>
#include<stdlib.h>
// #define 0 0
// #define 1 1

typedef struct Node
{
    int data;
    struct Node *next;
}Node;
typedef struct Node *LinkList;
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
void CreatListTail(LinkList *L,int n,int a){    //尾插法创建
    LinkList p,r;
    *L=(LinkList)malloc(sizeof(Node));
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
bool isEmpty(LinkList L){
    if(L->next==NULL){
        return 1;
    }
    return 0;
}
int EnsureElem(LinkList L,int *n){     //查找*n是否在链表内
    for(LinkList p=L;p!=NULL;p=p->next){
        if(p->data==(*n)){
            return 1;
        }
    }
    return 0;
}
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
int GetElem(LinkList L,int i){//       返回在i位置的元素;
    int j=1;
    L=L->next;
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
int ClearList(LinkList *L){
    LinkList p,q;
    p=(*L)->next;
    while (p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;
    return 1;
}
LinkList ListInsert(LinkList *L,int i,int e){
    int j=1;
    LinkList p,s;
    p=*L;
    while (p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!p||j>i){            //找不到或者链表节点数不允许
        return NULL;
    }
    s=(LinkList)malloc(sizeof(Node));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return *L;
}
LinkList ListDelete(LinkList *L,int i,int *e){//返回删除后的链表,并且用e来储存该节点值
    int j=1;
    LinkList p,q;
    p=*L;
    while (p&&j<i)
    {
        p=p->next;
        j++;
    }
    if(!(p->next)||j>i){            //找不到或者链表节点数不允许
        return NULL;
    }
    q=p->next;
    p->next=q->next;
    *e=q->data;
    free(q);
    return *L;
}
LinkList Reverse(LinkList L){ //奇怪的结果,无头结点，导致错误，尚未解决
    L->data=NULL;
    LinkList p1=NULL;
    LinkList p2=NULL;
    LinkList *p=&L;
    while(L){
        p1=L;
        L=L->next;
        p1->next=p2;
        p2=p1;
    }
    L=(LinkList)malloc(sizeof(Node));
    L->next=p2;
    return L;
}
LinkList ReverseWH(LinkList L){     //倒序法,n来保存往后的一个节点,让p,s倒指,用n来查询后面的数,一直保持,最后赋值   带头结点的反转
    LinkList p=L->next;
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
void PrintList(LinkList L){
    LinkList p=L->next;
    while (p)
    {
        printf("%d ",p->data);
        p=p->next;
    }
    printf("\n");
}
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