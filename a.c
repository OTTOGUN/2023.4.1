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

//����������������������������������������˳���������������������������������������������������
typedef struct{
    SeqType *elem;
    int length;
    int listsize;
} SqList;

SqList createList_sq(void){
    //SqList list; >>>>>>>ϵͳ����listռ�õ��ڴ�
    //return list;

    SqList* list = (SqList*)malloc(sizeof(SqList));
    return *list;  //>>>>>>>>�Զ��崴��
}

int initList_sq(SqList* L){
    L->elem = (SeqType*)malloc(sizeof(SeqType) * LIST_INIT_SIZE);
    if(!L->elem){
        strerror(errno);//>>>>>��������ԭ��:�ڴ治��
    }
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return 1;
}

int insertList(SqList* L,int index,SeqType val){
    if(index > L->length){
        printf("������±곬��˳���ĳ���");
        return 0;
    }
    if(index < L->length){
        index = L->length;
    }
    if(L->length == L->listsize){
        printf("�洢��Ԫ����,��Ҫ���·����ڴ�");
    }
    SqList* newBase = (SqList*)realloc(L->elem,(L->listsize + LISTINCREMENT)* sizeof(SeqType));
    if(!newBase){
        printf("�����ڴ�ʧ��");
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
            printf("û�д�Ԫ�أ�");
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

//����������������������������������������������������������������������������������������������������������������������������


//������������������������������������������������������������������������������������������

typedef struct link{
    int elem;
    struct link* next;
}Link;          //����������������Ľṹ�������� + ָ����

Link* initLink(){
    int i ;
    //1.��������ͷָ��
    Link* p = NULL;
    //2.��������ͷ�ڵ�
    Link* head = (Link*)malloc(sizeof(Link));
    head->elem = NULL;
    head->next = NULL;
    //����ͷָ��ָ��ͷ���
    p = head;
    //3.����ÿ����һ����㣬����ֱ��ǰ������ָ��ָ����
    for(i = 1;i < 5;i++){
        Link* a = (Link*)malloc(sizeof(Link));
        a->elem = i;
        a->next = NULL;
        //����ÿ��tempָ��Ľ�����a��ֱ��ǰ�����
        head->next = a;
        //����tempָ����һ�����(Ҳ����a)��Ϊ�´���ӽ����׼��
        head = head->next;
    }
    return p;
}

//����������pΪԭ����elem ΪҪ�����Ŀ��Ԫ��
void insertElem(Link* p,int elem,int add){
    int i = 0;
    Link* c = NULL;
    Link* temp = p;//����������ʱ���temp
    //���������ҵ�Ҫ����λ�õ���һ�����
    for(i = 1;i < add;i++){
        temp = temp -> next;
        if(temp == NULL){
            printf("������Ч\n");
        }
        //��������������
        c = (Link*)malloc(sizeof(Link));
        c -> elem = elem;
        //�ٽ��µĽ��nextָ��ָ�����λ�ú�Ľ��
        c -> next = temp ->next;
        //�ڽ�����λ��ǰ����nextָ��ָ�������
        temp -> next = c;
    }
}

void deleteElem(Link* p,int delete){
    int i = 0;
    Link* c = NULL;
    Link* temp = p;
    for(i = 1;i < delete;i++){
        if(temp == NULL){
            printf("����");
        }
        temp = temp -> next;
    }
    c = temp -> next;
    temp -> next = temp -> next -> next;
    free(c);
}

//����������pΪԭ����elemΪҪ���ҵĵ�Ŀ��Ԫ��
int selectElem(Link* p,int elem){
    int i = 1;
    //��ͷ��㣬pָ����Ԫ���
    p = p -> next;
    while(p){
        if(p -> elem == elem){
            return i;
        }
        p = p -> next;
        i++;
    }
}

//������pΪ��ͷ��������oldElemΪ��Ԫ�أ�newElemΪ��Ԫ��
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

//����������������������������������������������������������������������������������������������������
//����������������������������˫������������������������������������������������������������������<

typedef struct line{
    struct line* prior;
    int data;
    struct line* next;
}Line;

Line* initLine(Line* head){
    Line* list = NULL;
    //���������������һ�����
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
        //����������ýڵ��޺�̽ڵ㣬˵���˽�����������һ���ڵ�
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
    printf("����ĵ�4���ڵ��ֱ��ǰ���ǣ�%d",head -> next -> next -> next -> prior -> data);
    free_Line(head);
    return 0;
}