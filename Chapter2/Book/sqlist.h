#ifndef _Sqlist_H_
#define _Sqlist_H_

//定义顺序表结构及基本算法函数声明

#define OK 1
#define OVERFLOW -1
#define TRUE 1
#define FALSE 0
#define NOTEXIT 0
#define ERROR 0
#define LIST_INT_SIZE 2 //线性表存储空间初始分配容量
#define LISTINCREMENT 10 //线性表存储空间分配增量(用于动态分配)

typedef int Status;
typedef int ElemType;

//结构
struct Sqlist{
	ElemType *elem;//存储空间的基址
	int length;//当前长度
	int listsize;//当前分配的存储容量，注意区分分配的容量和实际的长度的区别
};

//基本算法函数
Status InitList_Sq(struct Sqlist &L);
void DestroyList_Sq(struct Sqlist &L);
void ClearList_Sq(struct Sqlist &L);
Status ListEmpty_Sq(struct Sqlist L);
Status ListLength_Sq(struct Sqlist L);
void GetElem_Sq(struct Sqlist L, int i, ElemType &e);
Status compare_equal_Sq(ElemType e1,ElemType e2);
Status LocateElem_Sq(struct Sqlist L,ElemType e,Status(*compare)(ElemType,ElemType));
Status PriorElem_Sq(struct Sqlist L,ElemType cur_e,ElemType &pre_e);
Status NextElem_Sq(struct Sqlist L,ElemType cur_e,ElemType &next_e);
void ListInsert_Sq(struct Sqlist &L,int i,ElemType e);
void ListDelete_Sq(struct Sqlist &L,int i,ElemType &e);
Status ListTraverse_Sq(struct Sqlist L,Status (*visit)(ElemType));
Status visit_display_Sq(ElemType e);

void unionList_Sq(struct Sqlist &La,struct Sqlist Lb);
void MergeList_Sq(struct Sqlist La,struct Sqlist Lb,struct Sqlist &Lc);

#endif