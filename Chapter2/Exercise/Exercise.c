#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FLASE 0
#define OVERFLOW -1
#define NOTEXIT 0
#define LIST_INT_SIZE 2
#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;

struct Sqlist{
	ElemType *elem;//存储空间基址
	int length;
	int listsize;
};
struct LNode
{
	ElemType data;
	struct LNode *next;
};
//习题2.12
int compareList(struct Sqlist La,struct Sqlist Lb)
{
	int i = 0;
	ElemType *pa;
	ElemType *pb;
	pa = La.elem;//pa为La的基址
	pb = Lb.elem;//pb为Lb的基址
	while(i<La.length && i<Lb.length)
	{
		if((*(pa+i)) > (*(pb+i)))//线性表的连续性，所以"pa+1"表示下一个元素的地址
			return 1;
		else if((*(pa+i)) < (*(pb+i)))
			return -1;
		else
			i++;
	}
	if(i == La.length && i == Lb.length)
		return 0;
	if(i<Lb.length)
		return -1;//la<lb
	if(i<La.length)
		return 1;//la>lb
	return -2;
}
//习题2.21 线性表的就地逆置——用一个指针即可
void reverseList(struct Sqlist L)
{
	int i;
	ElemType *p,tmp;
	p = L.elem;
	for(i = 0;i<(L.length)/2;i++)
	{
		tmp = *(L.elem + i);//充分发挥顺序表元素物理位置连续的特点
		*(L.elem + i) = *(L.elem + L.length - i - 1);
		*(L.elem + L.length - i - 1) = tmp;
	}
}
//习题2.22 单链表就地逆置
void reverseLinkList(struct LNode *L)
{
	struct LNode *p;
	struct LNode *tmp;
	//头插法
	p = L->next;//指向第一个结点
	L->next = NULL;
	while(p)
	{
		tmp = p->next;
		p->next = L->next;
		L->next = p;
		p = tmp;
	}
}
//习题2.24 La,Lb递增，归并Lc递减
void reverseMergeList(struct LNode *La,struct LNode *Lb)
{
	struct LNode *pa;
	struct LNode *pb;
	struct LNode *tmp;

	pa = La->next;
	pb = Lb->next;

	La->next = NULL;
	Lb->next = NULL;

	while(pa && pb)
	{
		if(pa->data <= pb->data)
		{
			tmp = pa->next;
			pa->next = La->next;
			La->next = pa;
			pa = tmp;
		}
		else 
		{
			tmp = pb->next;
			pb->next = La->next;
			La->next = pb;
			pb = tmp;
		}
	}
	if(pa)
	{
		while(pa)
		{
			tmp = pa->next;
			pa->next = La->next;
			La->next = pa;
			pa = tmp;
		}
	}
	if(pb)
	{
		while(pb)
		{
			tmp = pb->next;
			pb->next = La->next;
			La->next = pb;
			pb = tmp;
		}
	}//La即为符合要求的链
}
//习题2.38
typedef struct DNode
{
	ElemType data;
	struct DNode *pre,*next;
	int freq;
}DNode,*DLinkList;

DLinkList Locate(DLinkList *L,ElemType x)
{
	DNode *p = (*L)->next,*q;//p为工作指针，q为前驱记录指针
	while(p && p->data != x)
	{
		p = p->next;
	}
	if(!p)
	{
		printf("不存在值为x的结点\n");
		exit(0);
	}
	else
	{
		p->freq++;
		//摘下目标结点
		q = p->pre;
		p->next->pre = p->pre;
		p->pre->next = p->next;
		//查找插入位置——找到第一个freq大于现结点的结点
		while(q!=(*L)&&q->freq < p->freq)
		{
			q = q->pre;
		}
		//插入结点
		p->next = q->next;
		p->pre = q;
		q->next->pre = p;
		q->next = p;//先连后断，先连后再连前
	}
	return p;
}


