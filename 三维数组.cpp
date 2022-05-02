/* ����һ����ά���飬ʵ�����������������ȵĴ洢�ṹ��
   ��ά�ĳ������û��Ӽ������룬����ά������bounds[]��
   ��nά����ӳ������ʽ(Loc(Aijk)=Loc(a000)+(i��m��n+j��n+k)��d)
   �����ӳ�����и�����ֵ(m��n, n, 1)Ci������ӳ������������constants[]��
   Ϊʵ�ʼ�������Ԫ�صĵ�ַ��׼���������ֵ��ѭ����ֵ��ɣ�
   ��󰴽ṹ�������Ԫ�ص�ֵ�����ͷŸ����顣*/
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
	printf("��������ά����ĸ�ά���ȣ�");
	scanf("%d %d %d", &bounds[0], &bounds[1], &bounds[2]);
	InitArray(A, dim, bounds[0], bounds[1], bounds[2]);
	printf("A.bounds = ");
	for(i = 0; i < dim; i++) //���bounds 
	{
		printf("%d ", *(A.bounds + i));
	}
	printf("\nA.constants = ");
	for(i = 0; i < dim; i++) //���constants 
	{
		printf("%d ", *(A.constants + i));
	}
	printf("\n%dҳ%d��%d�о���Ԫ�����£�\n", bounds[0], bounds[1], bounds[2]);
	for(i = 0; i < bounds[0]; i++)
	{
		for(j = 0; j < bounds[1]; j++)
		{
			for(k = 0; k < bounds[2]; k++)
			{
				e = rand() % 50;
				Assign(A, e, i, j, k); //��0-50��������������A[i][j][k] 
				printf("A[%d][%d][%d] = %d\n", i, j, k, e);
			}
		}
	}
	DestroyArray(A); //�ͷ����� 
	return 0;
}
