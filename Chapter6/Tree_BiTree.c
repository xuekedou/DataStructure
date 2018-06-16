//结构体定义
typedef int TreeData;//树中结点数据的类型

//树结点的类型
typedef struct _treenode
{
	TreeData data;//数据域
	struct _treenode *child;//指向长子的指针
	struct _treenode *brother;//指向右兄弟的指针
}TreeNode;

//树类型
typedef struct _treenode
{
	int len;//树结点的个数（不算头结点）
	TreeNode *head;//指向头结点的指针
}

//只写有关操作的具体代码
//创建树
Tree *Create_tree()
{
	//创建一棵树
	Tree *tree = (Tree*)malloc(sizeof(Tree)/sizeof(char));
	if(tree == NULL)
	{
		return NULL;
	}
	//创建头结点
	tree->head = (TreeNode *)malloc(sizeof(TreeNode)/sizeof(char));
	if(tree->head == NULL)
	{
		return NULL;
	}
	tree->heaf->child = NULL;//头结点的孩子结点指针为空，此树为空
	tree->head->brother = NULL;//头结点没有兄弟
	tree->len = 0;
	return tree;
}

//插入树
int Insert_Tree(Tree *tree,TreeData data,int pos,int count,int flag)
{
	if(tree==NULL || count<0 || pos<0 || flag != CHILD && flag != BROTHER)
	{
		return FALSE;
	}
	//创建树结点
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode)/sizeof(char));
	if(node == NULL)
	{
		return FALSE;
	}
	//初始化树结点，该节点的孩子和右兄弟都为空
	node->data = data;
	node->child = NULL;
	node->brother = NULL;
	
}
