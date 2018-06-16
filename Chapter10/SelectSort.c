//算法10.9 对顺序表L作简单选择排序
void SelectSort(SqList &L)
{
	int i,j;
	for(i = 1;i<L.length;i++)//选择第i小的记录，并交换到位
	{
		j = SelectMinKey(L,i);//在L.r[i..L.length]中选择key最小的记录
		if(i!=j){
			swap(L.elem[i],L.elem[j]);//与第i个记录交换
		}
	}
}
//选择L.r[i...L.length]中key最小的记录，返回其位置——时间复杂度为o(n^2)
int SelectMinKey(SqList L,int i)
{
	int pos,k,min;
	min = L.elem[i];
	pos = i;
	for(k = i+1;k<=L.length;k++)
	{
		if(min > L.elem[k]){
			min = L.elem[k];
			pos = k;
		}
	}
	return pos;
}
//算法10.10 已知H.r[s...m]中记录的关键字除H.r[s].key之外均满足堆的定义
//本函数调整H.r[s]的关键字，使H.r[s...m]成为一个大顶堆
//筛选的实现
typedef SqList HeapType;//对采用顺序表存储表示
void HeapAdjust(HeapType &H,int s,int m)
{
	int rc,j;
	rc = H.elem[s];
	for(j = 2*s;j<=m;j = j*2)//沿key较大的孩子结点向下筛选
	{
		if(j<m && H.elem[j]<H.elem[j+1]){//j为key较大的记录的下标
			++j;
		}
		if(rc >= H.elem[j]){//rc应该插在位置s上
			break;
		}
		H.elem[s] = H.elem[j];
		s = j;
	}
	H.elem[s] = rc;//插入
}
//算法10.11——堆排序的实现——o(nlogn)
void HeapSort(HeapType &H)
{
	int i;
	for(i = H.length/2;i>0;i--)//从中间元素开始对前半部分元素筛选,构成大顶堆
	{
		HeapAdjust(H,i,H.length);
	}
	for(i = H.length;i>1;i--)
	{
		swap(H.elem[1],H.elem[i]);//将堆顶记录和当前未经排序子序列Hr[1...i]中最后一个记录相互交换
		HeapAdjust(H,1,i-1);//将H.r[1...i-1]重新调整为大顶堆
	}
}