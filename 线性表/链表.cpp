#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Lnode
{
	ElemType data;
	struct Lnode *next;
} LNode, *LinkList;
LinkList CreateList()
{
	LinkList H = (LinkList)malloc(sizeof(LNode));
	H->next = NULL;
	LNode *r = H, *s;
	int x;
	printf("请输入链表中的元素（输入非数时结束）：\n");
	while(scanf("%d", &x))
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->data = x;
		r->next = s;
		r = s;
		s->next = NULL;
	}
	
	return H;
}
void PrintList1(LinkList H)
{
	LNode *p = H->next;
	if(!p)
	{
		return;
	}
	while(p)
	{ 
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
void PrintList2(LinkList H)
{
	LNode *p = H;
	if(!p)
	{
		return;
	}
	while(p)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
int Length_LinkList(LinkList H)
{
	LNode *p = H;
	int j = 0;
	while(p->next)
	{
		p = p->next;
		j++;
	}
	return j;
}
LinkList Inverse(LinkList head)
{
	int Length_LinkList(LinkList head);
	void PrintList1(LinkList H);
	int i, len;
	LNode *p1, *p2, *newhead = NULL, *NEW;
	len = Length_LinkList(head);
	for(i=0; i<len; i++)
	{
		p1 = p2 = head;
		while(p1->next)
		{
			p2 = p1;
			p1 = p1->next;
		}
		if(i == 0)
		{
			newhead = NEW = p1;
		}
		else
		{
			NEW->next = p1;
			NEW = p1;
		}
		p2->next = NULL;
	}
	return newhead;
}
int main()
{
	LinkList CreateList();
	void PrintList1(LinkList H);
	void PrintList2(LinkList H);
	LinkList Inverse(LinkList head);
	LinkList p, pi;
	p = CreateList();
	printf("初始链表为：\n"); 
	PrintList1(p);
	printf("逆序排列后的链表为：\n"); 
	pi = Inverse(p);
	PrintList2(pi);
	return 0;
}
