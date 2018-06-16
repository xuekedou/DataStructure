//结构定义
#define MAX_NUM_OF_KEY 8//关键字项数的最大值
#define RADIX 10//关键字基数
#define MAX_SPACE 1000

typedef struct {
	KeysType keys[MAX_NUM_OF_KEY];//关键字
	int next;
}SLCell;//静态链表的结点类型

typedef struct{
	SLCell r[MAX_SPACE];//静态链表的可利用空间，r[0]为头结点
	int keynum;//记录的当前关键字个数
	int recnum;//静态链表的当前长度
}SLList;//静态链表类型
typedef int ArrType[RADIX];//指针数组类型

//算法10.15 分配算法，静态链表L的r域中记录已按(key[0]...key[i-1])有序，
//本算法按第i个关键字简历RADIX个字表，使同一子表中记录的key[i]相同
//f[0....RADIX-1]和e[0....RADIX-1]分别指向各子表中第一个记录和最后一个记录
void Distribute(SLCell r[],int i,ArrType &e)
{
	int j,p;
	fo(j = 0;j<RADIX;j++){//初始化f[]
		f[j] = 0;
	}
	for(p = r[0].next;p!=0;p = r[p].next)
	{
		j = ord(r[p].keys[i]);
		if(!f[i]){
			f[j] = p;
		}else{
			r[e[j]].next = p;
		}
		e[j] = p;
	}
}
//将关键字K映射到[0...RADIX-1]
int ord(KeysType K)
{
	return K;
}
//算法10.16 搜集算法
void Collect(SLCell r[],int i,ArrType f,ArrType e)
{
	int j,t;
	for(j = 0;f[j]!=0;j = succ(f,j)){
		;
	}
	r[0].next = f[j];
	t = e[j];
	while(j<RADIX)
	{
		for(j = succ(f,j);j<RADIX-1&&!f[i];j = succ(f,j))
		{
			;
		}
		if(f[j])
		{
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}
//求f[j]后的第一个非空表
int succ(ArrType f,int j)
{
	int i;
	for(i = j+1;f[i]!=0;i++)
	{
		;
	}
	return i;
}
//算法10.17 基数排序
void RadixSort(SLList &L)
{
	int i;
	ArrType f,e;
	for(i = 0;i<L.recnum;++i)
	{
		L.r[i].next = i+1;
	}
	L.r[L.recnum].next = 0;
	for(i = 0;i<L.keynum;i++)
	{
		Distribute(L.r,i,f,e);
		Collect(L.r,i,f,e);
	}
}