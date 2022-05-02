/* 输入一个稀疏矩阵A，建立 A的三元组顺序表
   求A的转置矩阵B
   求矩阵A和B的和，C */ 
#include<stdio.h>
#define MAXSIZE 12500
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;
typedef struct
{
	int i, j;
	ElemType e;
} Triple;
typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
} TSMatrix;
Status CreateSMatrix(TSMatrix &M)
{
	printf("请输入矩阵的行数，列数，非零元素数：");
	scanf("%d,%d,%d", &M.mu, &M.nu, &M.tu);
	for(int i = 1; i <= M.tu; i++)
	{
		printf("请按行序顺序输入第%d个非零元素所在的行（1~%d)，列(1~%d)，元素值：", i, M.mu, M.nu);
		scanf("%d,%d,%d", &M.data[i].i, &M.data[i].j, &M.data[i].e);
	}
	return OK;
}
void DestroySMatrix(TSMatrix &M)
{
	for(int i = 1; M.data[i].i <= M.tu; i++) 
	{
		M.data[i].i = 0;
		M.data[i].j = 0;
		M.data[i].e = 0;
	}
	M.mu = 0; M.nu = 0; M.tu = 0;
}
Status PrintSMatrix(TSMatrix M)
{
	printf("稀疏矩阵对应的三元组表为：\n%d行%d列%d个非零元素\n行  列  元素值\n", M.mu, M.nu, M.tu);
	for(int i = 1; i <= M.tu; i++)
	{
		printf("%2d%4d%8d", M.data[i].i, M.data[i].j, M.data[i].e);
		printf("\n");
	}
	return OK;
}
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
	if(M.mu != N.mu || M.nu != N.nu) //矩阵相加的条件 
	{
		return ERROR;
	}
	int i = 1, j = 1, k = 1;
	Q.mu = M.mu;
	Q.nu = M.nu;
	Q.tu = 0;
	if(M.tu == 0 && N.tu == 0)
	{
		return OK;
	}
	while(i <= M.tu && j <= N.tu)
	{
		if(M.data[i].i < N.data[j].i || (M.data[i].i == N.data[j].i && M.data[i].j < N.data[j].j))
		{
			Q.data[k].i = M.data[i].i;
			Q.data[k].j = M.data[i].j;
			Q.data[k].e = M.data[i].e;
			i++; k++; Q.tu++;
		}
		else if(M.data[i].i > N.data[j].i || (M.data[i].i == N.data[j].i && M.data[i].j > N.data[j].j))
		{
			Q.data[k].i = N.data[j].i;
			Q.data[k].j = N.data[j].j;
			Q.data[k].e = N.data[j].e;
			j++; k++; Q.tu++;
		}
		else if(M.data[i].i == N.data[j].i && M.data[i].j == N.data[j].j)
		{
			if(M.data[i].e + N.data[j].e) //两元素之和不为0 
			{
				Q.data[k].e = M.data[i].e + N.data[j].e;
				Q.data[k].i = M.data[i].i;
				Q.data[k].j = M.data[i].j;
				Q.tu++;
				k++;
			}
			i++; j++;
		}
	}
	while(i <= M.tu) //若M矩阵存在剩余元素，将其添加到Q中 
	{
		Q.data[k].i = M.data[i].i;
		Q.data[k].j = M.data[i].j;
		Q.data[k].e = M.data[i].e;
		i++; k++;
		Q.tu++;
	}
	while(j <= N.tu) //若N矩阵存在剩余元素，将其添加到Q中 
	{
		Q.data[k].i = N.data[j].i;
		Q.data[k].j = N.data[j].j;
		Q.data[k].e = N.data[j].e;
		j++; k++;
		Q.tu++;
	}
	return OK;
}
Status TransposeSMatrix(TSMatrix M, TSMatrix &T)//一般转置 
{
	int p, q, col;
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if(T.tu)
	{
		q = 1;
	for(col = 1; col <= M.nu; ++col)
	{
		for(p = 1; p <= M.tu; ++p)
		{
			if(M.data[p].j ==  col)
			{
				T.data[q].i = M.data[p].j;
				T.data[q].j = M.data[p].i;
				T.data[q].e = M.data[p].e;
				++q;
			}
		}
	}
	}
	return OK;
}
Status FastTransposeSMatrix(TSMatrix M, TSMatrix &T)//快速转置 
{
	int p, q, col, t;
	int num[20], cpot[20];
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if(T.tu)
	{
		for(col = 1; col <= M.nu; ++col)
		{
			num[col] = 0;
		}
		for(t = 1; t <= M.tu; ++t)
		{
			++num[M.data[t].j];
		}
		cpot[1] = 1;
		for(col = 2; col <= M.nu; ++col)
		{
			cpot[col] = cpot[col - 1] + num[col - 1];
		}
		for(p = 1; p<= M.tu; ++p)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	return OK;
}
int main()
{
	TSMatrix A, B1, B2, C1, C2;
	printf("创建矩阵A：\n");
	CreateSMatrix(A);
	TransposeSMatrix(A, B1);
	FastTransposeSMatrix(A, B2);
	AddSMatrix(A, B1, C1);
	AddSMatrix(A, B2, C2);
	PrintSMatrix(A);
	printf("矩阵B1（A的转置，采用一般转置）：\n");
	PrintSMatrix(B1);
	printf("矩阵B2（A的转置，采用快速转置）：\n");
	PrintSMatrix(B2);
	printf("矩阵C1（A+B1）：\n");
	PrintSMatrix(C1);
	printf("矩阵C2（A+B2）：\n");
	PrintSMatrix(C2);
	DestroySMatrix(A);
	return 0;
}
