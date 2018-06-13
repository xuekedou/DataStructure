#include <stdio.h>
#include <stdlib.h>

#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  INFEASIBLE -1
#define  OVERFLOW   -2

typedef int Status;

//图的数据（邻接矩阵）存储表示
#define MAX_VERTEX_NUM 20//图最大的顶点个数
typedef enum {DG,DN,UDG,UDN} GraphKind;//图的种类：有向图，有向网，无向图，无向网
typedef char InfoType;//弧相关信息的指针
typedef char VertexType;//顶点类型

#define INFINITY INT_MAX //最大值为无穷大
typedef int VRType;//顶点关系类型，对无权图，用0，1表示相邻与否；对带权图，表示权值类型
typedef struct ArcCell{
	VRType adj;//权值
	InfoType *info;//该弧相关信息的指针
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]//二维矩阵表示邻接矩阵

typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum,arcnum;//图的当前顶点数和弧数
	GraphKind kind;//图的种类
}MGraph;
//算法7.2 采用数组（邻接矩阵）表示法，构造无向网
Status CreateUDN(MGraph &G)
{
	int IncInfo;//是否有权
	int i,j,k;
	VertexType v1,v2;//结点
	VRType w;//边的权值
	printf("请输入顶点数、弧数、弧信息标志（空格分隔）：");//初始化图的一些基本信息
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);//IncInfo为1表示弧有相关信息
	getchar();//接收最后的换行符
	//输入顶点
	printf("输入%d个顶点向量:",G.vexnum);
	for(i = 0;i<G.vexnum;i++)//构造顶点向量——顶点构成的一维数组
	{
		scanf("%c",&G.vexs[i]);
		getchar();//接收最后的换行符
	}
	for(i = 0;i<G.vexnum;i++)//初始化邻接矩阵
	{
		for(j = 0;j<G.vexnum;j++)
		{
			G.arcs[i][j].adj = INFINITY;//权值初始化为无穷大
			G.arcs[i][j].info = NULL;//弧的相关信息
		}
	}
	printf("输入%d条边:\n",G.arcnum);
	for(k = 0;k<G.arcnum;k++)//构造邻接矩阵
	{
		printf("输入第%d条边依附的顶点及权值：", k+1);//边从1开始
		scanf("%c %c %d",&v1,&v2,&w);//输入边两端的结点和边上的权值
		getchar();//接收最后的换行符
		i = LocateVex(G,v1);//确定v1,v2在G中的位置
		j = LovateVex(G,v2);
		G.arcs[i][j].adj = w;//弧<v1,v2>的权值
		if(IncInfo)//如果IncInfo为0,则表示没有权；如果IncInfo为1.则表示有权
			Input(G.arcs[i][j].info);//用户输入弧的相关信息(即权)
		G.arcs[j][i] = G.arcs[i][j];//置<v1,v2>的对称弧<v2,v1>
		return OK;
	}
}
//采用数组（邻接矩阵）表示法，构造有向网G
Status CreateDN(MGraph &G)
{
	int IncInfo;
	int i,j,k;
	VertextType v1,v2;
	VRType w;
	printf("输入顶点数、弧数、弧信息标志（空格分隔）：");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);//IncInfo为1表示弧有相关信息
	getchar();//接收最后的换行符
	printf("输入%d个顶点向量",G.vexnum);
	for(i = 0;i<G.vexnum;i++)//构造顶点向量——即包含所有顶点的数组
	{
		scanf("%c",&G.vexs[i]);
		getchar();//接收最后的换行符
	}
	for(i = 0;i<G.vexnum;i++)//初始化邻接矩阵
	{
		for(j = 0;j<G.vexnum;j++)
		{
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	printf("输入%d条边:\n",G.arcnum);
	for(k = 0;k<G.arcnum;k++)//构造邻接矩阵
	{
		printf("输入第%d条边依附的顶点和权值：",k+1);
		scanf("%c %c %d",&v1,&v2,&w);
		getchar();//接收最后的换行符
		i = LocateVex(G,v1);
		j = LovateVex(G,v2);
		G.arcs[i][j].adj = w;//弧<v1,v2>的权值
		if(IncInfo)
			Input(G.arcs[i][j].info);
	}
	return OK;
}


//若G中顶点u存在，返回该顶点在图中的位置，否则返回ERROR
//即在G的顶点向量中查找u的位置
int LocateVex(MGraph G,VertextType u)//图的存储结构为邻接矩阵
{
	int i;
	for(i = 0;i<G.vexnum;i++)
	{
		if(u == G.vexs[i])//在结点数组中查找
			return i;
	}
	return ERROR;
}
//输入弧的相关信息
void Input(InfoType * &info)
{
	info = (InfoType *)malloc(50 * sizeof(InfoType));
	printf("请输入弧的信息");
	gets(info);
}
//算法7.3 创建十字链表存储表示的有向图
//存储结构的定义
typedef struct ArcBox{//弧结点的结构定义
	int tailvex,headvex;//该弧的尾和头顶点的位置
	struct ArcBox *hlink,*tlink;//分别为弧头相同或者弧尾相同的弧的链域
	InfoType *info;//该弧的相关信息指针
}ArcBox;
typedef struct VexNode{//头结点结构定义
	VertextType data;//顶点信息
	ArcBox *firstin,*firstout;//分别指向该顶点的第一条入弧和出弧
}VexNode;
typedef struct{
	VexNode xlist[MAX_VERTEX_NUM];//表头向量（存储表头结点的数组）
	int vexnum,arcnum;//有向图的顶点数和弧数
}OLGraph;//Orthogonal List
//算法实现
Status CreateDG(OLGraph &G)
{
	int i,j,k,IncInfo;
	VertexType v1,v2;
	ArcBox *p;//弧结点
	printf("输入有向图顶点数和弧数及弧是否含信息（0/1）:");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	getchar();//换行
	printf("输入%d个顶点（空格分隔）：",G.vexnum);
	for(i = 0;i<G.vexnum;i++)//构建表头结点向量
	{
		scanf("%c",&G.xlist[i].data);
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;//初始化链域均为空
		getchar();
	}
	for(k = 0;k<G.arcnum;k++)
	{
		printf("输入一条弧的起点和终点:");
		scanf("%c %c",&v1,&v2);//v1是起点，v2是终点
		getchar();
		i = LocateVex(G,v1);//i是起点(弧尾)；j是终点(弧头)
		j = LocateVex(G,v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));
		if(!p)
			return ERROR;
		//头插法插入链表中
		(*p).headvex = j;//注意：起点终点和弧尾弧头的对应
		(*p).tailvex = i;
		(*p).hlink = G.xlist[j].firstin;
		(*p).tlink = G.xlist[i].firstout;
		(*p).info = NULL;
		G.xlist[i].firstout = G.xlist[j].firstin = p;
		if(IncInfo)
			input((*p).info);
	}
	return OK;
}
//LocateVex函数
int LocateVex(OLGraph G,VertexType u)
{
	int i;
	for(i = 0;i<G.vexnum;i++)
	{
		if(G.xlist[i].data == u)
			return i;
	}
	return ERROR;
}
//邻接链表存储无向图(区别与无向网)
//邻接表存储表示
typedef struct ArcNode{//链表中的结点
	int adjvex;//该弧所指向的顶点的位置（顺序表中的位置）
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType *info;//该弧相关信息的指针
}ArcNode;
typedef struct VNode{//头结点
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向依附该顶点的第一条弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct{
	AdjList vertices;//存放带头结点的数组
	int vexnum,arcnum;//图的顶点数和弧数
	GraphKind kind;//图的种类
}ALGraph;
//算法实现
Status CreateUDG(ALGraph &G)
{
	int i,j,k,IncInfo;
	ArcNode *p;
	VertexType v1,v2;
	G.kind = UDG;//图的种类为无向图
	printf("请输入图的顶点数、弧数及弧信息标志：");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	getchar();//空格
	printf("输入%d个顶点："，G.vexnum);
	for(i = 0;i<G.vexnum;i++)
	{
		scanf("%c",&G.vertices[i].data);//存放头结点的数组
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("输入%d条弧\n",G.arcnum);
	for(k = 0;k<G.arcnum;k++)
	{
		printf("输入第%d条弧：",k+1);
		scanf("%c %c",&v1,&v2);
		getchar();
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		//两条链上分别添加两个弧结点
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if(!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;//下一条弧的位置
		p->adjvex = j;//该弧指向下一个顶点的位置
		G.vertices[i].firstarc = p;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if(!p)
			return ERROR;
		p->nextarc = G.vertices[j].firstarc;
		p->adjvex = i;
		G.vertices[j].firstarc = p;

		if(IncInfo)
		{
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}
	return OK;
}
//邻接表存储有向图
Status CreateDG(ALGraph &G)
{
	int i,j,k,IncInfo;
	ArcNode *p;
	VertexType v1,v2;
	G.kind = DG;//图的种类为有向图
	printf("请输入有向图的顶点数、弧数及信息标志：");
	scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);
	getchar();
	printf("输入%d个顶点：",G.vexnum);
	for(i = 0;i<G.vexnum;i++)
	{
		scanf("%c",&G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("输入%d条弧（有向）\n",G.arcnum);
	for(k = 0;k<G.arcnum;k++)
	{
		printf("输入第%d条弧：",k+1);
		scanf("%c %c",&v1,&v2);
		getchar();
		i = LocateVex(G,v1);
		j = LocateVex(G,v2);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if(!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;//下一条弧线
		p->adjvex = j;//这条弧线的另一个顶点
		G.vertices[i].firstarc = p;
		if(IncInfo){
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}
	return OK;
}
//创建邻接链表存储的有向网，弧信息即为权值
Status CreateDN(ALGraph &G)
{
	int i,j,k;
	ArcNode *p;
	char value[10];//权值信息
	VertexType v1,v2;
	G.kind = DG;
	printf("请输入有向图的顶点数及弧数：");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	getchar();
	printf("输入%d个顶点",G.vexnum);
	for(i = 0;i<G.vexnum;i++)
	{
		scanf("%c",&G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	//到这里邻接链表已经初始化好了——vertices[]\vexnum,arcnum\kind
	//以下是根据图的类型不同，构造不同邻接链表
	printf("请输入%d条弧（有向）\n",G.arcnum);
	for(k = 0;k<G.arcnum;k++)
	{
		printf("输入第%d条弧及其权值(空格分隔):",k+1);
		scanf("%c %c %s",&v1,&v2,value);//value为数组名
		getchar();
		i = LocateVex(G,v1);
		j = Locatevex(G,v2);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if(!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		G.vertices[i].firstarc->info = (char *)malloc(50 * sizeof(char));//先请求分配空间
		strcpy(G.vertices[i].firstarc->info,value);
	}
	return OK;
}
//领接表存储表示无向图G，v是G的顶点
//返回指定第v个顶点的第一个邻接顶点的位置，若不存在，则返回-1
int FirstAdjVex(ALGraph G,int v)
{
	if(NULL != G.vertices[v].firstarc){
		return G.vertices[v].firstarc->adjvex;
	}else
	{
		return -1;
	}
}
//领接表存储表示无向图G存在，v是G中的顶点，w是v的邻接顶点(不一定是第一个)
//返回v的下一个(相对于w)的邻接顶点的位置，若w是最后一个，则返回-1；
int NextAdjVex(ALGraph G,int v,int w)
{
	ArcNode *p;
	p = G.vertices[v].firstarc;
	while(p){
		if(p->adjvex = w){//找到顶点为w的弧
			p = p->nextarc;
			if(p!=NULL)//v的下一个邻接顶点存在
			{
				return p->adjvex;
			}else
			{
				return -1;
			}
		}else
		{
			p = p->nextarc;
		}
	}
}
//返回邻接顶点第v个结点的信息
VertexType GetVex(ALGraph G,int v)
{
	return G.vertices[v].data;
}
