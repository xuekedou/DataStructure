#include <stdio.h>
#include <stdlib.h>

#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1
#define  OVERFLOW   -2
#define  Link 0
#define  Thread 1

typedef int TElemType;
typedef int Status;


typedef enum PointerTag {Link,Thread};//Link == 0:指针；Thread == 1:线索
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode,*BiThrTree;

//按先序顺序构造二叉树
Status CreateBiThrTree(BiThrTree *T)
{
	char ch;
	ch = getchar();
	if(ch == '')
		T = NULL;
	else{
		T = (BiThrNode *)malloc(sizeof(BiThrNode));//构造根结点
		if(!T)
			return ERROR;
		T->data = ch;
		T->LTag = Link;//初始化为有孩子结点
		T->RTag = Link;
		CreateBiThrTree(T->lchild);//递归构造左子树
		CreateBiThrTree(T->rchild);//递归构造右子树
	}
	return OK;
}
//算法6.6 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
Status InorderThreading(BiThrTree *Thrt,BiThrTree T)
{
	BiThrTree pre;
	if(!(Thrt = (BiThrNode *)malloc(sizeof(BiThrTree))))//构建头结点
		return ERROR;
	Thrt->LTag = Link;//指针指向根节点
	Thrt->RTag = Thread;//线索到最后遍历到的结点
	Thrt->rchild = Thrt;//右指针回指
	if(!T){
		Thrt->lchild = Thrt;//如果二叉树为空，左指针回指
	}
	else{
		Thrt->lchild = T;pre = Thrt;//pre记录前一个访问的结点
		InThreading(T);//中序遍历进行中序线索化
		pre->rchild = Thrt;pre->RTag = Thread;//最后一个结点的线索化,最后一个结点的右链指向头结点
		Thrt->rchild = pre;//头结点的右链指向最后一个遍历的结点
	}
	return OK;
}
//递归算法中序创建线索二叉树
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);//左子树线索化
		if(!p->lchild)//左链为空时，前继线索；此时递归到最左边的结点
		{
			p->LTag = Thread;
			p->lchild = pre;//pre为中序遍历访问的第一个结点
		}
		if(!pre->rchild)//前一个结点的右链为空时，后继线索
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;//保持pre指向p的前驱
		InThreading(p->rchild);//右子树线索化 
	}
}


//算法6.5 T指向头结点，头结点的左链lchild指向根结点(指针)，右链指向遍历的最后一个结点(线索)
//中序遍历线索二叉树的非递归算法
Status InOrderTraverse_Thr(BiThrTree T,Status(*visit)(TElemType e))
{
	BiThrTree p;//记录型指针
	p = T->lchild;//p指向根结点
	while(p!=T){//空数或者比那里
		while(Link == p->LTag)
			p = p->lchild;//走到左子树的尽头
		if(visit(p->data) == ERROR)
			return ERROR;
		while(p->RTag == Thread && p->rchild != T)//右链为线索，指向后继结点，当p为最后一个结点时，p->rchild == T（头结点）
		{
			p = p->rchild;
			if(visit(p->data) == ERROR)//访问后继结点
				return ERROR;
		}
		p = p->rchild;//右链不是线索，将p指向其右子树
	}
	return OK;
}