#include <stdlib.h>
#include <stdlib.h>

int chess[8][8] = {0};//初始化所有都为0
int count = 0;//解的个数
/*
算法6.16，八皇后问题求解
进入本函数前，在N*N的棋盘上前i-1行已经放置了互不攻击的i-1个棋子
现从第i行起继续为后面的棋子选择合适的位置
当i>n,输出当前布局
*/
void trial(int i,int n)//i表示第i行
{
	int j;//j表示列数
	if(i>n)//找寻成功，输出棋盘的当前布局
		display_chess(n);
	else
	{
		for(j = 1;j<=n;j++)
		{
			put(i,j);//在i行j列摆放一颗棋子
			if(isReasonable(n,i,j))
				trial(i+1,n);//递归遍历
			remove(i,j);//移除i行j列的棋子
		}
	}
}
//在第row行第col列放置皇后是否合法，合法返回true
bool isReasonable(int n,int row,int col)
{
	int i,j,count1,count2,count3;
	count1 = count2 = count3 = 0;
	for(i = 0;i<n;i++)//遍历行
	{
		count3 = 0;
		for(j = 0;j<n;j++)//遍历列
		{
			if(i-j == row-col && 1 = chess[i][j])
				count1++;//斜下对角线的情况
			if(i+j == row + col -2 && chess[i][j] == 1)//输入的row和col是从1开始的
				count2++;//斜上对角线的情况
			if(i+1 == col && chess[i][j] == 1)
				count3++;//同一列的情况；应为是从棋盘上往下放，所以只需检查上面是否放有棋子即可
		}
		if(count3 > 1)
			return false;
	}
	if(count1 > 1 || count2 > 1)//因为是先放置棋子，在检查棋子的放置是否合理
		return false;
}
//移除第i行第j列棋子
void remove(int i,int j)
{
	chess[i-1][j-1] = 0;
}
//第i行第j列放置棋子
void put(int i,int j)
{
	chess[i-1][j-1] = 1;
}

//寻找成功的时候打印当前棋盘
void display_chess(int n)
{
	int i,j;
	count ++;//解的数量加1
	printf("%d.\n", count);
	for(i=0;i<n;i++){
		for(j = 0;j<n;j++)
			printf("%d ", chess[i][j]);
		printf("\n");//每一行换行
	}
	printf("---------------------");
}
