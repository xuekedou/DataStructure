//算法10.12 将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
void Merge(int SR[],int TR[],int i,int m,int n)
{
	int j,k;
	for(j = m+1,k = i;i<=m && j<=n;k++)
	{
		if(SR[i]<=SR[j])
		{
			TR[k] = SR[i];
			i++;
		}else{
			TR[k] = SR[j];
			j++;
		}
	}
	if(i<=m)
	{
		for(j = i;j<=m;j++)
		{
			TR[k] = SR[j];
			k++;
		}
	}
	if(j<=n){
		for(i = j;i<=n;i++)
		{
			TR[k] = SR[i];
			k++;
		}
	}
}
//算法10.13 将SR[s...t]归并排序为TR1[s...t]
void MSort(int SR[],int TR1[],int s,int t)
{
	int m;
	int TR2[100];
	if(s == t)
	{
		TR1[s] = SR[s];
	}
	else
	{
		m = (s + t)/2;//将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		MSort(SR,TR2,s,m);//递归地将SR[s..m]归并为有序的TR2[s..m]
		MSort(SR,TR2,m+1,t);//递归地将SR[m+1..t]归并为有序的TR2[m+1,t]
		Merge(TR2,TR1,s,m,t);//将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
	}
}
//算法10.14 归并排序算法实现——o(nlogn),辅助空间为和待排记录等数量
void MergeSort(SqList &L)
{
	MSort(L.elem,L.elem,1,L.length);
}