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

//队列的线性表示一般用循环队列
//顺序存储结构
#define MAXQSIZE 100;//最大的存储长度
typedef struct{
	QElemtype *base;//基址
	int front;//头指针，若队列不空，指向队头元素
	int rear;//尾指针，若队列不空，指向对尾元素的后一个位置
}SqQueue;
//初始化空的循环队列
Status InitQueue(SqQueue *Q)
{
	Q->base = (QElemtype *)malloc(MAXQSIZE * sizeof(QElemtype));
	if(!Q->base)
	{
		return ERROR;
	}
	Q->front = 0;//循环队列起始地址为0
	Q->rear = 0;
	return OK;
}
//销毁队列
Status DestroyQueue(SqQueue *Q)
{
	free(Q->base);
	Q->base = NULL;
	return OK;
}
//清空队列
Status ClearQueue(SqQueue *Q)
{
	Q->front = Q->rear = 0;
	return OK;
}
//判断是否为空
Status QueueEmpty(SqQueue *Q)
{
	if(Q->front == Q->rear)
	{
		return TRUE;
	}
	else
		return FALSE;
}
//返回队列Q元素个数
Status QueueLength(SqQueue Q)
{
	//循环队列是线性存储，序号相邻，位置也相邻
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
//得到队头元素
Status GetHead(SqQueue Q,QElemtype *e)
{
	if(Q->head == Q->rear)
		return ERROR;
	(*e) = *(Q->base+Q->front);
	return OK;
}
//插入元素e为Q的新的队尾元素——求余运算
Status EnQueue(SqQueue *Q,QElemtype e)
{
	if (((Q->rear - Q->front + MAXQSIZE) % MAXQSIZE)==1)//循环队列的循环只是假象循环
		return ERROR;
	Q->base + Q->rear = e;//加上基址
	Q->rear = (Q->rear + 1)%MAXQSIZE;//front之前的存储空间可能为空值
	return OK;
}
//删除队头元素
Status DeQueue(SqQueue *Q,QElemtype *e)
{
	if(Q->rear == Q->front)
		return ERROR;
	(*e) = *(Q->base + Q->front)
	Q->front = (Q->front + 1)%MAXQSIZE;
	return (*e);
}
//遍历
Status QueueTraverse(SqQueue Q,Status (*visit)(QElemtype *e))
{
	int p;
	p = Q->front;
	while(p != Q->rear)
	{
		if(!(*visit)(*(Q.base+p)))
			return ERROR;
		p = (p+1)%MAXQSIZE;
	}
	return OK;
}