#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "link_list.h"

//初始化空链表
void InitList_L(struct LNode * &L)
{
	L = (struct LNode *) malloc (sizeof(LNode));
	L->next = Null;
}
//销毁链表
void DestroyList_L(struct LNode * &L)
{
	free(L);
	L = NULL;
}
//置为空表
void ClearList_L(struct LNode * &L)
{
	L->next = NULL;
}
//判断是否为空表——o(1)
bool ListEmpty_L(struct LNOde * &L)
{
	if(L->next == NULL)
		return true;
	else
		return false;
}
//返回链表的长度——o(n)
int ListLength_L(struct LNode * &L)
{
	int len = 0;
	struct LNode *p = L->next;//p指针指向第一个节点
	while(p != NULL){
		len++;
		p = p->next;
	}
	return len;
}
//算法2.8
//取位序为i的元素——o(n)
Status GetElem_L(struct LNode * &L,int i,ElemType &e)
{
	//L为带头结点的单链表的头指针
	struct LNode *p = L->next;
	int j = 1;
	while(p != NULL && j<i)//直到p指向第i个元素或p为空
	{
		p = p->next;
		j++;
	}
	if(p == NULL || j>i)//第i个元素不存在。j>i好像不可能成立
		return ERROR;
	e = p->data;
	return OK;
}
//返回满足compare()函数的元素——o(n)
int LocateElem_L(struct LNode * &L Elemtype e,Status (*compare)(Elemtype,Elemtype))
{
	struct LNode *p = L->next;
	int i = 0;
	while(p){
		i++;//位序初始化为0，所以先++再判断
		if(compare(e,p->data))
			return i;
		p = p->next;
	}
	return 0;
}
//返回其目标元素的前驱——o(n)
Status PriorElem_L(struct LNode * &L,Elemtype cur_e,Elemtype &pre_e)
{
	int i = 0;
	struct LNode *p = L->next;
	while(p){
		i = LocateElem_L(L,cur_e,compare_equal_Sq);//o(n)
		if(i != 0 && i != 1)
		{
			GetElem_L(L,i-1,pre_e);//o(n)
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}
//获取目标元素的下一个元素——o(n)
Status NextElem_L(struct LNode * &L,Elemtype cur_e,Elemtype &next_e)
{
	int i = 1;
	struct LNode *p = L->next;
	while(p->next)//p没有指向最后一个元素
	{
		i = LocateElem_L(L,cur_e,compare_equal_Sq);//o(0)
		if(i != 0)//
		{
			GetElem_L(L,i+1,next_e);//o(n)
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}
//插入元素——表头o(1),表尾o(n)
Status ListInsert_L(struct LNode * &L,int i,Elemtype e)
{
	//1<=i<=ListLength_Sq(L)+1
	struct LNode *p;
	struct LNode *q;
	int j = 0;
	p = L;
	while(p && j<i-1)//让p指向第i-1个结点——o(i)
	{
		p = p->next;
		++j;
	}
	if(!p || j > i -1)
		return ERROR;
	q = (struct LNode *)malloc(sizeof(LNode));//生成新结点
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}
//删除指定位置的结点——表头o(1)表尾o(n)
Status ListDelete_L(struct LNode * &L,int i,Elemtype &e)
{
	struct LNode *p;
	struct LNode *q;
	int j = 0;
	p = L;
	while(p && j<i-1)
	{
		p = p->next;
		++j;
	}
	if(!p || j>i-1)
		return ERROR;
	q = p->next;//q为被删除结点
	p->next = q->next;
	e = q->data;
	free(q);
	q = NULL;//销毁q结点
	return OK;
}
//遍历——o(n)
Status ListTraverse_L(struct LNode * &L, Status (*visit)(struct LNode * &))
{
	//对每个元素一次调用visit()函数，一旦visit()失败，操作失败
	struct LNode *p;
	p = L->next;//p指向第一个结点
	while(p){
		if(visit(p) == ERROR)
			return ERROR;
		p = p->next;
	}
	return OK;
}
//显示
Status visit_display_L(struct LNode * &L)
{
	printf("%d", L->data);
	return OK;
}
//算法2.11 头插法建立带头结点的单链表——o(n)
void CreateList_L(struct LNode * &L,int n)
{
	int i;
	//建立空链表
	L = (struct LNode *)malloc(sizeof(LNode));
	L->next = NULL;
	//头插法插入元素
	for(i = n;i>0;--i)
	{
		p = (struct LNode *)malloc(sizeof(LNode));//生成新结点
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
}
//算法2.12
void MergeList_L(struct LNode * &La,struct LNode * &Lb,struct LNode * Lc)
{
	//La,Lb非递减排列，要求Lc也按非递减排列
	struct LNode *pa;
	struct LNode *pb;
	struct LNode *pc;
	pa = La->next;//指向La的第一个结点
	pb = Lb->next;//指向Lb的第一个结点
	pc = Lc = La;//以La为主链
	while(pa && pb)
	{
		if((pa->data) > (pb->data))
		{
			pc->next = pb;
			pc = pc->next;
			pb = pb->next;
		}
		else
		{
			pc->next = pa;
			pc = pc->next;
			pa = pa->next;
		}
	}
	pc->next = pa ? pb : pa;
	//销毁Lb
	free(Lb);
	Lb = NULL;
}
