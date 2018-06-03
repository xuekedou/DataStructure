#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int Status;

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0

//结点类型
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}*Link, *Position;

//链表类型
typedef struct{
	Link head, tail;//指向头结点和尾结点
	int len;//链表中元素的个数
}LinkList;

//分配由p指向的值为e的节结点——初始化结点及结点的值
Status MakeNode(Link *p,ElemType e)
{
	*p = (Link)malloc(sizeof(Link));
	if(!*p)//分配失败
	{
		return ERROR;
	}
	(*p)->data = e;
	return OK;
}
//释放p所指的结点
void FreeNode(Link *p)
{
	free(*p);
	*p = NULL;
}

//构造一个空的线性链表
Status InitList(LinkList *L)
{
	Link p;
	p = (Link)malloc(sizeof(Link));
	if(!p)
	{
		return ERROR;
	}
	p->next = NULL;//p为头结点
	(*L).head = (*L).tail = p;
	(*L).len = 0;//初始化长度为0
	return OK;
}
//置链表为空，并释放原链表的结点空间,头尾指针都指向头结点
Status ClearList(LinkList *L)
{
	Link p,q;
	p = (*L).head -> next;//第一个结点
	(*L).head->next = NULL;
	while(p != NULL)//遍历释放所有元素
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L).tail = (*L).head;//头尾指针都指向头结点
	(*L).len = 0;
	return OK;
}
//销毁线性表,L不存在
Status DestroyList(LinkList *L)
{
	ClearList(L);
	free((*L).head);//释放头结点
	(*L).head = (*L).tail = NULL;//指针指向空
	(*L).len = 0;//长度变为0
	return OK;
}
//h指向链表头结点，s头插到h之前
Status InsFirst(Link h,Link s)
{
	s->next = h->next;
	h->next = s;
	return OK;
}
//删除第一个结点，并以q返回它
Status DelFirst(Link h,Link *q)
{
	if(h->next == NULL)//链表为空返回ERROR
	{
		return ERROR;
	}
	*q = h->next;
	h->next = (*q)->next;
	(*q)->next = NULL;
	return OK;
}
//将s所指向的一串结点链接到L最后一个结点之后,注意修改尾指针
Status Append(LinkList *L,Link s)
{
	int i = 1;
	(*L).tail->next = s;//链接
	while(s->next != NULL)//寻找尾指针
	{
		s = s->next;
		i++;
	}
	(*L).tail = s;//修改尾指针
	(*L).len += i;
	return OK;
}
//删除L尾结点，并以q返回
Status Remove(LinkList *L, Link *q)
{
	Link p;
	p = (*L).head;
	if((*L).head == (*L).tail)//只有头结点
		return ERROR;
	(*q) = (*L).tail;
	while(p->next != (*q))
	{
		p = p->next;
	}
	p->next = NULL;//删除尾结点
	(*L).tail = p;//修改尾指针
	(*L).len--;//长度--
	return OK;
}
//已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之前
Status InsBefore(LinkList *L, Link *p, Link s)
{
	Link h = (*L).head;
	while((*p) != h->next)
	{
		h  = h->next;
	}
	s->next = (*p);
	h->next = s;
	(*p) = s;//修改p指向新插入的结点
	(*L).len++;
	return OK;
}
Status InsAfter(LinkList *L,Link *p,Link s)
{
	s->next = (*p)->next;
	(*p)->next = s;
	if((*p) == (*L).tail)
		(*L).tail = s;//修改尾指针
	(*p) = s;
	(*L).len++;
	return OK;
}
//修改指定结点的元素值
Status SetCurElem(Link *p,ElemType e)
{
	(*p)->data = e;
	return OK;
}
//返回指定结点的元素值
ElemType GetCurElem(Link p)
{
	return p->data;
}
//返回链表是否为空
Status ListEmpty(LinkList L)
{
	if(L.head->next == NULL)
		return TRUE;
	else
		return FALSE;
}
//返回链表长度
int ListLength(LinkList L)
{
	return L.len;
}
//返回头结点位置
Position GetHead(LinkList L)
{
	return L.head;//返回头结点的位置
}
Position GetLast(LinkList L)
{
	return L.tail;
}
//返回指定结点的前驱
Position PriorPos(LinkList L,Link p)
{
	Link pri = L.head;
	while(pri->next != p)
	{
		pri = pri->next;
	}
	if(L.head == pri)//p没有直接前驱
		return NULL;
	return pri;
}
Position NextPos(LinkList L,Link p)
{
	if(p == L.tail)
		return NULL;
	return p->next;//直接后继不用遍历
}
//返回第i个位置的元素,找到了返回1，未找到返回0
Status LocatePos(LinkList L,int i,Link *p)
{
	if(i<0 || i>L.len)
		return 0;
	(*p) = L.head;
	while(i!=0)
	{
		i--;//通过序号判断
		(*p) = (*p)->next;
	}
	return 1;
}
//返回线性表中第1个与e满足compare函数的元素
Position LocateElem(LinkList L,ElemType e,int (*compare)(ElemType,ElemType))
{
	Link p = L.head->next;
	while(p){
		if(0 == (*compare)(e,p->data))
			return p;
		p = p->next;
	}
	return NULL;
}
//遍历
Status ListTraverse(LinkList L,void (*visit)(Link))
{
	Link p = L.head->next;
	while(p)
	{
		visit(p);
		p = p->next;
	}
	return OK;
}
//遍历显示结点的值
void visit_display(Link p)
{
	printf("%d", p->data);
}
//算法2.20 在第i个元素之前插入e——o(n)
Status ListInsert(LinkList *L,int i,ElemType e)
{
	Link h,s;//双指针
	if(!LocatePos((*L),i-1,h)//h指向第i-1个元素——o(n)
		return ERROR;
	if(!MakeNode(s,e))
		return ERROR;
	if(h == (*L).tail)
		(*L).tail = s;//尾部插入，修改尾指针
	InsFirst(h,s);//对于从第i个结点开始的链表，第i-1个结点就是它的头结点
	(*L).len++;
	return OK;
}
//La Lb按值非递减排列
//归并La Lb到Lc中，让Lc也非递减排列
Status MergeList_L(LinkList *La,LinkList*Lb,LinkList *Lc,int (*compare)(ElemType,ElemType))
{
	Link ha,hb,pa,pb,q;
	ElemType a,b;
	if(!InitList(*Lc)) return ERROR;//存储分配失败
	ha = GetHead(La);
	hb = GetHead(Lb);
	pa = NextPos(La,ha);
	pb = NextPos(Lb,hb);
	while(pa && pb)
	{
		a = GetCurElem(pa);
		b = GetCurElem(pb);
		if((*compare)(a,b)<=0)//a<=b
		{
			DelFirst(ha,q);//删除ha后面的第一个结点，并以q返回
			Append(Lc,q);//尾插法
			pa = NextPos(La,ha);//pa指向ha在La中的后继
		}
		else//a>b
		{
			DelFirst(hb,q);
			Append(Lc,q);
			pb = NextPos(Lb,hb);//实际上pa始终在hb之后
		}
		if(pa) Append(Lc,pa);
		else Append(Lc,pb);
		FreeNode(ha);//释放头结点(free结点+指针指向NULL)
		FreeNode(hb);
		return OK;
	}
}





