//算法10.6（a），交换顺序表L中字表L.r[low...high]的记录，使枢轴记录到位
//并返回其所在位置，此时在它之前（之后）的记录不大（小）于它
int Partition_a(SqList &L,int low,int high)
{
	int pivotkey;
	pivotkey = L.elem[low];//第一个记录作为枢轴记录
	while(low<high)//从表的两端交替地向中间扫描
	{
		while(low<high && L.elem[high]>=pivotkey){
			--high;
		}
		swap(L.elem[low],L.elem[high]);//将比枢轴记录小的记录交换到底端
		while(low<high && L.elem[low]<=pivotkey){
			++low;
		}
		swap(L.elem[low],L.elem[high]);//将比枢轴记录大的交换到高端
	}
	return low;//返回枢轴所在位置
}
//算法10.7（b），对算法10.7（a）的改进算法，减少了交换的步骤
int Partition(SqList &L,int low,int high)
{
	int pivotkey;
	L.elem[0] = L.elem[low];//用子表的第一个记录作枢轴记录
	pivotkey = L.elem[low];//枢轴记录关键字
	while(low<high)//从表的两端交替向中间扫描
	{
		while(low<high && L.elem[high] >= pivotkey)
		{
			--high;
		}
		L.elem[low] = L.elem[high];//将比枢轴记录小的记录移到低端
		while(low<high && L.elem[low] <= pivotkey)
		{
			++low;
		}
		L.elem[high] = L.elem[low];//将比枢轴记录大的记录移到高端
	}
	L.elem[low] = L.elem[0];//枢轴记录到位
	return low;//返回枢轴位置
}
//算法10.7 递归法对顺序表L中的子序列L.r[low...high]作快速排序
void QSort(SqList &L,int low,int high)
{
	int pivotloc;
	if(low<high){
		pivotloc = Partition(L,low,high);//找到第一个枢轴分成两部分
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);//分别对枢轴前后两部分用快速排序
	}
}
//算法10.8 快速排序
void QuickSort(SqList &L)
{
	QSort(L,1,L.length);
}