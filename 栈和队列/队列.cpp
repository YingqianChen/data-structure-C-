/*由计算机随机产生20个100以内的随机整数。分别建立三个队列（顺序或链式）Q1、Q2、Q3，
分别存放能被3整除的随机数、被3整除余1的随机数和被3整除余2的随机数。
最后，输出三个队列中的随机数。（需要指出每个队列的元素个数）*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int QElemType;
typedef int Status;
typedef struct
{
	QElemType *base;
	int front;
	int rear;
} CirSeQueue;
Status InitQueue(CirSeQueue &sq)
{
	sq.base = (QElemType *)malloc(MAXSIZE *sizeof(QElemType));
	if(!sq.base)
	{
		exit(OVERFLOW);
	}
	sq.front = sq.rear = 0;
	return OK;
}
Status EmptyQueue(CirSeQueue sq)
{
	if(sq.front == sq.rear)
	{
		return TRUE;
	}
	return FALSE;
}
int QueueLength(CirSeQueue sq)
{
	return(sq.rear - sq.front + MAXSIZE) % MAXSIZE;
}
Status EnQueue(CirSeQueue &sq, QElemType e)
{
	if((sq.rear + 1) == sq.front)
	{
		return ERROR;
	}
	sq.base[sq.rear] = e;
	sq.rear = (sq.rear + 1) % MAXSIZE;
	return OK;
}
Status DeQueue(CirSeQueue &sq, QElemType &e)
{
	Status EmptyQueue(CirSeQueue sq); 
	if(EmptyQueue(sq))
	{
		return ERROR;
	}
	e = sq.base[sq.front];
	sq.front = (sq.front + 1) % MAXSIZE;
	return OK;
}
void conversion(CirSeQueue &sq, int x, int y, QElemType *a)
{
	Status EnQueue(CirSeQueue &sq, QElemType e);
	int i;
	for(i = 0; i < 20; i++)
	{
		if(a[i] % x == y)
		{
			EnQueue(sq, a[i]);
		}
	}
}
void PrintQueue(CirSeQueue sq)
{
	int QueueLength(CirSeQueue sq);
	Status DeQueue(CirSeQueue &sq, QElemType &e);
	int i, n;
	QElemType e;
	n = QueueLength(sq);
	for(i = 0; i < n; i++)
	{
		DeQueue(sq, e);
		printf("%d ", e);
	}
	printf("\n");
}
int main()
{
	Status InitQueue(CirSeQueue &sq);
	void conversion(CirSeQueue &sq, int x, int y, QElemType *a);
	void PrintQueue(CirSeQueue sq);
	int a[20], i;
	CirSeQueue Q1, Q2, Q3;
	printf("生成20个100以内的随机整数为：\n"); 
	for(i = 0; i < 20; i++)
	{
		a[i] = rand() % 100;
		printf("%d ", a[i]);
	}
	printf("\n");  
	InitQueue(Q1);
	InitQueue(Q2);
	InitQueue(Q3);
	conversion(Q1, 3, 0, a);
	conversion(Q2, 3, 1, a);
	conversion(Q3, 3, 2, a);
	printf("能被3整除的随机整数为：\n"); 
	PrintQueue(Q1);
	printf("能被3整除余1的随机整数为：\n"); 
	PrintQueue(Q2);
	printf("能被3整除余2的随机整数为：\n"); 
	PrintQueue(Q3);
	return 0;
}
