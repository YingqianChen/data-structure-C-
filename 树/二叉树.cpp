#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define MAX_TREE_SIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef char TElemType;
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
typedef BiTree SElemType;
typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;
Status InitStack(SqStack &S)
{
	S.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
	{
		exit (OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status Push(SqStack &S, SElemType p)
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			exit (OVERFLOW);
		}
		S.top = S.top + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top ++= p;
	return OK;
}
Status Pop(SqStack &S, SElemType &p)
{
	if(S.top == S.base)
	{
		return ERROR;
	}
	p = *--S.top;
	return OK;
}
Status StackEmpty(SqStack S)
{
	if(S.base == S.top)
	{
		return TRUE;
	}
	return FALSE;
}
Status InitBiTree(BiTree &T)
{
	if(T == NULL)
	{
		return OK;
	}
	T = NULL;
	return OK;
}
Status Visit(TElemType e)
{
	printf("%c ", e);
	return OK;
}
Status CreateBiTree(BiTree &T)
{
	TElemType ch;
	ch = getchar();
	if(ch == '.')
	{
		T = NULL;
	}
	else
	{
		if(!(T = (BiTNode *)malloc(sizeof(BiTNode))))
		{
			exit(OVERFLOW);
		}
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}
Status FindNode(BiTree T, TElemType e)
{
	if(!T)
	{
		return ERROR;
	}
	else if(T->lchild != NULL && T->lchild->data == e ||
			T->rchild != NULL && T->rchild->data == e)
	{
		Visit(T->data);
		return OK;
	}
	else if(FindNode(T->lchild, e) || FindNode(T->rchild, e))
	{
		Visit(T->data);
		return OK;
	}
	else
	{
		return ERROR;
	}
}
int BiTHeight(BiTree T)
{
	int height, left, right;
	if(T == NULL)
	{
		return 0;
	}
	left = BiTHeight(T->lchild);
	right = BiTHeight(T->rchild);
	if(left > right)
	{
		return left + 1;
	}
	else
	{
		return right + 1;
	}
}
Status PreOrderTraverse(BiTree T, Status (* Visit)(TElemType e))
{
	if(T)
	{
		if(Visit(T->data))
		{
			if(PreOrderTraverse(T->lchild, Visit))
			{
				if(PreOrderTraverse(T->rchild, Visit))
				{
					return OK;
				}
			}
		}
		return ERROR;
	}
	else
	{
		return OK;
	}
}
Status InOrderTraverse(BiTree T, Status (* Visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	p = T;
	InitStack(S);
	while(p || !StackEmpty(S))
	{
		if(p)
		{
			Push(S, p);
			p = p->lchild;
		}
		else
		{
			Pop(S, p);
			if(!Visit(p->data))
			{
				return ERROR;
			}
			p = p->rchild;
		}
	}
	return OK;
}
Status PostOrderTraverse(BiTree T, Status (* Visit)(TElemType e))
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild, Visit))
		{
			if(PostOrderTraverse(T->rchild, Visit))
			{
				if(Visit(T->data))
				{
					return OK;
				}
			}
		}
		return ERROR;
	}
	else
	{
		return OK;
	}
}
int main()
{
	BiTNode *T;
	int h;
	TElemType ch;
	InitBiTree(T);
	printf("先序建立二叉树：\n"); 
	CreateBiTree(T);
	h = BiTHeight(T);
	printf("二叉树的高度为%d", h);
	printf("\n先序递归遍历二叉树：\n");
	PreOrderTraverse(T, Visit);
	printf("\n中序非递归遍历二叉树：\n");
	InOrderTraverse(T, Visit);
	printf("\n后序递归遍历二叉树：\n");
	PostOrderTraverse(T, Visit);
	printf("\n请输入要查找的结点值：\n");
	scanf(" %c", &ch);
	printf("所查找结点的父结点为：\n");
	FindNode(T, ch);
	return 0;
}
