#include <stdio.h>
#include <stdbool.h>//C99
#define arrsize 40
#define MAXINT 65535

int main()
{
	int n,i,j;
	int a[arrsize];
	int tmp = 1;
	bool flag = true;//handle the overflow
	printf("please input n: ");
	scanf("%d",&n);
	if(n > arrsize)
	{
		flag = false;
	}
	for(i = 0;i<n && flag;i++)
	{
		tmp = 1;
		for(j=i;j>0 && flag;j--)//calculate a[i]
		{
			if(tmp>MAXINT/(2*j))//(tmp *= 2*j) > MAXINT is useless
			{
				flag = false;
			}
			tmp *= 2*j;
		}
		if(i == 0)
		{
			a[i] = 1;
		}
		else
		{
			a[i] = tmp;
		}
	}
	for (i = 0; i < n && flag; ++i)
	{
		printf("%d\t", a[i]);
	}
	if(!flag)
	{
		printf("Input wrong");
	}
	printf("\n");
}