#include <stdio.h>
#include <math.h>//floor(),ceil(),abs()
#include <stdlib.h>//malloc(),free()

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int Status;//表示函数的类型，值是函数结果状态代码，比如OK
typedef int ElemType;

//存储结构
struct LNode
{
	ElemType data;
	struct LNode *next;
};
typedef struct LNode *LinkList;//另一种定义LinkList的方法

//构造空的单循环链表,单向循环链表比较好的是表尾指针，特别便于merge两个链表！
//L表示的是表尾指针
Status InitList_CL(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(struct LNode));//初始化头结点
	if(!*L)
	{
		exit(OVERFLOW);//存储分配失败
	}
	(*L)->next = *L;//指针域指向头结点表示为空
	return OK;
}
//判断是否为空
Status ListEmpty_CL(LinkList L)
{
	if(L->next == L)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//返回L中的元素个数
int ListLength_CL(LinkList L)
{
	int i = 0;
	LinkList p = L->next;//p指向表头结点
	while(p != L)//没到表尾
	{
		++i;
		p = p->next;
	}
	return i;
}
//在第i个位置上插入元素e,注意尾结点之后插入的情况
Status ListInsert_CL(LinkList *L,int i,ElemType e)
{
	LinkList p = (*L)->next,s;//p指向表头结点
	int j = 0;
	if(i<1 || (i>ListLength_CL(*L) + 1))
	{
		return ERROR;
	}
	while (j < i-1)
	{
		p = p->next;
		++j;
	}
	s = (LinkList)malloc(sizeof(struct LNode));//新的节点
	s->data = e;
	s->next = p->next;
	p->next = s;
	//如果插入的最后一个结点的后面
	if(p == *L)
	{
		*L = s;
	}
	return OK;
}
//获取第i个元素的值
Status GetElem_CL(LinkList L,int i,ElemType *e)
{
	int j = 1;
	LinkList p = L->next->next;//L表示表尾指针，p指向第一个节点
	if((i < 1) || i > ListLength_CL(L))
	{
		return ERROR;
	}
	while(j<i)
	{
		p = p->next;
		++j;
	}
	*e = p->data;
	return OK;
}
//删除第i个位置的元素
Status ListDelete_CL(LinkList *L,int i)
{
	LinkList p = (*L)->next,s;
	int j = 0;
	if(i<1 || i>ListLength_CL(*L))
	{
		return ERROR;
	}
	while(j< i-1)//返回要删除元素的前一个元素
	{
		p = p->next;
		++j;
	}
	s = p->next;
	p->next = s->next;
	//如果删除的是尾结点
	if(s == *L)
	{
		*L = p;
	}
	free(s);
	return OK;
}
//遍历
Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
{
	LinkList p = L->next->next;//第一个结点
	while(p!=L->next)
	{
		vi(p->data);
		p = p->next;
	}
	return OK;
}
//返回指定元素的前驱，如果是第一个元素，则返回false
Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
{
	LinkList q,p = L->next->next;
	q = p->next;
	while(q != L->next)//p没有到表尾
	{
		if(q->data == cur_e)
		{
			*pre_e = p->data;
			return TRUE;
		}
		p = q;
		q = q->next;
	}
	return FALSE;
}
//返回指定元素的后继，如果是最后一个，则返回false
Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
{
	LinkList p = L->next->next;
	while(p != L)//p没有到表尾
	{
		if(p->data == cur_e)
		{
			*next_e = p->next->data;
			return TRUE;
		}
		p = p->next;
	}
	return FALSE;
}
//返回第一个与e满足compare()的位序
int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	int i = 0;
	LinkList p = L->next->next;
	while(p != L->next)
	{
		++i;
		if(compare(p->data,e))//满足条件
			return i;
		p = p->next;
	}
	return 0;
}
void visit(ElemType c)
{
	printf("%d", c);
}
//销毁
Status DestroyList_CL(LinkList *L)
{
	LinkList q,p = (*L)->next;
	while(p!=*L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(*L);
	*L = NULL;
	return OK;
}
//置为空表
Status ClearList_CL(LinkList *L)
{
	LinkList p,q;
	*L = (*L)->next;//尾指针变为头指针
	p = (*L)->next;//指向第一个结点
	while(p!=*L)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = *L;//头指针指向自身
	return OK;
}
//合并两个单循环链表——带尾结点的单循环链表的优点
void MergeList_CL(LinkList *La,LinkList Lb)
{
	LinkList p = Lb->next;//Lb的头结点
	Lb->next = (*La)->next;
	(*La)->next = p->next;//La尾指针指向Lb头结点；La在前，Lb在后
	free(p);
	*La = Lb;//两个指针都成为合并之后链表的尾指针
}
int main()
{
	LinkList L,Lb;//带头结点、单向循环链表的表尾指针
	ElemType e;
	int j;
	Status i;
	InitList_CL(&L);//先初始化
	ListInsert_CL(&L,1,3);
	ListInsert_CL(&L,2,5);
	ListInsert_CL(&L,3,7);
	i = GetElem_CL(L,1,&e);
	if(i==OK)
	{
		printf("%d\n",e);
	}
	return 0;
}
