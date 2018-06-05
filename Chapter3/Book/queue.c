#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef int QElemtype;

#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1
#define  OVERFLOW   -2

typedef struct QNode
{
	QElemtype data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct {
	QueuePtr front;//队首指针
	QueuePtr rear;//队尾指针
}LinkQueue;
//初始化
Status InitQueue(LinkQueue *Q){//Q是链队的头指针
	Q->front = (QNode *)malloc(sizeof(QNode));//头结点
	if(!Q->front)
	{
		return ERROR;
	}
	Q->front->next = NULL;
	Q->rear = Q->front;
	return OK;
}
//销毁队列
Status DestroyQueue(LinkQueue *Q){
	//free每一个元素
	while(Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	return OK;
}
//将Q清空并释放结点空间
Status ClearQueue(LinkQueue *Q){
	QueuePtr p,tmp;
	p = Q->front->next;
	Q->front->next = NULL;
	Q->rear = Q->front;
	return OK;
}
//判断Q是否为空
Status QueueEmpty(LinkQueue Q)
{
	if(Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}
//返回Q元素的个数
int QueueLength(LinkQueue Q)
{
	int i = 0;
	while(Q.front != Q.rear){
		++i;
		Q.front = Q.front->next;
	}
	return i;
}
//用e返回Q的队头元素
Status GetHead(LinkQueue Q,QElemtype *e)
{
	if(Q.front)
	{
		return ERROR;
	}
	else
		(*e) = Q.front->next->data;
	return OK;
}
//插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue *Q,QElemtype e)
{
	QueuePtr p;
	p = (QNode *)malloc(sizeof(QNode));
	if(!p)
	{
		return ERROR;
	}
	p->data = e;
	p->next = NULL;//初始化结构体类型数据要初始化数据
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}
//出队
Status DeQueue(LinkQueue *Q,QElemtype *e)
{
	QueuePtr p;
	p = Q->front->next;
	if(!Q->front->next)
	{
		return ERROR;
	}
	(*e) = p->data;
	if(Q->front->next == Q->rear)
		Q->rear = Q->front;//当只有一个元素的时候，要重新修改尾指针
	Q->front->next = p->next;
	free(p);
	p = NULL;
	return OK;
}
//遍历
Status QueueTraverse(LinkQueue Q,Status (*visit)(QElemtype *e))
{
	QueuePtr p;
	if(Q.front == Q.rear)
		return ERROR;
	p = Q.front->next;
	while(p){
		(*visit)(&(p->data));//遍历
		p = p->next;
	}
	return OK;
}
//打印元素
Status visit_display(QElemtype *e)
{
	printf("%d",(*e));
	return OK;
}
//链栈其实就是链表的特殊操作，要特别注意的是出栈操作尾指针丢失的情况