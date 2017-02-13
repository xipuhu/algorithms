#include<stdio.h>
#include<stdlib.h>
typedef struct BiTNode{
	int data;                         //数据域
	struct BiTNode *lchild, *rchild;  //左、右孩子
}BiTNode,*BiTree;


BiTree TreeCreat(BiTree BT, int k);
void PreOrder(BiTree T);
void PreOrder_nonrecur(BiTree T);
void InOrder_nonrecur(BiTree T);
void PostOder_nonrecur(BiTree T);
int main(){
	BiTree BT = (BiTNode *)malloc(sizeof(BiTNode *));
	BiTree tree = TreeCreat(BT, 0);
	//PreOrder(tree);
	//PreOrder_nonrecur(tree);
	//InOrder_nonrecur(tree);
	PostOder_nonrecur(tree);

	printf("\n");
	system("pause");
	return 0;

}
//生成二叉树函数
BiTree TreeCreat(BiTree BT,int k){

	BiTree p = (BiTNode *)malloc(sizeof(BiTNode *));
	int x;
	printf("输入节点的数值：");

	scanf_s("%d", &x);
	if (x != 0){
		if (!(p = (BiTNode *)malloc(sizeof(BiTNode *)))) exit(0);

		//生成根结点
		p->data = x;
		p->lchild = NULL;
		p->rchild = NULL;

		if (k == 0) BT = p;
		if (k == 1) BT->lchild = p;
		if (k == 2) BT->rchild = p;

		TreeCreat(p, 1);  //生成左子树
		TreeCreat(p, 2);  //生成右子树
	}
	return BT;
}

//二叉树先序递归遍历
void PreOrder(BiTree T){
	if (T != NULL){
		printf("%d", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}

}
//二叉树先序非递归遍历
void PreOrder_nonrecur(BiTree T){
	BiTree st[20];
	int top = -1;
	BiTree p = (BiTNode *)malloc(sizeof(BiTNode *));
	if (T != NULL){
		st[++top] = T;
		while (top>-1)
		{
			p = st[top--];
			printf("%d", p->data);

			if (p->rchild != NULL) st[++top] = p->rchild;
			if (p->lchild != NULL) st[++top] = p->lchild;
			
		}
	}

}
//二叉树中序非递归遍历
void InOrder_nonrecur(BiTree T){
	BiTree st[20];
	BiTree p = (BiTree)malloc(sizeof(BiTree));
	p = T;
	int top = -1;
	while (p != NULL || top > -1){
	    
		if (p != NULL){
			st[++top] = p;
			p = p->lchild;
		}
		else
		{
			p = st[top--];
			printf("%d", p->data);
			p = p->rchild;
		}
	}
	free(p);
}

//二叉树后序非递归遍历
void PostOder_nonrecur(BiTree T){
	BiTree st[20];
	BiTree p = (BiTree)malloc(sizeof(BiTree));

	int flag, top = -1;
	do
	{
		//将根结点的左子树入栈
		while (T != NULL){     
			st[++top] = T;
			T = T->lchild;
		}

		p = NULL, flag = 1;
	    
		//在栈顶元素即当前的根结点出栈前将该根结点的右子数入栈
		while (top != -1 && flag==1){

			T = st[top];
			if (T->rchild == p){
				--top;
				printf("%d", T->data);
				p = T;               //p指向刚才访问的结点
			}
			else
			{
				T = T->rchild;
				flag = 0;           //设置成未被访问的标记并跳出while语句
			}
		}


	} while (top!=-1);

}