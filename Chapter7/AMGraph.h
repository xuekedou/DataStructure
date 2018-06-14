//声明区域
typedef enum{unmarked,marked}MarkedIf;
typedef int VertexType;//图结点标识号
typedef int QElemType;

//数据结构体
typedef struct ArcType//边结点
{
	int ivex,jvex;//该边依附的两个顶点的位置
	struct ArcType *ilink,*jlink;//分别指向依附这两个顶点的下一条边
	MarkedIf mark;//是否访问
	float weight;//权重
	inline Arctype:ivex(-1),jvex(-1),mark(unmarked),weight(0){}//inline内联函数
}ArcType;
typedef struct VertexNode//头结点
{
	VertexType data;
	bool isVisited;//访问标记
	ArcType *firstarc;//指向第一条依附该顶点的边
	inline VertexNode():data(-1),isVisited(false){}
}VertexNode;
typedef struct MulAdjGraph
{
	VertexNode *adjmulist;//头结点向量
	int ivexNum,iarcnum;//顶点数和边数
	int MaxVertexNum;//表中最大的结点数
	MulAdjGraph():ivexNum(0),iarcnum(0),MaxVertexNum(0){}
}MulAdjGraph;
//单链队列-队列的链式存储结构
typedef struct QNode
{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front,rear;//队头和队尾指针
}LinkQueue;
//------------------------------基本函数操作
//若G中存在顶点u，则返回该顶点在无向图中位置，否则返回-1
int LocateVex(const MulAdjGraph &G,const VertexType &u);

//采用邻接多重链表存储结构，构造无向图
int CreateGraph(MulAdjGraph &G);

//返回v值
inline VertexType* GetVex(const MulAdjGraph &G,const int &v);

//对v赋新值value
int PutVex(MulAdjGraph &G,const VertexType v,const VertexType &value);

//返回v的第一个领接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
int FirstAdjVex(const MulAdjGraph &G,const VertexType &v);

//返回v的（相对w的）下一个邻接顶点的序号，若w是v的最后一个邻接顶点，则返回-1
int NextAdjVex(const MulAdjGraph &G,const VertexType &v,const VertexType &w);

//在G中增添新顶点v（不增添与顶点相关的弧，留待InsertArc()去实现）
int InsertVer(MulAdjGraph &G,const VertexType v);

//在G中删除弧<v,w>
int DeleteArc(MulAdjGraph &G,const VertexType &v,const VertexType &w);

//删除G中顶点v及其相关的边
int DeleteVex(MulAdjGraph &G,const VertexType &v);

//销毁G
void DestroyGraph(MulAdjGraph &G);

//在G中添加弧<v,w>
int InsertArc(MulAdjGraph &G,const VertextType &v,const VertexType &w);

//搜索弧<v,w>是否存在
bool SearchArc(const MulAdjGraph &G,const VertexType &v,VertexType &w);

//找到顶点v的邻接顶点，函数返回符合条件的顶点数目
int FindNeighbour(const MulAdjGraph &G,const VertexType &v,VertexType *s);

extern int (*VisitFunc)(const VertexType &v);

void DFS(MulAdjGraph &G,int v);//v为遍历的开始结点

//算法7.4
//从第一个顶点其，深度优先遍历图G，并对每个顶点调用函数visit
void DFSTraverse(MulAdjGraph &G,int(*visit)(const VertexType&));

//从第一个顶点起，按广度优先非递归遍历图G，并对每个顶点调用函数
//使用辅助队列Q和访问标志数组visite
void BFSTraverse(MulAdjGraph &G,int(*visit)(const VertexType&));

//置边的访问标记为未被访问
void MarkUnvisited(MulAdjGraph &G);

//输出无向图的邻接多重链表G
void Display(MulAdjGraph &G);

int visit(const VertexType &v);




