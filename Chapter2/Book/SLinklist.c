#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int DataType;
//存储结构
#define MAXSIZE 100
typedef struct 
{
	ElemType data;
	int cur;//整型游标，类似指针的作用
}SLinkList[MAXSIZE];

//初始化操作
void SListInit(SLinkList space)
{
	int i;
	for(i = 0;i<MAXSIZE;++i)
	{
		space[i].cur = i+1;//将所有结点链入备用链表
	}
	space[0].cur = space[1].cur;//第0个节点作为备用链表的头结点，指向第二个结点
	space[1].cur = 0;//第一个节点作为链表的头结点，游标为0类似于指针为空
}
//初始化一个结点
int Malloc_SL(SLinkList space)
{
	int i = space[0].cur;
	if(space[0].cur)//判断备用链表是否非空
		space[0].cur = space[i].cur;//备用链表的第一个结点，也就是第一个可以使用的空结点
	return i;//返回第一个空结点在数组中的下标
}
//free一个结点
void Free_SL(SLinkList space,int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;//类似指针操作
}
//获取链表长度
int SListLenght(SLinkList space)
{
	int len = 0;
	int i = space[1].cur;//链表第一个结点的下标
	while(i)
	{
		++len;
		i = space[i].cur;
	}
	return len;
}
//在链表第i个位置插入元素e
void SListInsert(SLinkList space, int i, ElemType e)
{
	if(i<1 || i > SListLenght(space) + 1)//超出范围
		return;
	int k = 1,j;
	for(j = 0;j<i-1;++j)
		k = space[k].cur;//k指向要插入结点的前一个结点
	int v = Malloc_SL(space);//备用链表的第一个结点的下标
	if(v)
	{
		space[v].data = e;
		space[v].cur = space[k].cur;
		space[k].cur = v;//链入链表,不需要脱离备用链表，因为备用链表的头结点cur为0
	}
}
//删除第i个位置的元素
void SListDelete(SLinkList space, int i)
{
	int k = 1,j;
	for(j = 0;j<i-1;++j)
	{
		k = space[k].cur;//k指向要删除结点的前一个结点
	}
	int d = space[k].cur;
	space[k].cur = space[d].cur;//链表中删除

	space[d].cur = space[0].cur;//备用链表中添加
	space[0].cur = d;
}
//遍历链表
void SListTraverse(SLinkList space)
{
	int i = space[1].cur;
	while(i)
	{
		printf("%d\n", space[i].data);
		i = space[i].cur;
	}
}
//测试代码
int main()
{
	SLinkList space;
	SListInit(space);//初始化
	int i;
	for(i = 1;i<=10;i++)
	{
		SListInsert(space,i,i);
	}
	SListDelete(space,10);
	SListTraverse(space);
	return 0;
}