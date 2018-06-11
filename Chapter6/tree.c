#include <stdio.h>
#include <stdlib.h>

#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1
#define  OVERFLOW   -2

typedef int TElemType;//定义二叉树结点的数据元素类型
typedef struct BiTNode{//定义二叉树结点
	TElemType data;
	struct BiTNode *lchild,*rchild;//左右孩子结点
}BiTNode,*BiTree;

typedef BiTree SElemType;
typedef BiTree QElemType;


//按先序构造二叉树
Status CreateBiTree(BiTree *T)
{
	char ch;
	scanf("%c",&ch);//输入的数
	if(ch == ' ')
		T = NULL;//根节点为空
	else
	{
		T = (BiTNode *)malloc(sizeof(BiTNode));//初始化结点
		if(!T)
		{
			return ERROR;
		}
		T->data = ch;
		//递归构造
		CreateBiTree(T->lchild);//构造左子树
		CreateBiTree(T->rchild);//构造右子树
	}
}
//打印一个元素
Status display(TElemType e)
{
	printf("%c",e);
	return OK;
}
//先序遍历二叉树——递归算法
Status PreOrderTraverse(BiTree T,Status (*visit)(TElemType e))
{
	if(T){
		if(visit(T->data) == OK)
			if(PreOrderTraverse(T->lchild,visit) == OK)
				if(PreOrderTraverse(T->rchild,visit) == OK)
					return OK;//遍历结束
		return ERROR;
	}else
		return OK;//成功遍历
}
//中序遍历二叉树
Status InOrderTraverse(BiTree T,Status (*visit)(TElemType e))
{
	if(T){
		if(InOrderTraverse(T->lchild,visit) == OK)
			if (visit(T->data) == OK)
				if(InOrderTraverse(T->rchild,visit) == OK)
					return OK;
		return ERROR;
	}else
		return OK;
}
//后序遍历二叉树
Status PostOrderTraverse(BiTree T,Status (*visit)(TElemType e))
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,visit) == OK)
			if(PostOrderTraverse(T->rchild,visit) == OK)
				if(visit(T->data) == OK)
					return OK;
		return ERROR;
	}else
		return OK;
}
//层序遍历二叉树
Status LevelOrderTraverse(BiTree T,Status (*visit)(TElemType e))
{
	BiTree p;//头指针
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	while(p || !QueueEmpty(Q))
	{
		if(p){
			visit(p->data);
			if(p->lchild)
				EnQueue(Q,p->lchild);
			if(p->rchild)
				EnQueue(Q,p->rchild);
			if(!QueueEmpty(Q))
				DeQueue(Q,p);//p为队列的第一个结点
			else			//队列为空时，退出循环
				break;
		}
	}
	return OK;
}
//非递归算法实现先序遍历
Status PreOrderTraverse2(BiTree T,Status (*visit)(TElemType e))
{
	SqStack S;//递归算法迭代化用栈
	BiTree p;
	InitStack(S);
	p = T;
	while(p || !StackEmpty(S))
	{
		if(p)
		{
			if(visit(p->data) == ERROR)//先遍历根节点
				return ERROR;
			Push(S,p);
			p = p->lchild;
		}
		else
		{
			Pop(S,p);//当前子树的根节点，已经访问过了
			p = p->rchild;//把右孩子看成右子树
		}
	}
}
//非递归算法中序遍历
Status InOrderTraverse2(BiTree T,Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;//根结点
	while(p || !StackEmpty(S))
	{
		if(p){
			Push(S,p);
			p = p->lchild;
		}else//遍历到当前子树的最左节点
		{
			Pop(S,p);
			if(visit(p->data) == ERROR)
				return ERROR;
			p = p->rchild;
		}//if-end
	}//while-end
	return OK;
}
//非递归算法中序遍历2
Status InOrderTraverse3(BiTree T,Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S,T);
	while(!StackEmpty(S))
	{
		while(GetTop(S,p) && p) Push(S,p->lchild);//走到左边的尽头
		Pop(S,p);//空指针退栈
		if(!StackEmpty(S))//访问结点，向右子树遍历
		{
			Pop(S,p);
			if(!visit(p->data)) return ERROR;
			Push(S,p->rchild);
		}//if-end
	}//while-end
	return OK;
}
//非递归算法实现后续遍历
Status PostOrderTraverse2(BiTree T,Status (*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];//标志栈
	int t = 1;
	p = T;
	while(p || !StackEmpty(S))
	{
		while(p)
		{
			Push(S,p);
			p = p->lchild;
			Tag[t++] = 0;
		}
		while(!StackEmpty(S) && Tag[t-1] == 1)//先判断是否遍历完右子树
		{
			Pop(S,p);
			t--;
			if(visit(p->data) == ERROR)
				return ERROR;
		}
		if(!StackEmpty(S))//开始遍历右子树
		{
			Tag[t-1] = 1;
			GetTop(S,p);
			p = p->rchild;
		}else
			break;//遍历完成
	}
	return OK;
}
//树的遍历的时间复杂度为o(n)
//所用的辅助空间为遍历过程中栈的最大容量，即数的深度!最坏情况为n,所以空间复杂度也为o(n);


