#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;//status是函数类型，其值是函数结果状态码

//存储结构
typedef struct Polynomial
{
	float coef;//系数
	int expn;//指数
	struct Polynomial *next;//结点指针域
}Polynomial,*LinkList;
/*
c和c++区别：
在GCC编译器上，出错原因是：在c中没有像C++所谓的“按引用传递”，例如C++可以这样申明函数：
Status createPolyn(LinkList &L,int m){}
但是在c中是无法这样使用的，所以要改成“地址引用”
Status createPolyn(LinkList *L,int m){}
调用函数的时候就改为
Polynomial *pa = (LinkList)malloc(sizeof(Polynomial));
pa->next = NULL;
createPolyn(&pa,4);
*/

//创建具有m个项的一元多项式
Status CreatePolyn(LinkList *L,int m)
{
	Polynomial *q = *L;//q指向头结点
	float coef;
	int expn;
	int i;
	for(i = 0;i<m;i++)
	{
		printf("请输入系数：");
		scanf("%f",&coef);
		printf("请输入指数：");
		scanf("%d",&expn);

		Polynomial * Polyn = (LinkList)malloc(sizeof(Polynomial));//创建新结点
		if(!Polyn)
			return ERROR;//存储分配失败
		Polyn->coef = coef;
		Polyn->expn = expn;

		q->next = Polyn;
		q = Polyn;//q始终指向最后一个结点
	}
	q->next = NULL;
	return OK;
}
//多项式Pa和Pb相加，将结果保存在Pa链中
void AddPolyn(LinkList *La,LinkList *Lb){
	Polynomial *qa = *La;
	Polynomial *qb = *Lb;//指向头结点
	while(qa->next && qb->next)
	{
		//1.如果qa指向结点的下一个结点的指数大于qb指向结点的下一个结点的指数，就把qb所指结点插入到qa之后。注：qa和qb均为比较结点的前一个结点
		if((qa->next->expn) > (qb->next->expn))
		{
			Polynomial *tmp = qb->next;
			qb->next = tmp->next;

			tmp->next = qa->next;
			qa->next = tmp;

			qa = qa->next;
		}
		else if ((qa->next->expn) < (qb->next->expn))
		{
			qa = qa->next;//结果返回pa链
		}
		else if((qa->next->expn) == (qb->next->expn))
		{
			float tmp = (qa->next->coef) + (qb->next->coef);
			//分别从qa、qb中删除当前结点
			if(tmp == 0)
			{
				qa->next = qa->next->next;
			}
			//修改qa结点的系数，后移指针
			if(tmp != 0)
			{
				qa->next->coef = tmp;
				qa = qa->next;
			}
			qb = qb->next;
		}
	}
}
//打印链上所有的值
void PrintAllValues(LinkList *L)
{
	Polynomial *q = *L;//指向头结点
	while(q->next){
		printf("系数 : %f", q->next->coef);
		printf("指数 : %d\n", q->next->expn);
		q = q->next;
	}
}
int main()
{
	//创建多项式pa
	Polynomial *pa = (LinkList)malloc(sizeof(Polynomial));
	pa->next = NULL;//建立空链表
	printf("%s\n","Pa: ");
	CreatePolyn(&pa,4);//输入创建链表
	PrintAllValues(&pa);

	//创建多项式pb
	Polynomial *pb = (LinkList)malloc(sizeof(Polynomial));
	pb->next = NULL;
	printf("%s\n","pb: ");
	CreatePolyn(&pb,3);
	PrintAllValues(&pb);

	//多项式相加
	AddPolyn(&pa,&pb);
	printf("%s\n","pa + pb: ");
	PrintAllValues(&pa);

	return 0;
}
