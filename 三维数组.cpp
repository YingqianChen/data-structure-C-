/* 建立一个三维数组，实现数组在以行序优先的存储结构，
   各维的长度由用户从键盘输入，存入维长数组bounds[]。
   由n维数组映像函数公式(Loc(Aijk)=Loc(a000)+(i×m×n+j×n+k)×d)
   计算出映像函数中各常量值(m×n, n, 1)Ci，存入映像函数常量数组constants[]，
   为实际计算数组元素的地址做准备。数组的值由循环赋值完成，
   最后按结构输出数组元素的值，并释放该数组。*/
#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#define MAX_ARRAY_DIM 8
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define UNDERFLOW -1
typedef int ElemType;
typedef int Status;
typedef struct
{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
} Array;
Status InitArray(Array &A, int dim, ...)
{
	int i, elemtotal;
	if(dim < 1 || dim > MAX_ARRAY_DIM)
	{
		return ERROR;
	}
	A.dim = dim;
	A.bounds = (int *)malloc(dim * sizeof(int));
	if(!A.bounds)
	{
		exit(OVERFLOW);
	}
	elemtotal = 1;
	va_list ap;
	va_start(ap, dim);
	for(i = 0; i < dim; ++i)
	{
		A.bounds[i] = va_arg(ap, int);
		if(A.bounds [i] < 0)
		{
			return UNDERFLOW;
		}
		elemtotal = elemtotal * A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if(!A.base)
	{
		exit(OVERFLOW);
	}
	A.constants = (int *)malloc(dim * sizeof(int));
	A.constants[dim - 1] = 1;
	for(i = dim - 2; i >= 0; --i)
	{
		A.constants[i] = A.bounds[i+1] * A.constants[i+1];
	}
	return OK;
}
Status DestroyArray(Array &A)
{
	if(!A.base)
	{
		return ERROR;
	}
	free(A.base);
	A.base = NULL;
	if(!A.bounds)
	{
		return ERROR;
	}
	free(A.bounds);
	A.bounds = NULL;
	if(!A.constants)
	{
		return ERROR;
	}
	free(A.constants);
	A.constants = NULL;
	return OK;
}
Status Locate(Array A, va_list ap, int &off)
{
	off = 0;
	for(int i = 0; i < A.dim; ++i)
	{
		int ind = va_arg(ap, int);
		if(ind < 0 || ind >= A.bounds[i])
		{
			return OVERFLOW;
		}
		off += A.constants[i] * ind;
	}
	return OK;
}
Status Value(Array A, ElemType &e, ...)
{
	Status result;
	int off;
	va_list ap;
	va_start(ap, e);
	if((result = Locate(A, ap, off)) <= 0)
	{
		return result;
	}
	e = *(A.base + off);
	return OK;
}
Status Assign(Array &A, ElemType e, ...)
{
	Status result;
	int off;
	va_list ap;
	va_start(ap, e);
	if((result = Locate(A, ap, off)) <= 0)
	{
		return result;
	}
	*(A.base + off) = e;
	return OK;
}
int main()
{
	Array A;
	ElemType e;
	int i, j, k, dim = 3, bounds[3];
	printf("请输入三维数组的各维长度：");
	scanf("%d %d %d", &bounds[0], &bounds[1], &bounds[2]);
	InitArray(A, dim, bounds[0], bounds[1], bounds[2]);
	printf("A.bounds = ");
	for(i = 0; i < dim; i++) //输出bounds 
	{
		printf("%d ", *(A.bounds + i));
	}
	printf("\nA.constants = ");
	for(i = 0; i < dim; i++) //输出constants 
	{
		printf("%d ", *(A.constants + i));
	}
	printf("\n%d页%d行%d列矩阵元素如下：\n", bounds[0], bounds[1], bounds[2]);
	for(i = 0; i < bounds[0]; i++)
	{
		for(j = 0; j < bounds[1]; j++)
		{
			for(k = 0; k < bounds[2]; k++)
			{
				e = rand() % 50;
				Assign(A, e, i, j, k); //将0-50的随机数随机赋给A[i][j][k] 
				printf("A[%d][%d][%d] = %d\n", i, j, k, e);
			}
		}
	}
	DestroyArray(A); //释放数组 
	return 0;
}
