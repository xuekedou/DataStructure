#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int DataType;

typedef struct  DNode
{
	ElemType data;
	struct DNode *pre, *next;
}DNode, *DLinkList;

//创建长度为n的双循环链表
void ListCreate(DLinkList L,int n)
{
	int i;
	DLinkList p,s;//初始化结点
	p = L;
	L->pre = L->next = L;//空双循环链表的判定条件
	for(i = 0;i<n;i++)
	{
		s = (DLinkList)malloc(sizeof(DNode));
		scanf("%d",&s->data);

		p->next = s;
		s->pre = p;

		s->next = L;
		L->pre = s;

		p = s;//链表元素的顺序和输入的顺序一致
	}
}
//在第i个位置插入元素e
void ListInsert(DLinkList L,int i,ElemType e)
{
	DLinkList s,p = L;
	while(p->next != L && i > 1)//p->next!=L保证不会重复循环，p是待插入位置的前一个元素
	{
		p = p->next;
		i--;
	}
	s = (DLinkList)malloc(sizeof(DNode));
	s->data = e;

	s->next = p->next;
	//if(p->next != NULL)//非循环链表需要判断是否空
	p->next->pre = s;//先连
	s->pre = p;
	p->next = s;//后断
}
//删除i位置的元素
void ListDelete(DLinkList L,int i,ElemType *e)
{
	DLinkList p = NULL,q = L;
	while(q->next != L && i>=1)//
	{
		p = q;
		q = q->next;
		i--;
	}
	p->next = q->next;
	q->next->pre = p;
	*e = q->data;
	free(q);
}
//正向遍历
void ListTraverse(DLinkList L)
{
	DLinkList p = L;
	while(p->next != L)
	{
		p = p->next;//先移动指针，再打印
		printf("%d", p->data);
	}
	printf("\n");
}
//逆向遍历
void ListReTraverse(DLinkList L)
{
	DLinkList p = L;
	while(p->pre != L)
	{
		p = p->pre;
		printf("%d", p->data);
	}
	printf("\n");
}
int main()
{
	DNode L;
	int e;
	ListCreate(&L,3);//初始化
	ListTraverse(&L);//正向遍历

	ListInsert(&L,1,0);
	ListTraverse(&L);

	ListInsert(&L,5,7);
	ListTraverse(&L);

	ListDelete(&L,1,&e);
	ListTraverse(&L);

	ListReTraverse(&L);//逆向遍历
}
