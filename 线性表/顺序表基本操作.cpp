//ʵ��˳���Ľ��������롢���ҡ�ɾ���Ȳ��� 
#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OVERFLOW -1
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType *elem;
	int length;
	int listsize;
}SqList;
Status InitList_Sq(SqList &L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)
	{
		exit(OVERFLOW);
	}
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
Status ListInsert_Sq(SqList &L, int i, ElemType e)
{
	if(i < 1 || i > L.length+1)
	{
		return ERROR;
	}
	if(L.length >= L.listsize)
	{
		ElemType *newbase = (ElemType*)realloc(L.elem,
		(L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)
		{
			return ERROR;
		}
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	ElemType *p, *q;
	q = &(L.elem[i-1]);
	for(p = &(L.elem[L.length-1]); p >= q; --p)
	{
		*(p+1) = *p;
	}
	*q = e;
	++L.length;
	return OK;
}
Status compare(ElemType x, ElemType y)
{
	if(x == y)
	{
		return 1;
	}
	else return 0;
}
int LocateElem_Sq(SqList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	int i;
	ElemType *p;
	i = 1;
	p = L.elem;
	while(i <= L.length && !(*compare)(*p++, e))
	{
		++i;
	}
	if(i <= L.length)
	{
		return i;
	}
	else return ERROR;
}
Status ListDelete_Sq(SqList &L, int i, ElemType &e)
{
	ElemType *p, *q;
	if(i < 1 || i > L.length)
	{
		return ERROR;
	}
	p = &(L.elem[i-1]);
	e = *p;
	q = L.elem+L.length-1;
	for(++p; p <= q; ++p)
	{
		*(p-1) = *p;
	}
	--L.length;
	return OK; 
}
void print(SqList &L)
{
	for(int i = 0; i < L.length; i++)
	{
		printf("%d ", L.elem[i]);
	}
	printf("\n");
}
int main() 
{
	SqList List;
	InitList_Sq(List); //����һ���յ�˳��� 
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for(int i = 0; i < 10; i++) //�������е�Ԫ�����β���˳���
	{
		ListInsert_Sq(List, i+1, a[i]);
	}	
	printf("��ʼ˳���Ϊ��\n");
	print(List);
	ListInsert_Sq(List, 4, 21); //�ڵ�4��λ�ò���Ԫ��21
	printf("������Ԫ��֮���˳���Ϊ��\n");
	print(List);
	int add;
	add = LocateElem_Sq(List, 9, (*compare));
	printf("Ԫ��9��λ��Ϊ��%d\n", add);
	ElemType e;
	ListDelete_Sq(List, 8, e); //ɾ��˳���ĵ�8��Ԫ��
	printf("ɾ����Ԫ��Ϊ%d\n", e);
	printf("ɾ�����˳���Ϊ��\n");
	print(List);
	return 0;
}
