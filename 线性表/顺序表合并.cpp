//两个顺序表的合并。已知线性表La和Lb中的数据元素按值非递减排列。归并La和Lb得到新的线性表Lc，使Lc的数据元素也按值非递减排列 
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
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
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
void print(SqList &L)
{
	for(int i = 0; i < L.length; i++)
	{
		printf("%d ", L.elem[i]);
	}
	printf("\n");
}
void merge(SqList &La, SqList &Lb, SqList &Lc)
{
	ElemType *pa, *pb, *pc, *pa_last, *pb_last;
	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if(!Lc.elem)
	{
		exit(OVERFLOW);
	}
	pa_last = pa + La.length - 1;
	pb_last = pb + Lb.length - 1;
	while(pa <= pa_last && pb <= pb_last)
	{
		if(*pa < *pb)
		{
			*pc++ = *pa++;
		}
		else *pc++ = *pb++;
	}
	while(pa <= pa_last)
	{
		*pc++ = *pa++;
	}
	while(pb <= pb_last)
	{
		*pc++ = *pb++;
	}
}
int main()
{
	Status InitList_Sq(SqList &L);
	Status ListInsert_Sq(SqList &L, int i, ElemType e);
	void print(SqList &L);
	void merge(SqList &La, SqList &Lb, SqList &Lc);
	SqList La, Lb, Lc;
	InitList_Sq(La); //创建La表 
	InitList_Sq(Lb); //创建Lb表 
	InitList_Sq(Lc); //创建Lc表 
	int a[] = {1, 1, 3, 4, 7, 8, 9};
	int b[] = {1, 2, 5, 7, 8, 8, 9};
	for(int i = 0; i < 7; i++) //为La表赋值 
	{
		ListInsert_Sq(La, i+1, a[i]);
	}
	for(int i = 0; i < 7; i++) //为Lb表赋值 
	{
		ListInsert_Sq(Lb, i+1, b[i]);
	}
	merge(La, Lb, Lc); //合并La表和Lb表 
	printf("La表为：\n");
	print(La); //输出La表 
	printf("Lb表为：\n");
	print(Lb); //输出Lb表 
	printf("Lc表为：\n");
	print(Lc); //输出合并后的顺序表 
	return 0;
}
