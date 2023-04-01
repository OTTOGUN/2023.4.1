//
// Created by 39221 on 2023/3/16.
//
#include<stdio.h>
#include <synchapi.h>
#include<string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#ifndef SQLIST_H_
#define SQLIST_H_
#define LIST_INIT_SIZE 50
#define LISTINCREMENT 10
#endif /* sqlist_h_ */
typedef int SeqType;

//》》》》》》》》》》》》》》》》》》》》顺序表《《《《《《《《《《《《《《《《《《《《《《《《《
typedef struct{
    SeqType *elem;
    int length;
    int listsize;
} SqList;

SqList createList_sq(void){
    //SqList list; >>>>>>>系统分配list占用的内存
    //return list;

    SqList* list = (SqList*)malloc(sizeof(SqList));
    return *list;  //>>>>>>>>自定义创建
}

int initList_sq(SqList* L){
    L->elem = (SeqType*)malloc(sizeof(SeqType) * LIST_INIT_SIZE);
    if(!L->elem){
        strerror(errno);//>>>>>输出错误的原因:内存不够
    }
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 1;
}

int insertList(SqList* L,int index,SeqType val){
    if(index > L->length){
        printf("插入的下标超出顺序表的长度");
        return 0;
    }
    if(index < L->length){
        index = L->length;
    }
    if(L->length == L->listsize){
        printf("存储单元已满,需要重新分配内存");
    }
    SqList* newBase = (SqList*)realloc(L->elem,(L->listsize + LISTINCREMENT)* sizeof(SeqType));
    if(!newBase){
        printf("分配内存失败");
        return 0;
    }
    L->elem = newBase;
    L->listsize += LISTINCREMENT;

    for(int i = L->length;i > index;i--){
        L->elem[i] = L->elem[i - 1];
    }
    L->elem[index] = val;
    L->length++;
    return 1;
}

int removeList_sq(SqList* L,SeqType val){
    int index = -1;
    for(int i = 0;i < L->length;i++){
        if(L->elem[i] == val){
            index = i;
            break;
        }else{
            printf("没有此元素！");
            return 0;
        }
    }
    for(;index < L->length;index++){
        L->elem[index] = L->elem[index + 1];
    }
    L->length--;
    return 1;
}

int removeList_sq1(SqList* L,int index,SeqType* elem){
    if(index >= L->length){
        return 0;
    }
    index = index < 0 ? L->length:index;
    elem = L->elem[index];
    for(;index < L->length - 1;index++){
        L->elem[index] = L->elem[index + 1];
    }
    L->length--;
    return 1;
}

void destory_List(SqList* L){
    L->length = 0;
    L->listsize = 0;
    free(L->elem);
    free(L);
}

//》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》


//》》》》》》》》》》》》》》》》》》链表《《《《《《《《《《《《《《《《《《《《《《《《《《

typedef struct link{
    int elem;
    struct link* next;
}Link;          //》》》》》单链表的结构，数据域 + 指针域

Link* initLink(){
    int i ;
    //1.》》创建头指针
    Link* p = NULL;
    //2.》》创建头节点
    Link* head = (Link*)malloc(sizeof(Link));
    head->elem = NULL;
    head->next = NULL;
    //》》头指针指向头结点
    p = head;
    //3.》》每创建一个结点，都令直接前驱结点的指针指向它
    for(i = 1;i < 5;i++){
        Link* a = (Link*)malloc(sizeof(Link));
        a->elem = i;
        a->next = NULL;
        //》》每次temp指向的结点就是a的直接前驱结点
        head->next = a;
        //》》temp指向下一个结点(也就是a)，为下次添加结点做准备
        head = head->next;
    }
    return p;
}

//》》》》》p为原链表，elem 为要插入的目标元素
void insertElem(Link* p,int elem,int add){
    int i = 0;
    Link* c = NULL;
    Link* temp = p;//》》创建临时结点temp
    //》》首先找到要插入位置的上一个结点
    for(i = 1;i < add;i++){
        temp = temp -> next;
        if(temp == NULL){
            printf("插入无效\n");
        }
        //》》创建插入结点
        c = (Link*)malloc(sizeof(Link));
        c -> elem = elem;
        //①将新的结点next指针指向插入位置后的结点
        c -> next = temp ->next;
        //②将插入位置前结点的next指针指向插入结点
        temp -> next = c;
    }
}

void deleteElem(Link* p,int delete){
    int i = 0;
    Link* c = NULL;
    Link* temp = p;
    for(i = 1;i < delete;i++){
        if(temp == NULL){
            printf("寄了");
        }
        temp = temp -> next;
    }
    c = temp -> next;
    temp -> next = temp -> next -> next;
    free(c);
}

//》》》》》p为原链表，elem为要查找的的目标元素
int selectElem(Link* p,int elem){
    int i = 1;
    //带头结点，p指向首元结点
    p = p -> next;
    while(p){
        if(p -> elem == elem){
            return i;
        }
        p = p -> next;
        i++;
    }
}

//》》》p为有头结点的链表，oldElem为旧元素，newElem为新元素
int amendElem(Link* p,int oleElem,int newElem){
    p = p -> next;
    while(p){
        if(p -> elem == oleElem){
            p -> elem = newElem;
        }
        p = p -> next;
    }
    return -1;
}

//》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》
//》》》》》》》》》》》》》》双向链表《《《《《《《《《《《《《《《《《《《《《《《《《《《《《《《<

typedef struct line{
    struct line* prior;
    int data;
    struct line* next;
}Line;

Line* initLine(Line* head){
    Line* list = NULL;
    //》》》创建链表第一个结点
    head = (Line*)malloc(sizeof(Line));
    head -> prior = NULL;
    head -> next = NULL;
    head -> data = 0;
    list = head;
    for(int i = 1;i <= 5;i++){
        Line* a = (Line*)malloc(sizeof(Line));
        a -> data = i;
        a -> prior = list;
        a -> next = NULL;
        list -> next = a;
        list = list -> next;
    }
    return head;
}

void display(Line* head){
    Line* temp = head;
    while(temp)
    {
        //》》》如果该节点无后继节点，说明此节是链表的最后一个节点
        if(temp -> next != NULL)
        {
            printf("%d ",temp -> data);
        }else{
            printf("%d\n",temp ->data);
        }
        temp = temp -> next;
    }
}

void free_Line(Line* head){
    Line* temp = head;
    while(temp){
        head = head -> next;
        free(temp);
        temp = head;
    }
}

int main(){
    Line* head = NULL;
    head = initLine(head);
    display(head);
    printf("链表的第4个节点的直接前驱是：%d",head -> next -> next -> next -> prior -> data);
    free_Line(head);
    return 0;
}