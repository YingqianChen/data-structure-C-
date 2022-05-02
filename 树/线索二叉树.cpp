#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef enum
{
	Link, Thread
} PointerTag;
typedef struct BiThrNode
{
	TElemType data;
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;
BiThrTree pre = NULL;
Status Visit(TElemType e)
{
	printf("%c ", e);
	return OK;
}
Status CreateBiTree(BiThrTree &p)
{
	TElemType ch;
	scanf("%c", &ch);
	if(ch == '.')
	{
		p = NULL;
	}
	else
	{
		if(!(p = (BiThrNode *)malloc(sizeof(BiThrNode))))
		{
			exit(OVERFLOW);
		}
		p->data = ch;
		CreateBiTree(p->lchild);
		CreateBiTree(p->rchild);
	}
	return OK;
}
void InThreading(BiThrTree p)
{
	if(p)
	{
		InThreading(p->lchild);
		if(!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if(!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	void InThreading(BiThrTree p);
	if(!(Thrt = (BiThrNode *)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	}
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if(!T)
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		InThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}
void PreThreading(BiThrTree p)
{
	if(p)
	{
		if(!p->lchild)
		{
			p->LTag = Thread;
			p->lchild = pre;
		}
		if(!pre->rchild)
		{
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		if(p->LTag == Link)
		{
			PreThreading(p->lchild);
		}
		if(p->RTag == Link)
		{
			PreThreading(p->rchild);
		}
	}
}
Status PreOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	void PreThreading(BiThrTree p);
	if(!(Thrt = (BiThrNode *)malloc(sizeof(BiThrNode))))
	{
		exit(OVERFLOW);
	}
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if(!T)
	{
		Thrt->lchild = Thrt;
	}
	else
	{
		Thrt->lchild = T;
		pre = Thrt;
		PreThreading(T);
		pre->rchild = Thrt;
		pre->RTag = Thread;
		Thrt->rchild = pre;
	}
	return OK;
}
Status PreOrderTraverse_Thr(BiThrTree T, Status (* Visit)(TElemType e))
{
	BiThrTree p = T->lchild;
	while(p != T)
	{
		while(p->lchild != NULL && p->LTag == Link)
		{
			if(!Visit(p->data))
			{
				return ERROR;
			}
			p = p->lchild;
		}
		Visit(p->data);
		if(p->LTag == Thread)
		{
			p = p->rchild;
		}
	}
	return OK;
}
Status InOrderTraverse_Thr(BiThrTree T, Status (* Visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;
	while(p != T)
	{
		while(p->LTag == Link)
		{
			p = p->lchild;
		}
		if(!Visit(p->data))
		{
			return ERROR;
		}
		while(p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			Visit(p->data);
		}
		p = p->rchild;
	}
	return OK;
}
int main()
{
	BiThrTree t, thrt;
	int op;
	printf("先序递归建立二叉树：\n");
	CreateBiTree(t);
	printf("请选择遍历方式：[1]中序遍历 [2]先序遍历 [3]退出\n");
	scanf("%d", &op);
	switch(op)
	{
		case 1:
			InOrderThreading(thrt, t);
			printf("中序遍历线索二叉树：\n");
			InOrderTraverse_Thr(thrt, Visit);
			break;
		case 2:
			PreOrderThreading(thrt, t);
			printf("先序遍历线索二叉树：\n");
			PreOrderTraverse_Thr(thrt, Visit);
			break;
		default:
			break; 
	}
	return 0;
}

