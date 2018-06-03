//page 15——the multiple of two matrix
#include <stdio.h>

int main(void)
{
	int T[10][10],Y[10][10],res[10][10],l,c,i,j;
	printf("\n enter the number of lines and column = ");
	scanf("%d",&l);
	printf("\nenter the number of matrix of T \n");
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < l; ++j)
		{
			printf("T[%d][%d] = ", i,j);
			scanf("%d",&T[i][j]);
		}
	}
	printf("\nenter the number of matrix of Y \n");
	for (int i = 0; i < l; ++i)
	{
		for (int j = 0; j < l; ++j)
		{
			printf("Y[%d][%d] = ", i,j);
			scanf("%d",&Y[i][j]);
		}
	}
	printf("\nThe result of matrix is below \n");
	//the main code in page 15
	//o(n^3)
	for (int i = 0; i < l; ++i)
	{
		printf("\n");
		for (int j = 0; j < l; ++j)
		{
			res[i][j] = 0;
			for (int k = 0; k < l; ++k)
			{
				res[i][j] += T[i][k] * Y[k][j];
			}
			printf("\t %d", res[i][j]);//\t表示输入一个tab
			
		}
	}
	return 0;
	
}