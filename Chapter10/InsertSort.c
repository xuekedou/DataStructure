//静态链表
#define SIZE 100
typedef struct{//表结点类型
	int key;
	int next;
}SLNode;
typedef struct{//静态链表
	SLNode r[SIZE];//0号单元为表头结点
	int length;//链表当前长度
}SLinkList;

//从文件filename中读入数据创建顺序表L，0号单元不用
Status CreateSqList(SqList &L,char *filename)
{
	InitList_Sq(L);
	FILE *pf;
	ElemType e;

	pf = fopen(filename,"r");
	if(pf == NULL)
	{
		printf("打开文件%s失败\n",filename);
		return ERROR;
	}
	while (fscanf(pf,"%d",&e) != EOF)
	{
		ListInsert_Sq(L,2,e);
	}
	fclose(pf);
	return OK;
}
//算法10.1 对顺序表做插入排序
void InsertSort(SqList &L)
{
	int i,j;
	for(i=2;i<=L.length;i++)
	{
		if(L.elem[i]<L.elem[i-1])
		{
			L.elem[0] = L.elem[i];//哨兵结点记录
			L.elem[i] = L.elem[i-1];//倒数第二个元素后移
			for(j = i-2;L.elem[0]<L.elem[j];j--)
			{
				L.ele[j+1] = L.elem[j];//从倒数第三个元素开始后移
			}
			L.elem[j+1] = L.elem[0];//L.elem[j]是小于L.elem[0]，L.elem[0]插到j后面
		}
	}
}
//算法10.2 折半插入排序——减少比较的次数，不减少插入移动元素的次数o(n^2)
void BInsertSort(SqList &L)
{
	int i,j,low,high,mid;
	for(i = 2;i<=L.length;i++)
	{
		L.elem[0] = L.elem[i];//哨兵值
		high = i-1;//i插入到[1...i-1]中
		low = 1;
		while(high >= low)//折半查询插入位置，应为low的位置
		{
			mid = (high+low)/2;
			if(L.elem[0] < L.elem[mid])
			{
				high = mid-1;
			}else
			{
				low = mid+1;
			}
		}//找到low的位置
		for(j=i-1;j>=low;j--)//记录后移
		{
			L.elem[j+1] = L.elem[j];
		}
		L.elem[low] = L.elem[0];
	}
}

//2-路插入排序算法——减少移动记录的次数
void TwoInsertSort(SqList &L)
{
	ElemType *d;
	int first,final,i,j;
	d = (ElemType *)malloc((L.length+1)*sizeof(ElemType));//添加了一个哨兵元素
	first = 0;
	final = 0;
	if(L.length > 0){
		d[1] = L.elem[1];//L中的第一个元素做d的中间位置
		first = 0;
		final = 1;//final是前半部分数组
	}
	//直接插入
	for(i=2;i<=L.length;i++){
		if(L.elem[i]>d[1]){//插入到后半部分
			for(j = final;L.elem[i]<d[j];j--){
				d[j+1] = d[j];//记录后移
			}
			++final;
			d[j+1] = L.elem[i];//插入
		}else{//插入到前半部分,但是在数组后半段表示
			if(first == 0)
			{
				first = L.length;//放到数组的最后面
				d[L.lenght] = L.elem[i];
			}else{
				for(j = first;(j<=L.length)&&(L.elem[i]>d[j]);j++)//第一次是碰到自己和自己比较
				{
					d[j-1] = d[j];//记录后移
				}
				--first;
				d[j-1] = L.elem[i];
			}
		}
	}
	//重新组织数组中的元素
	if(first == 0)
	{
		for(i = 1;i<=L.length;i++)
		{
			L.elem[i] = d[i];
		}
	}else{
		for(i = first,j=1;i<=L.length;i++,j++)
		{
			L.elem[j] = d[i];
		}//先遍历输入较小的一部分
		for(i = 1;i<=final;i++,j++)
		{
			L.elem[j] = d[i];
		}//再遍历输入较大的一部分
	}
}
//静态链表的插入排序
void TableInsertSort(SLinkList &S)
{
	int i,j,p;
	S.r[0].key = INTMAX;//链表的第一个结点作为头结点
	if(S.length > 0)
	{
		S.r[1].next = 0;
		S.r[0].next = 1;//构成循环链表
	}
	for(i = 2;i<=S.length;i++)
	{
		p = 0;
		for(j = S.r[0].next;S.r[i].key>S.r[j].key && j>0;p=j,j=S.r[j].next)//寻找插入的位置
		{
			;
		}//j从序号1开始遍历已经排好序的元素，p是j前面的一个元素
		S.r[i].next = j;//i是当前待插入的元素
		S.r[p].next = i;//p是j之前的元素，便于插入
	}
}
//算法10.3 根据静态链表SL中各结点的指针调整记录的位置，使得SL中记录按关键字非递减有序顺序排列
void Arrang(SLinkList &SL)
{
	int p,q,i,temp;
	p = SL.r[0].next;//指向链表中的第一个记录
	for(i = 1;i<=SL.length;i++)
	{
		if(p!=i)
		{
			swap(SL.r[i].key,SL.r[p].key);//先交换key的值
			q = SL.r[p].next;//记录关键字排序为下一个的位置
			SL.r[p].next = SL.r[i].next;//再换指针
			SL.r[i].next = p;
			p = q;
		}
	}
}
//交换两个数
void swap(int &i,int &j)
{
	int tmp;
	tmp = i;
	i = j;
	j = tmp;
}
//算法10.4
//1.前后记录位置的增量是dk而不是1
//2.r[0]只是暂存单元，不是哨兵。当j<=0,插入位置已经找到
void ShellInsert(SqList &L,int dk)
{
	int i,j;
	for(i = dk+1;i<=L.length;i++)
	{
		if(L.elem[i]<L.elem[i-dk])//需将L.elem[i]插入有序增量字表
		{
			L.elem[0] = L.elem[i];//暂存在L.elem[0]
			for(j = i-dk;j>0&&L.elem[0]<L.elem[j];j = j-dk)
			{
				L.elem[j+dk] = L.elem[j];//记录后移，查找插入位置
			}
			L.elem[j+dk] = L.elem[0];//插入
		}
	}
}
//算法10.5 希尔排序，按增量序列dlta[0...t-1]对顺序表L作希尔排序，且dlta[t-1]必须为1
//希尔排序利用插入排序的两个特性：1.对已经排好序的只要o(n) 2.对数据量小的排序效率比较高
void ShellSort(SqList &L,int dlta[],int t)
{
	int k;
	for(k = 0;k<t;k++)//dlta[]增量序列需要自定义输入
	{
		ShellInsert(L,dlta[k]);//一趟增量为dlta[k]的插入排序
	}
}