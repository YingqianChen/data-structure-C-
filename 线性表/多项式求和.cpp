#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct Lnode
{
	ElemType coef;
	ElemType exp;
	struct Lnode *next;
} LNode, *LinkList;
LinkList CreatePoly()
{
	LinkList H = (LinkList)malloc(sizeof(LNode));
	H->next = NULL;
	LNode *r = H, *s;
	int x, y;
	printf("请输入多项式各项的系数和指数（系数等于0时结束）：\n");
	scanf("%d %d", &x, &y);
	while(x != 0)
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->coef = x;
		s->exp = y;
		r->next = s;
		r = s;
		s->next = NULL;
		scanf("%d %d", &x, &y);
	}
	return H;
}
void PrintPoly(LinkList H)
{
	LNode *p = H->next;
	int count = 1; 
	if(!p)
	{
		return;
	}
	while(p)
	{
		if(p->coef > 0 && count > 1) //判断何时在系数前输出+ 
		{
			printf("+");
		}
		if(p->coef == 1) //系数=1 
		{
			if (p->exp == 1) //指数=1 
			{
				printf("X", p->exp);
			}
			else if(p->exp > 1) //指数为大于1的正数 
			{
				printf("X^%d", p->exp);
			}
			else if(p->exp < 0) //指数小于0 
			{
				printf("X^(%d)", p->exp);
			}
			else //指数=0 
			{
				printf("%d", p->coef);
			}
		}
		else if(p->coef == -1) //系数=-1 
		{
			if (p->exp == 1)
			{
				printf("-X", p->exp);
			}
			else if(p->exp > 1)
			{
				printf("-X^%d", p->exp);
			}
			else if(p->exp < 0)
			{
				printf("-X^(%d)", p->exp);
			}
			else
			{
				printf("%d", p->coef);
			}
		}
		else if(p->coef > 1) //系数为大于1的正数 
		{
			if (p->exp == 1)
			{
				printf("%dX", p->coef);
			}
			else if(p->exp > 1)
			{
				printf("%dX^%d", p->coef, p->exp);
			}
			else if(p->exp < 0)
			{
				printf("%dX^(%d)", p->coef, p->exp);
			}
			else
			{
				printf("%d", p->coef);
			}
		}
		else if(p->coef < -1) //系数为小于-1的正数 
		{
			if (p->exp == 1)
			{
				printf("%dX", p->coef);
			}
			else if(p->exp > 1)
			{
				printf("%dX^%d", p->coef, p->exp);
			}
			else if(p->exp < 0)
			{
				printf("%dX^(%d)", p->coef, p->exp);
			}
			else
			{
				printf("%d", p->coef);
			}
		}
		p = p->next;
		count ++; 
	}
	printf("\n");
}
void AddPoly(LinkList pa, LinkList pb)
{
	void PrintPoly(LinkList H);
    LNode *qa = pa->next;
    LNode *qb = pb->next;
    LinkList p = (LinkList)malloc(sizeof(LNode));
	p->next = NULL;
    LNode *pc = p;
    while (qa && qb)
	{
        if(qa->exp < qb->exp)
		{
            pc->next = qb;
            pc = qb;
            qb = qb->next;
        }
        else if(qa->exp > qb->exp)
		{
            pc->next = qa;
            pc = qa;
            qa = qa->next;
        }
        else if(qa->coef + qb->coef != 0)
		{
            qa->coef = qa->coef + qb->coef;
            pc->next = qa;
            pc = qa;
            qa = qa->next;
            qb = qb->next;
        }
        else if(qa->coef + qb->coef == 0)
		{
			qa = qa->next;
            qb = qb->next;
        }
    }
    while(qa)
    {
    	pc->next = qa;
    	qa = qa->next;
	}
	while(qb)
    {
    	pc->next = qb;
    	qb = qb->next;
	}
	PrintPoly(p);
}
int main() 
{
	LinkList CreatePoly();
	void PrintPoly(LinkList H);
	void AddPoly(LinkList pa, LinkList pb);
	LinkList pa, pb;
	pa = CreatePoly(); //创建多项式A(X)
	pb = CreatePoly(); //创建多项式B(X)
	printf("多项式A(X) = ");
	PrintPoly(pa);
	printf("多项式B(X) = ");
	PrintPoly(pb);
	printf("A(X)+B(X) = ");
	AddPoly(pa, pb); //输出多项式合并后的结果 
	return 0;
}

