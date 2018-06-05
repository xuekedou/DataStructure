//算法3.21 正常表达式转换为逆波兰表达式，即后缀表达式
//算法思想：
//1.用两个栈，一个栈存储临时运算符S1，一个栈存储逆波兰表达式S2
//2.遇到数字，直接存储到S2；遇到符号，判断是(、+-*/、)三类的一种
//3.如果是第一种，直接压入S1，如果是第三种，直接弹出S1中的符号至遇到'(',如果是第二种，比较与S1栈顶元素的关系，如果是大于，直接压入，如果是小于，持续弹出至大于的情况
void RPN(SqStack &S1,SqStack &S2)
{
	char c;//用户输入
	int tmp;
	InitStack(S1);//存储临时运算符,从栈底向上，优先级依次递增
	InitStack(S2);//存储逆波兰式
	Push(S1,'#');
	c = getchar()
	while(c != '#' || !StackEmpty(S1))
	{
		if(!In(c))//不是运算符，是操作数
		{
			Push(S2,c);
			c = getchar();//读入下一个字符
		}else {
			if(c=='('){
				Push(S1,c);
				c = getchar();
			}else if(c == ')'){
				while(GetTop(S1)!='('){//依次弹出S1中的元素
					Pop(S1,tmp);
					Push(S2,tmp);
				}
				if(GetTop(S1) == '('){//弹出'(',逆波兰式中没有'('
					Pop(S1,tmp);
				}
				c.getchar();//读入下一个字符
			}else{//加减乘除的情况
				switch (Precede(GetTop(S1),c)){
					case '<':
						Push(S1,c);
						c = getchar();
						break;
					case '>':
						while(Precede(GetTop(S1),c) == '>'){//依次弹出至现在遍历的符号优先级大于栈顶元素的符号（符号栈中从栈底向上，优先级依次增加）
							Pop(S1,tmp);
							Push(S2,tmp);
						}
						Push(S1,c);
						c = getchr();
						break;
				}
			}
		}
		if(c == '#'){
			while(GetTop(S1)!='#'){
				Pop(S1,tmp);
				Push(S2,tmp);
			}
			Pop(S1,tmp);//把栈底的'#'弹出
		}
	}

}
