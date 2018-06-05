#include <stdio.h>
#include <stdlib.h>

#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1
#define  OVERFLOW   -2
#define  STACK_INIT_SIZE  100//初始大小
#define  STACKINCREMENT    10//增加的大小

typedef int ElemType;
typedef int Status;

//栈的结构
typedef struct
{
	ElemType *base;
	ElemType *top;
	int stacksize;//SqStack预设的存储空间
}SqStack;

//构造一个空的链表
Status InitStack(SqStack *S)
{
	//初始化三个属性top,base,stacksize
	(*S).base = (ElemType *)malloc(STACK_INIT_SIZE*sizeof(ElemType));//初始化栈的size
	if(!(*S).base)//没有分配内存的空间
	{
		exit(OVERFLOW);
	}
	(*S).top = (*S).base;//top=base表示栈为空
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}
//销毁栈
Status DestroyStack(SqStack *S)
{
	//置空三个属性：top是指针，base所指结点
	(*S).top = NULL;//top指针为空
	(*S).stacksize = 0;//空间置空
	free((*S).base);//free最下面的结点
	return OK;
}
//清空栈——空栈
Status ClearStack(SqStack *S)
{
	(*S).top = (*S).base;
	return OK;
}
//判断是否为空栈
Status StackEmpty(SqStack S)
{
	if(S.top == S.base)
		return ERROR;
	else
		return TRUE;
}
//求栈的长度
Status StackLength(SqStack S)
{
	if(S.top == S.base)
		return ERROR;
	else
		return (S.top-S.base);
}
//求栈顶元素
Status GetTop(SqStack S,ElemType *e)
{
	if(S.base == NULL || S.top == S.base)
	{
		return ERROR;
	}
	else
	{
		(*e) = *(S.top - 1);//S.top在栈顶元素之上
		return (*e);
	}
}
//栈顶插入元素——检验空间是否足够
Status Push(SqStack *S,ElemType *e)
{
	if((*S).top - (*S).base >= STACK_INIT_SIZE)//超出初始化空间
	{
		//通过S.base重新分配空间，类似于线性表通过“SqList.elem”重新分配空间
		//重新分配空间之后S.base可能改变，SqList.elem可能会改变
		(*S).base = (ElemType *)realloc((*S).base,((*S).stacksize + STACKINCREMENT) * sizeof(ElemType));
		if(!(*S).base)
		{
			return FALSE;
		}
		//重新定义其他两个属性
		(*S).top = (*S).base + STACK_INIT_SIZE;//栈底地址可能改变
		(*S).stacksize = (*S).stacksize + STACKINCREMENT;
	}
	(*S).top = e;
	(*S).top++;
	return OK;
}
//删除栈顶元素
Status Pop(SqStack *S,ElemType *e)
{
	if((*S).top == (*S).base)
		return FALSE;
	(*S).top--;//top在栈顶元素之上
	e = (*S).top;//注意：实际上元素并没有真正被删除，仍然在栈中，被S.top所指，但是插入元素的时候，就会被更新
	return *e;
}
//遍历栈
Status TraverseStack(SqStack S)
{
	//case1:栈不存在
	if(S.base == NULL)
	{
		return ERROR;
	}
	//case2：空栈
	if(S.top == S.base)
	{
		printf("栈中没有元素\n");
	}
	//case3:符合遍历条件
	ElemType *p = S.top;
	while(p != S.base)
	{
		p--;
		printf("%d\n",*p);
	}
	return OK;
}
//算法3.1——数制转换
/*
void conversion(){
	//对于输入的任何一个非负十进制数，转换成相应的八进制数
	int N;
	ElemType e;
	SqStack S;
	InitStack(&S);
	scanf("%d",&N);//待转换的十进制数
	while(N)
	{
		Push(&S,(N%8));//根据进制转换公式
		N = N/8;
	}
	while(!StackEmpty(S))
	{
		Pop(&S,e);
		printf("%d",e);
	}
}
*/
//算法3.2.2——括号匹配,先遍历的期待迫切度低——栈
Status CheckBracket(char *expr)//输入的是一个char数组
{
	int i = 0;
	SqStack S;
	InitStack(&S);
	ElemType e;
	while(*(expr+i) != '\0')//expr是char数组指向第一个元素的指针
	{
		switch(*(expr)){
			case '(':
				Push(&S,-1);//用数字标记符号
				break;
			case '[':
				Push(&S,-2);
				break;
			case '{':
				Push(&S,-3);
				break;
			case ')':
				if(GetTop(S,e) == OK)
				{
					if(e == -1)
					{
						Pop(S,e);
					}
					else
					{
						return ERROR;
					}
				}else
					return ERROR;
				break;
			case ']':
				if(GetTop(S,e) == OK)
				{
					if(e == -2)
					{
						Pop(S,e);
					}
					else
					{
						return ERROR;
					}
				}
				else 
					return ERROR;
				break;
			case '}':
				if(GetTop(S,e) == OK)
				{
					if(e == -3)
						Pop(S,e);
					else
						return ERROR;
				}
				else
					return ERROR;
				break;
			default:
				break;
		}//switch-end
		i++;//遍历
		if(StackEmpty(S))
			return OK;
		else
			return ERROR;
	}
}
//算法3.2——行编辑器
void LineEdit()
{
	char ch;//用户输入的字符
	int c;
	SqStack S;
	InitStack(S);
	ch = getchar();//用户输入的字符
	while(ch != EOF)//EOF为全文结束符，windows下为ctrl+Z
	{
		while(EOF != ch && '\n' != ch)
		{
			swich(ch){
				case '#':
					Pop(S,c);
					break;
				case '@':
					ClearStack(S);
					break;
				default:
					Push(S,ch);
					break;
			}//switch-end
			ch = getchar()
		}
		//一行输入结束
		TraverseStack(S,display_char);
		printf("\n");
		ClearStack(S);
		if(ch != EOF)//输入了换行符
		{
			ch = getchar();
		}
	}
}
Status display_char(ElemType e)
{
	printf("%c",e);
	return OK;
}
//两个栈实现四则运算
//判断两个符号的优先级
char Precede(char c1,char c2)
{
	switch (c1){
		case '+':
		case '-':
			switch (c2){
				case '+':
				case '-':
				case ')':
				case '#':
					return '>';
					break;
				case '*':
				case '/':
				case '(':
					returen '<';
					break;
				default:
					break;
			}
			break;//break才表示一种情况结束
		case '*':
		case '/':
			switch(c2)
			{
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
				case '#':
					return '>';
					break;
				case '(':
					return '<';
					break;
				default:
					break;
			}
		case '(':
			switch (c2) {
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
					return '<';
					break;
				case ')':
					return '=';
					break;
			default:
				break;
		}
		break;
		case ')':
			switch (c2) {
				case '+':
				case '-':
				case '*':
				case '/':
				case ')':
				case '#':
					return '>';
					break;
				default:
					break;
		}
		break;
		case '#':
			switch (c2) {
				case '+':
				case '-':
				case '*':
				case '/':
				case '(':
					return '<';
					break;
				case '#':
					return '=';
					break;
				default:
					break;
		}
		break;
		default:
			break;
	}

}
//判断字符c是否为操作符，
bool In(char c){}
//运算
int Operate(int a,char theta,int b){}
//算术表达式求值
int EvaluateExpression(){
	SqStack OPTR,OPND;
	InitStack(OPTR);//存储操作数的栈
	Push(OPTR,'#');
	InitStack(OPND);//存储操作数的栈
	int c,x;
	int theta;
	int a,b;
	c = getchar();//用户输入
	while (c!='#' || GetTop(OPTR) != '#')
	{
		if(!In(c)){//c不是操作符
			c = c-'0';//ASCII
			Push(OPND,c);
			c = getchar();
		}
		else//是操作符
		{
			switch(Precede(GetTop(OPTR),c)){//比较操作数的优先级
				case '<'://优先级高，先算，退栈并将运算结果入栈;优先级的后入先出
					Push(OPTR,c);
					c = getchar();
					break;
				case '>'://优先级低
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					Push(OPND,Operate(a,theta,b));
					break;
				case '='://脱括号
					Pop(OPTR,c);
					c = getchar();
					break;
				default :
					break;
			}
		}
	}
}
//算法3.5——汉诺塔
void hanoi(int n,char x,char y,char z)
{
	if(n == 1)
	{
		move(count,x,1,z);
	}
	else{
		hanoi(n-1,x,y,z);//x为起始位置，y为辅助位置，z为终点位置
		move(count,x,n,z);
		hanoi(n-1,y,x,z);
	}
}



//主函数检验
int main()
{
	SqStack S;
	printf("构造一个空栈.....\n");
	InitStack(&S);
	int i,n;
	printf("请输入一个栈的长度：\n");
	scanf("%d",&n);
	for(i = 1;i<=n;i++)
	{
		printf("输入栈的第%d个元素 ：", i);
		S.top++;
		scanf("%d",S.top-1);
	}
	printf("本栈是空栈吗？");
	if(StackEmpty(S) == 1)//1代表TRUE
		printf("NO!!!");
	else
		printf("YES!");
	printf("求出栈的长度");
	int m;
	m = StackLength(S);
	printf("栈的长度是：%d",m);
	//其他操作类似
}


