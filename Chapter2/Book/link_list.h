#ifndef _LINK_LIST_
#define _LINK_LIST_

struct LNode
{
	ElemType data;
	struct LNode *next;
};

void InitList_L(struct LNode * &L);
void DestroyList_L(struct LNode * &L);
void ClearList_L(struct LNode * &L);
bool ListEmpty_L(struct LNOde * &L);
int ListLength_L(struct LNode * &L);
Status GetElem_L(struct LNode * &L,int i,ElemType &e);
int LocateElem_L(struct LNode * &L Elemtype e,Status (*compare)(Elemtype,Elemtype));
Status PriorElem_L(struct LNode * &L,Elemtype cur_e,Elemtype &pre_e);
Status NextElem_L(struct LNode * &L,Elemtype cur_e,Elemtype &next_e);
Status ListInsert_L(struct LNode * &L,int i,Elemtype e);
Status ListDelete_L(struct LNode * &L,int i,Elemtype &e);
Status ListTraverse_L(struct LNode * &L, Status (*visit)(struct LNode * &));
Status visit_display_L(struct LNode * &L);
void CreateList_L(struct LNode * &L,int n);
void MergeList_L(struct LNode * &La,struct LNode * &Lb,struct LNode * Lc);


#endif