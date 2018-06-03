//线性顺序表(线性表)的构造和基本操作
#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

//初始化空线性表——算法2.3
Status InitList_Sq(Sqlist &L)
{
	L.elem = (ElemType *)malloc(LIST_INT_SIZE * sizeof(ElemType));//基址
	if(!L.elem) exit(OVERFLOW);//存储分配失败
	L.length = 0;//空表长度为0
	L.listsize = LIST_INT_SIZE;//初始存储容量
	return OK;

}

//销毁线性表
void DestroyList_Sq(Sqlist &L)
{
	//销毁线性表首先要求线性表存在
	free(L.elem);
	L.elem = NULL;
}
//线性表置为空表
void ClearList_Sq(Sqlist &L)
{
	//要求线性表存在
	L.length = 0;
}
//判断线性表是否为空表
Status ListEmpty_Sq(Sqlist L)
{
	if(L.length == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//返回线性表长度,即元素个数
Status ListLength_Sq(Sqlist L)
{
	return L.length;
}
//返回第i个元素的值
void GetElem_Sq(Sqlist L,int i,ElemType &e)
{
	//要求1<=i<=ListLength_Sq(L)
	e = *(L.elem + i - 1);
}
//判断两个数据元素是否相等
Status compare_equal_Sq(ElemType e1,ElemType e2)
{
	if(e1 == e2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//返回第一个满足compare()判断关系的函数的元素的序号
Status LocateElem_Sq(Sqlist L,ElemType e,Status(*compare)(ElemType,ElemType))
{
	ElemType *p = L.elem;
	int i;//遍历位序
	for(i = 1;i<=L.length;i++)//线性表位序从1开始！！
	{
		if(compare(e,*(p+i-1)))
		{
			return i;
		}
	}
	return 0;//未找到
}
Status PriorElem_Sq(Sqlist L,ElemType cur_e,ElemType &pre_e)
{
	//若cur_e是L的数据元素，且不是第一个，用pre_e返回它的前驱
	int pos;
	pos = LocateElem_Sq(L,cur_e,compare_equal_Sq);//返回序号
	if(!pos || 1 == pos)
		return NOTEXIT;
	else
		return *(L.elem+pos-2);

}
//返回符合要求的后驱
Status NextElem_Sq(Sqlist L,ElemType cur_e,ElemType &next_e)
{
	int pos;
	pos = LocateElem_Sq(L,cur_e,compare_equal_Sq);
	if(!pos || L.length == pos)
		return NOTEXIT;
	else
		return *(L.elem+pos);//-1+1
}
//指定位置插入元素
void ListInsert_Sq(Sqlist &L,int i,ElemType e)
{
	ElemType *newbase;
	int q;
	//1<=i<=ListLength_Sq(L)+1
	if(i<1 || i>L.length + 1) return ERROR;//i值不合法
	if(L.length >= L.listsize)//当前存储空间已满，增加分配
	{
		newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));//realloc对大小进行调整
		if(!newbase) exit(OVERFLOW);//存储分配失败
		L.elem = newbase;//新基址
		L.listsize += LISTINCREMENT;//增加存储容量
	}
	q = &(L.elem[i-1]);//q为插入位置;数组
	for(p = &(L.elem[L.length-1]);p>=q;--p)//插入位置之后的元素后移
		*(p+1) = *(p);
	*q = e;//插入e
	++L.length;//表长+1
	return OK;
}
//删除第i个元素，用e返回值，L的长度减1
void ListDelete_Sq(Sqlist &L,int i,ElemType &e)
{
	if((i<1) || (i>L.length)) return ERROR;//i不合理
	int p = &(L.elem[i-1]);//被删除元素的位置
	e = *p;//被删除元素赋值给e
	int q = L.elem+L.length -1;//q为表尾元素的位置
	for(++p;p<q;++p) *(p-1) = *p;//后面的元素前移
	--L.length;//长度--
	return OK;
}
//遍历
Status ListTraverse_Sq(Sqlist L,Status (*visit)(ElemType))
{
	int i;
	for(i = 0;i<L.length;i++)
	{
		if(!visit(*(L.elem+i)))//visit
			return FALSE;
	}
	return TRUE;
}
//显示
Status visit_display_Sq(ElemType e)
{
	printf("%d", e);
	return TRUE;
}
//算法2.1
//将Lb中存在La中不存在的元素插入La中
void unionList_Sq(Sqlist &La,Sqlist Lb)
{
	int La_len = ListLength_Sq(La);
	int Lb_len = ListLength_Sq(Lb);
	int i;
	ElemType e;
	for(i = 1;i<Lb_len;i++)
	{
		GetElem_Sq(Lb,i,e);//取Lb中的第i个元素赋值给e
		if(!LocateElem_Sq(La,e,compare_equal_Sq))
		{
			ListInsert_Sq(La,++La_len,e);//插入到La的后面
		}
	}
}
//时间复杂度为o(ListLength(La)xListLength(Lb))

//算法2.2
void MergeList_Sq(Sqlist La,Sqlist Lb,Sqlist &Lc)
{
	//La和Lb非递减排列
	//归并La和Lb，让Lc也非递减排列
	InitList_Sq(c);
	int i = j = 1;
	int ai,bj;
	int k = 0;
	int La_len = ListLength_Sq(La);
	int Lb_len = ListLength_Sq(Lb);
	while((i<=La_len) && (j<=Lb_len))//La和Lb均为非空
	{
		GetElem_Sq(La,i,ai);//获取第i序列的元素值
		GetElem_Sq(Lb,j,bj);
		if(ai<=bj)
		{
			ListInsert_Sq(Lc,++k,bj);
			++i;
		}
		else
		{
			ListInsert_Sq(Lc,++k,ai);
			++j;
		}
	}
	while(i<=La_len)
	{
		GetElem_Sq(La,i,ai);
		ListInsert_Sq(Lc,++k,ai);
	}
	while(j<=Lb_len)
	{
		GetElem_Sq(Lb,j,bj);
		ListInsert_Sq(Lc,++k,bj);
	}
}
//时间复杂度为o(ListLength(La) + ListLength(Lb))
