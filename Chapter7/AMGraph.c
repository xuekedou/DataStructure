#include <stdio.h>
#include <stdlib.h>
#include "AMGraph.h"

//若G中存在顶点u，则返回该顶点在无向图中的位置，否则返回-1
int LocateVex(const MulAdjGraph &G,const VertexType &u)
{
	int i;
	for(i = 0;i<G.ivexNum;++i)//ivexNum为结点数量
		if(u == G.adjmulist[i].data)//adjmulist为头结点数组
			return i;
	return -1;
}
//采用邻接多重链表存储结构，构造无向图G
int CreateGraph(MulAdjGraph &G)
{
	int i,j,OverInfo,IncInfo;
	VertexType first,second;
	printf("输入无向图G的顶点数，边数，边是否含权重信息（1，0）");
	scanf("%d %d %d",&G.ivexNum,&G.iarcNum,&OverInfo);
	G.maxVertexNum = G.ivexNum;
	G.adjmulist = new VertexNode[G.MaxVertexNum];//初始化头结点数组
	printf("请输入%d个顶点的标识号（标识号为int数据类型）:\n",G.ivexNum);
	for(i = 0;i<G.ivexNum;++i)//构造顶点向量
	{
		scanf("%d",&G.adjmulist[i].data);
		G.adjmulist[i].firstarc = NULL;
	}
	printf("请输入由两点构成的边%d条(以空格作为间隔):\n",G.iarcNum);
	for(int k = 0;k<G.iarcNum;++k)//构造表结点链表
	{
		scanf("%d %d%*c",&first,&second);//%*c吃掉回车符
		i = LocateVex(G,first);
		j = LocateVex(G,second);
		if(i == -1 || j == -1) return 0;

		ArcType* pArc = new ArcType;
		pArc->ivex = i;
		pArc->jvex = j;	
		//关键部分！！！
		pArc->ilink = G.adjmulist[i].firstarc;//插在表头之后
		G.adjmulist[i].firstarc = pArc;
		pArc->jlink = G.adjmulist[j].firstarc;
		G.adjmulist[j].firstarc = pArc;
	}
	if(OverInfo)
	{
		printf("该边是否有权重（1，0）:");
		scanf("%d%*c",&IncInfo);
		if(IncInfo);//边有相关信息
		{
			printf("请输入该边的权值：");
			scanf("%f%*c",&pArc->weight);
		}
	}
	return 1;//构造成功
}
//返回v的值
inline VertexType* GetVex(const MulAdjGraph &G,const int &v)
{
	if(v>=G.ivexNum || v<0) exit(0);
	return &G.adjmulist[v].data;
}
//对v赋新值value
int PutVex(MulAdjGraph &G,const VertexType v,const VertexType &value)
{
	int i;
	i = LocateVex(G,v);
	if(i<0)//v不是G的顶点
		return 0;//修改失败
	G.adjmulist[i].data = value;
	return 1;//修改成功
}
//返回v的第一个邻接顶点的序号。若顶点在G中没有领接顶点，则返回-1
int FirstAdjVex(const MulAdjGraph &G,const VertexType &v)
{
	int i;
	i = LocateVex(G,v);
	if(i<0) return -1;
	if(G.adjmulist[i].firstarc)//v有邻接节点
		if(G.adjmulist[i].firstarc->ivex == i)//ivex就等于i；jvex就是弧线另一端的结点
			return G.adjmulist[i].firstarc->jvex;
		else
			return G.adjmulist[i].firstarc->ivex;
	else 
		return -1;
}
//返回v的（相对于w的）下一个邻接顶点的序号。若w是v的最后一个邻接顶点，则返回-1
int NextAdjVex(const MulAdjGraph &G,const VertexType &v,const VertexType &w)
{
	int i,j;
	ArcType *p;
	i = LocateVex(G,v);//i是顶点v的序号
	j = LocateVex(G,w);//j的顶点w的序号
	if(i<0 || j<0)//不是G的节点
		return -1;
	p = G.adjmulist[i].firstarc;//p指向顶点v的第1条边
	while(p)
	{
		if(p->ivex == i && p->jvex!=j)//当前邻接节点不是w(情况一)
			p = p->ilink;//找下一个邻接节点;ilink指下一条依附于ivex的边
		else if (p->jvex == i && p->ivex != j)//当前邻接节点不是w（情况二）
			p = p->jlink;//找下一个邻接节点
		else//邻接节点是w
			break;
		if(p&&p->ivex==i&&p->jvex==j)//找到邻接节点w（情况一）
		{
			p = p->ilink;
			if(p&&p->ivex==i)
				return p->jvex;
			else if(p&&p->jvex==i)
				return p->ivex;
		}
		if(p&&p->ivex==j&&p->jvex==i)//找到邻接节点w（情况二）
		{
			p = p->jlink;
			if(p&&p->ivex==i)
				retrun p->jvex;
			else if(p&&p->jvex==i)
				return p->ivex;
		} 
	}
	return -1;
}
//在G中添加新顶点v（暂时不添加弧线）
int InsertVex(MulAdjGraph &G,const VertexType v)
{
	if(G.ivexNum == G.MaxVertexNum)//结点已满，不能插入
	{
		printf("结点已满，不能插入\n");
		return 0;
	}
	if(LocateVex(G,v)>0)//结点已经存在，不能插入
	{
		printf("结点已经存在，不能插入\n");
		return 0;
	}
	G.adjmulist[G.ivexNum].data = v;//直接在数组中添加
	G.adjmulist[G.ivexNum].firstarc = NULL;//链表的尾结点
	G.ivexNum++;
	return 1;
}
//在G中删除弧<v,w>
//因为每个结点都有两个指针域，加上其他结点指向该结点的两个指针，即一共四个指针
//所以在从i开始遍历的时候，断开其中两个指针；从j开始遍历的时候，断开两个指针并且删除结点
int DeleteArc(MulAdjGraph &G,const VertexType &v,const VertexType &w)
{
	int i,j;
	ArcType *p,*q;

	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i<0 || j<0 ||i == j) return 0;//图中没有该点或者该弧
	//第一遍：从i结点开始遍历寻找弧<v,w>
	p = G.adjmulist[i].firstarc;//p指向顶点v的第一条边（包含顶点v的两种情况是ivex和jvex分别是结点v）
	if(p&&p->jvex==j)//第一条边即为待删除边，i为边前面的结点（情况一）
	{
		G.adjmulist[i].firstarc = p->ilink;//ilink表示已p为结点的下一条边
	}else if(p&&p->ivex==j)//第一条边即为带删除边，i为边后面的结点（情况二）
	G.adjmulist[i].firstarc = p->jlink;
	else//第一条边不是待删除边
	{
		while(p)
		{
			if(p->ivex == i && p->jvex!=j)//不是待删除边
			{
				q = p;
				p = p->ilink;//找下一个邻接点
			}
			else if(p->jvex == i && p->ivex!=j)//不是待删除边
			{
				q = p;
				p = p->jlink;//找下一个邻接点
			}
			else//是邻接顶点w
				break
		}
		if(!p)//没有找到符合要求的边
			return 0;
		if(p->ivex == i&&p->jvex = j)//找到
			if(q->ivex==i)//只要是ivex或者jvex是i，则就在链上，所以每个结点都有两种情况要判断
				q->ilink = p->ilink;
			else
				q->jlink = p->jlink;
		else if(p->ivex==j&&p->jvex==i)//找到
			if(q->ivex==i)
				q->ilink=p->jlink;
			else
				q->jlink = p->jlink;
	}
	//第二遍：从w顶点开始遍历寻找弧线<v,w>
	p = G.adjmulist[j].firstarc;//指向第一条边
	if(p->jvex == i)
	{
		G.adjmulist[j].firstarc = p->ilink;//因为ivex是j，所以连到下一个ilink上
		delete p;
	}else if(p->ivex == i)
	{
		G.adjmulist[j].firstarc = p->jlink;
		delete p;
	}
	else//第一条不是待删除的边
	{
		while(p)
			if(p->ivex==j&&p->jvex!=i)
			{
				q = p;
				p = p->ilink;
			}
			else if(p->jvex==j&&p->ivex!=i)
			{
				q = p;
				p = jlink;
			}
			else
				break;
		if(p->ivex==i&&p->jvex==j)
		{
			if(q->jvex==j)
				q->jlink = p->jlink;
			else
				q->ilink = p->jlink;
			delete p;
		}
		else if(p->ivex==j&&p->jvex==i)
		{
			if(q->jvex==i)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
			delete p;
		}
	}
	--G.iarcNum;//弧数组减一
	return 1;
}
//删除G中顶点v及相关的边
//先删除相关的边——遍历所有头结点，利用DeleteArc函数
//在删除结点——数组后面的数前移，然后数组长度减一，然后修改链中ivex或者jvex的值
int DeleteVex(MulAdjGraph &G,const VertexType &v)
{
	int i,j;
	VertexType w;
	ArcType *p;
	i = LocateVex(G,v);
	if(i<0) return 0;
	for(j=0;j<G.ivexNum;++j)//删除与顶点v相连的边(如果有的话)
	{
		if(j==i)
			continue;
		w=*GetVex(G,j);//w是第j个顶点的值
		DeleteArc(G,v,w);//函数会判断<v,w>弧是否存在
	}
	for(j=i+1;j<G.ivexNum;++j)//排在顶点v后面的顶点的序号减1
		G.adjmulist[j-1] = G.adjmulist[j];//只修改了顶点的序号，没有修改后面链表中结点的序号
	--G.ivexNum;//顶点数减1
	for(j=i;j<G.ivexNum;++j)//修改顶点序号
	{
		p = G.adjmulsit[j].firstarc;
		while(p)
		{
			if(p->ivex == j+1)//左结点域
			{
				p->ivex--;
				p = p->ilink;
			}
			else//右结点域
			{
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	return 1;
}
//销毁图
void DestroyGraph(MulAdjGraph &G)
{
	int i;
	for(i=G.ivexNum-1;i>=0;--i)
	{
		DeleteVex(G,G.adjmulist[i].data);//从后面往前面删除，节约操作时间
	}
	delete [](G.adjmulist);
}
//在G中添加弧<v,w>
//弧以结点的形式存在
int InsertArc(MuladjGraph &G,const VertexType &v,const VertexType &w)
{
	int i,j,IncInfo;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i<0||j<0) return 0;
	ArcType* pArc = new ArcType;//结点指针变量
	pArc->ivex = i;
	pArc->jvex = j;
	pArc->ilink = G.adjmulist[i].firstarc;//头插法
	G.adjmulist[i].firstarc = pArc;
	pArc->jlink = G.adjmulist[j].firstarc;
	G.adjmulist[j].firstarc = parc;
	G.iarcNum++;//弧的数量加一
	return 1;
}
//搜索弧<v,w>是否存在
bool Search(const MulAdjGraph &G,const VertexType &v,const VertexType &w)
{
	int i,j;
	i = LocateVex(G,v);
	j = LocateVex(G,w);
	if(i<0 || j<0) return 0;
	ArcType* p = new Arctype;
	p = G.adjmulist[i].firstarc;
	while(p)
	{
		//先判断符合条件的情况，再判断不符合条件的情况
		if(p->ivex==i&&p->jvex==j)
			return true;
		else if(p->jvex==i&&p->ivex==j)
			return true;
		else if(p->ivex == i)
			p = p->ilink;
		else if(p->jvex == j)
			p = p->jlink;
	}
	return false;
}
//找到顶点v的邻接顶点，函数返回符合条件的个数
int FindNeighbour(const MulAdjGraph &G,const VertexType &v)
{
	int i,num=0;
	ArcType* p;
	i = LocateVex(G,v);//i用来存储待查找结点的位置
	if(i<0) return 0;
	p = G.adjmulist[i].firstarc;
	if(p)
	{
		printf("顶点%d的邻接顶点为：\n",v);
	while(p)
	{
		if(p->ivex == i)
		{
			printf("%4d",G.adjmulist[p->jvex].data);
			num++;
			p = p->ilink;
		}
		else if(p->jvex == i)
		{	
			printf("%4d",G.adjmulist[p->ivex].data);
			num++;
			p = p->jlink;
		}
	}	
	}
	else 
		printf("该顶点无相邻顶点.\n");
	return num;
}
int (*VisitFunc)(const VertexType &v);

void DFS(MulAdjGraph &G,int v)
{
	int j;
	ArcType *p;
	VisitFunc(G.adjmulist[v].data);//遍历函数
	G.adjmulist[v].isVisited = true;

	p = G.adjmulist[v].firstarc;
	while(p)
	{
		//j为另一个结点
		j=p->ivex==v ? p->jvex:p->ivex;
		if(!G.adjmulist[j].isVisited)
			DFS(G,j);//深度优先遍历
		p = p->ivex==v?p->ilink:p->jlink;//换成另一个结点
		//先深度遍历，再换结点
	}
}
//算法7.4
//从第一个顶点起，深度优先遍历图G，并对每一个顶点调用函数Visit
void DFSTraverse(MulAdjGraph &G,int (*visit)(const VertexType&))
{
	int i;
	VisitFunc = visit;//遍历方法
	for(i = 0;i<G.ivexNum;++i)//初始化标记为未访问
		G.adjmulist[i].isVisited = false;
	for(i = 0;i<G.ivexNum;++i)//遍历头结点数组进行深度优先遍历
		if(!G.adjmulist[i].isVisited)
			DFS(G,i);
	printf("\n");
}
//构造一个空队列Q（链队）
int InitQueue(LinkQueue *Q)
{
	(*Q).front=(*Q).rear=new QNode();
	if(!(*Q).front)
		exit(0);
	(*Q).front->next = NULL;//队头指针指向空
	return 1;
}
//若Q为空队列，则返回1，否则返回0
int QueueEmpty(LinkQueue Q)
{
	if(Q.front == Q.rear)
		return 1;
	else
		return 0;
}
//插入元素e为Q的新的队尾元素
int EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(0);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return 1;
}
//若队列不空，删除Q的队头元素，用e返回其值，并返回1，否则返回0
int DeQueue(LinkQueue *Q,QElemType *e)
{
	if((*Q).rear == (*Q).front)
		return 0;
	QueuePtr p;
	p = (*Q).front->next;//队头元素,有头结点
	*e = p->data;
	(*Q).front->next = p->next;
	if((*Q).rear == p)
		(*Q).rear = (*Q).front;//注意尾指针丢失的情况
	delete(p);
	return 1;
}
//销毁队列
void DestroyQueue(LinkQueue *Q)
{
	while(Q->front)
	{
		Q->rear = Q->front->next;//一个一个结点释放
		free(Q->front);
		Q->front = Q->rear;
	}
}
//从第一个顶点开始，按广度优先非递归遍历图G，并对每个顶点调用函数
//使用辅助队列Q和访问标志数组visite
void BFSTraverse(MulAdjGraph &G,int(*Visit)(const VertexType&))
{
	int i,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(i = 0;i<G.ivexNum;++i)
		G.adjmulist[i].isVisited = false;//初始化未访问
	InitQueue(&Q);//初始化辅助队列Q
	for(i=0;i<G.ivexNum;++i)
	{
		if(!G.adjmulist[i].isVisited)//v未访问
		{
			G.adjmulist.isVisited = true;
			Visit(G.adjmulist[i].data);
			EnQueue(&Q,i);//v入队列
			while(!QueueEmpty(Q))//队列不空
			{
				DeQueue(&Q,&u);//队头出队并置为u
				u1=*GetVex(G,u);//出队的元素对应的头结点
				//通过找邻接节点函数来遍历所有邻接节点——FirstAdjVex(G,u)和NextAdjVex(G,u,w)
				for(w = FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,w1))//先遍历u的邻接节点！
				{
					if(!G.adjmulist[w].isVisited)//w为u的未访问的邻接节点的序号
					{
						G.adjmulist[w].isVisited = true;
						Visit(G.adjmulist[w].data);
						EnQueue(&Q,w);
					}
					w1 = *GetVex(G,w);//返回对应的值
				}
			}
		}
	}
	DestroyQueue(&Q);
	printf("\n");
}
//置边访问标记为未被访问
void MarkUnvisited(MulAdjGraph &G)
{
	int i;
	ArcType *p;
	for(i = 0;i<G.ivexNum;++i)
	{
		p = G.adjmulist[i].firstarc;
		while(p)
		{
			p->mark = unmarked;
			if(p->ivex == i)
				p = p->ilink;
			else
				p = p->jlink;
		}
	}
}
//输出无向图的邻接多重链表G
void Display(MulAdjGraph &G)
{
	int i;
	ArcType *p;
	MarkUnvisited(G);//置边的访问标记未被访问
	printf("%d个顶点：\n",G.ivexNum);
	for(i = 0;i<G.ivexNum;++i)
	{
		printf("%d", G.adjmulist[i].data);
	}
	printf("\n%d条边:\n", G.iarcNum);
	for(i = 0;i<G.iarcNum;++i)
	{
		p = G.adjmulist[i].firstarc;
		while(p)
			if(p->ivex==i)//边的i端与该顶点有关
			{
				if(!p->mark)//只输出一次，所以要标记
				{
					printf("%d %d,%8.2f",G.adjmulist[p->ivex].data,G.adjmulist[p->jvex].data,p->weight);
					p->mark = marked;
				}
				p = p->ilink;
			}else//边的j端与该顶点有关
			{
				if(!p->mark)//只输出一次
				{
					printf("%d %d,%8.2f",G.adjmulist[p->ivex].data,G.adjmulist[p->jvex].data,p->weight);
					p->mark = marked;
				}
				p = p->jlink;
			}
			printf("\n");
	}
}
int visit(const VertexType &v)
{
	printf("%6d",v);
	return 1;
}
//参考代码：https://blog.csdn.net/hyymeishi/article/details/50481378


