//算法7.7 建立无向图G的深度优先生成森林的孩子兄弟链表
Status DFSForst(ALGraph G,CSTree &T,bool visited[])
{
	//ALGraph是已经建立好的邻接链表
	int v;
	CSTree p,q;
	for(v = 0;v<G.vexnum;v++)//初始化结点元素未访问
	{
		visited[v] = false;
	}
	for(v = 0;v<G.vexnum;v++)
	{
		if(!visited[v])//第v顶点为新的生成树的根节点
		{
			//CSTree是利用孩子兄弟表示法存储的树
			p = (CSTree)malloc(sizeof(CSNode));//分配根结点
			if(!p)
				return ERROR;
			p->data = GetVex(G,v);//给该结点赋值
			p->lchild = NULL;
			p->nextsibling = NULL;
			if(!T){//是第一棵生成树的根
				T = p;
			}else{
				q->nextsibling = p;//是其他生成树的根（前一棵的根的兄弟）
			}	
			q = p;//q指向当前生成树的根
			DFSTree(G,v,p,visited);//建立以p为根的生成树
		}
	}
	return OK;
}
//算法7.8 从第v个顶点出发深度优先遍历图G，简历以T为根的生成树
Status DFSTree(ALGraph G,int v,CSTree T,bool visited[])
{
	bool first;
	CSTree p,q;
	int w;
	visited[v] = true;
	first = true;
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
	{
		if(!visited[w])
		{
			p = (CSTree)malloc(sizeof(CSNode));//分配孩子结点
			if(!p)
			{
				return ERROR;
			}
			p->data = GetVex(G,w);
			p->lchild = NULL;
			p->nextsibling = NULL;
			if(first)//w是v的第一个未被访问的邻接节点
			{
				T->lchild = p;
				first = false;//是根的左孩子结点
			}
			else{//w是v的其他未被访问的邻接节点
				q->nextsibling = p;//是上一邻接节点的有兄弟结点
			}
			q = p;
			DFSTree(G,w,q,visited);//从第w个顶点出发深度优先遍历图G，建立子树q
		}
	}//DSTree
	return OK;
}
//算法7.9 Prim算法，最小生成树
//时间复杂度为o(n^2),适合于求边稠密的网的最小生成树
void MiniSpanTree_PRIM(MGraph G,VertexType u)//网以二维矩阵存储，两个顶点不存在的边的权值为机内允许最大值
{
	int i,j,k;
	lowedge closedge;
	k = LocateVex(G,u);
	for(j=0;j<G.vexnum;j++)//辅助数组初始化
	{
		if(j!=k)
		{
			closedge[j].adjvex = u;
			closedge[j].lowcost = G.arc[k][j].adj;//{adjvex,lowcost}
		}
	}
	closedge[k].lowcost = 0;//初始 U={u}
	printf("最优树的边：\n");
	for(i = 1;i<G.vexnum;i++)//选择其余G.vexnum-1个顶点
	{
		k = minium(closedge,G.vexnum);//求出T的下一个结点:第k顶点
		printf("%c %c\n",closedge[k].adjvex,G.vexs[k]);//输出生成树的边
		closedge[k].lowcost = 0;//将k顶点并入U集
		for(j=0;j<G.vexnum;j++)
		{
			if(G.arcs[k][j].adj < closedge[j].lowcost)//新顶点并入U后重新选择最小边
			{
				closedge[j].adjvex = G.vexs[k];
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}

	}
}
//求closedge中权值非0的最小的顶点
int minium(lowedge closedge,int len)
{
	int min,i,j;
	min = -1;
	for(i=0;i<len;i++)
	{
		if(closedge[i].lowcost != 0)
		{
			min = i;
			break;
		}
	}
	for(j = i;j<len;j++)
	{
		if(closedge[j].lowcost != 0 && closedge[min].lowcost > closedge[j].lowcost)
		{
			min = j;
		}
	}
	return min;
}

//克鲁斯卡尔(Kruskal)算法——最小生成树的另一种算法（时间复杂度为o(eloge)）
#define MAXN 11//顶点个数的最大值
#define MAXM 20 //边个数的最大值

struct edge//边
{
	int u,v,w;//边的顶点和权值
}edges[MAXM];//边的数组

int parent[MAXN];//parent[i]为顶点i所在集合对应的树中的根结点
int n,m;//顶点个数，边的个数
int i,j;//循环变量
void UFset()//初始化
{
	for(i = 1;i<=n;i++)
		parent[i] = -1;
}
//并查集(Union-Find Set)——一种数据结构
//原时间复杂度：o(e^2),使用并查集优化之后为:o(eloge)
int Find(int x)//查找并返回结点x所在集合的根节点
{
	int s;//查找位置
	for(s=x;parent[s]>=0;s = parent[s]);
		while(s!=x)//优化方案-压缩路径，使后续的查找操作加速
		{
			int tmp = parent[x];
			parent[x] = s;
			x = tmp;
		}
		return s;
}
//将两个不同集合的元素进行合并，使两个集合中任两个元素都连通
void Union(int R1,int R2)
{
	int r1 = Find(R1),r2 = Find(R2);//r1为R1的根结点，r2为R2的根节点
	int tmp = parent[r1] + parent[r2];//两个集合结点个数之和（负数）
	//如果R2所在树结点个数>R1所在树结点个数(注意parent[r1]是负数)
	if(parent[r1]>parent[r2])//优化方案——加权法则
	{
		parent[r1] = r2;
		parent[r2] = tmp;
	}else
	{
		parent[r2] = r1;
		parent[r1] = tmp;
	}
}

bool cmp(edge a,edgeb)//实现边按权值从小到大排序的比较函数
{
	return a.w<=b.w;
}
//Kruskal算法的实现代码
vodi Kruskal()
{
	int sumweight = 0;//生成树的权值
	int num = 0;//已选用的边的数目
	int u,v;//选用边的两个顶点
	UFset();//初始化parent[]数组
	for(i=0;i<m;i++)
	{
		u = edges[i].u;v = edges[i].v;
		if(Find(u)!=Find(v))
		{
			printf("%d %d %d\n",u,v,edges[i].w);
			sunweight += edges[i].w;num++;
			Union(u,v);
		}
		if(num>=n-1) break;
	}
	printf("Weight of MST is %d\n",sumweight);
}
//测试
int main()
{
	int u,v,w;//边的起点和终点以及权值
	scanf("%d%d",&n,&m);//读入顶点个数n
	for(int i = 0;i<m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);//读入边的起点和终点
		edges[i].u = u;
		edges[i].v = v;
		edges[i].w = w;
	}
	sort(edges,edges+m,cmp);
	Kruskal();
	return 0;
}
//算法7.12 求拓扑序列，有向图G用邻接链表存储结构，若G中无回路则输出拓扑序列并返回OK
Status TopologicalSort(ALGraph G)
{
	int i,j,count;
	ArcNode *p;
	int indegree[MAX_VERTEX_NUM];
	int stack[MAX_VERTEX_NUM];//避免重复检测ID为0的顶点，用栈来暂存所有ID为0的顶点
	int top = 0;//栈指针
	FindInDegree(G,indegree);//对各个顶点求ID indegree[0...vernum-1]
	for(i = 0;i<G.vexnum;i++)
	{
		if(indegree[i] == 0){//初始时所有ID为0的顶点入栈
			stack[top] = i;
			++top;
		}
	}
	count = 0;//拓扑序列内的顶点数计数
	while(top!=0){
		--top;
		i = stack[top];///弹栈访问ID为0的顶点
		printf("%d:%c\n",count+1,G.vertices[i].data);//弹出顶点信息
		++count;//计数+1
		for(p = G.vertices[i].fistarc;p!=NULL;p=p->nextarc)
		{
			j = p->adjvex;//顶点入度-1
			--indegree[j];
			if(indegree[j]==0){
				stack[top] = j;//ID为0顶点进栈
				++top;
			}
		}
	}
	if(count < G.vexnum)//说明有向图存在回路
	{
		return ERROR;
	}else{
		return OK;
	}
}
