#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	int n,i,x;
	int total = 0;
	int tmp = 1;
	printf("please input the number of x: ");
	scanf("%d",&x);
	printf("please input the n: ");
	scanf("%d",&n);
	int a[n];
	printf("please input the elements: \n");
	for (i = 0; i < n; ++i)
	{
		printf("a[%d] :", i);
		scanf("%d",&a[i]);
		// total += a[i]*pow(x,i);//using the pow(a,b)
		total += a[i]*tmp;
		tmp = tmp*x;//not using the pow(a,b)
	}
	printf("the result is: %d",total);
	return 0;
}