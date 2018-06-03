#include <stdio.h>

void sort(int i,int j,int k);

int main(int argc, char const *argv[])
{
	int i=3,j=7,k=1;
	printf("三个数字范例是：%d %d %d\n",i,j,k);
	printf("这三个数从大到小顺序为：");
	sort(i,j,k);
	// printf("\n");
	return 0;
}

void sort(int i,int j,int k)
{
	int tmp;
	if(i<j)
	{
		tmp = i;
		i = j;
		j = tmp;
	}
	/* solution 1
	if(j<k)
	{
		tmp = j;
		j = k;
		k = tmp;
	}
	if(i<j)
	{
		tmp = i;
		i = j;
		j = tmp;
	}
	*/
	//solution 2——reduce the times of swip
	if(j<k)
	{
		tmp = k;
		k = j;
		if(i>=tmp) j = tmp;
		else {j = i;i = tmp;}//i is the first position
	}
	printf("%d %d %d\n",i,j,k);
}