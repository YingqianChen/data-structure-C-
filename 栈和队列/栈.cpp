/*���ʽ��ֵ 
ʵ���ַ��Ƿ��ǲ���������In(c, op)
ʵ�ֱȽ�����������ȼ�����precede(o1, o2) 
ʵ���������ʽ��⺯��operate(a, op, b)
ʵ�ֱ��ʽ��ֵ����EvaluateExpression()
���������main()����������*/
#include<stdio.h>
#include<stdlib.h>
#define OK 0
#define ERROR -1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef char OPElemType;
typedef float NDElemType;
typedef float OperandType;
typedef struct
{
	OPElemType *base;
	OPElemType *top;
	int stacksize;
} SqStack_OP;
typedef struct
{
	NDElemType *base;
	NDElemType *top;
	int stacksize;
} SqStack_ND;
Status InitStack_OP(SqStack_OP &S)
{
	S.base = (OPElemType *)malloc(STACK_INIT_SIZE*sizeof(OPElemType));
	if(!S.base)
	{
		exit (OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
Status InitStack_ND(SqStack_ND &S)
{
	S.base = (NDElemType *)malloc(STACK_INIT_SIZE*sizeof(NDElemType));
	if(!S.base)
	{
		exit (OVERFLOW);
	}
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
OPElemType GetTop_OP(SqStack_OP S)
{
	OPElemType c;
	if(S.top == S.base)
	{
		return ERROR;
	}
	c = *(S.top - 1);
	return c;
}
NDElemType GetTop_ND(SqStack_ND S)
{
	NDElemType f;
	if(S.top == S.base)
	{
		return ERROR;
	}
	f = *(S.top - 1);
	return f;
}
Status Push_OP(SqStack_OP &S, OPElemType OP)
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (OPElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(OPElemType));
		if(!S.base)
		{
			exit (OVERFLOW);
		}
		S.top = S.top + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top ++= OP;
	return OK;
}
Status Push_ND(SqStack_ND &S, NDElemType ND)
{
	if(S.top - S.base >= S.stacksize)
	{
		S.base = (NDElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(NDElemType));
		if(!S.base)
		{
			exit (OVERFLOW);
		}
		S.top = S.top + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top ++= ND;
	return OK;
}
Status Pop_OP(SqStack_OP &S, OPElemType &OP)
{
	if(S.top == S.base)
	{
		return ERROR;
	}
	OP = *--S.top;
	return OK;
}
Status Pop_ND(SqStack_ND &S, NDElemType &ND)
{
	if(S.top == S.base)
	{
		return ERROR;
	}
	ND = *--S.top;
	return OK;
}
Status In(char c)
{
	if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '#')
	{
		return TRUE;
	}
	else
	return FALSE;
}
OPElemType Precede(OPElemType a, OPElemType b)
{
	if(a == '+' || a == '-')
	{
		if(b == '+' || b == '-' || b == ')' || b == '#')
		return '>';
		else
		return '<';
	}
	else if(a == '*' || a == '/')
	{
		if(b == '(')
		return '<';
		else
		return '>';
	}
	else if(a == '(')
	{
		if(b == ')')
		return '=';
		else if(b == '#')
		return '!';
		else
		return '<';
	}
	else if(a == ')')
	{
		if(b == '(')
		return '!';
		else
		return '>';
	}
	else if(a == '#')
	{
		if(b == '#')
		return '=';
		else if(b == ')')
		return '!';
		else
		return '<';
	}
}
OperandType Operate(NDElemType a, OPElemType op, NDElemType b)
{
	switch(op)
	{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			return a/b;
		default:
			printf("������ַ��Ƿ���\n");
	}
}
OperandType EvaluateExpression()
{
	SqStack_OP OPTR;
	SqStack_ND OPND;
	OPElemType c[20], s[2], r, op;
	NDElemType a, b, f;
	int i = 0, j;
	InitStack_OP(OPTR); Push_OP(OPTR, '#');
	InitStack_ND(OPND); gets(c);
	while((c[i] != '#') || (GetTop_OP(OPTR) != '#'))
	{
		for(j = 0; j < 2; j++)
		{
			s[j] = '\0';
		}
		j = 0;
		s[j] = c[i];
		if(!In(c[i]))
		{
			i++;
			if(!In(c[i]))
			{
				j++;
				s[j] = c[i];
				f = atof(s);
				Push_ND(OPND, f);
				i++;
			}
			else
			{
				f = atof(s);
				Push_ND(OPND, f);
			}
		}
		else
		{
			r = Precede(GetTop_OP(OPTR), c[i]);
			switch(r)
			{
				case '<':
					Push_OP(OPTR, c[i]);
					i++;
					break;
				case '=':
					Pop_OP(OPTR, op);
					i++;
					break;
				case '>':
					Pop_OP(OPTR, op);
					Pop_ND(OPND, b);
					Pop_ND(OPND, a);
					Push_ND(OPND, Operate(a, op, b));
					break;
			}
		}
	}
	return (GetTop_ND(OPND));
}
int main()
{
	printf("��������ʽ��������#������\n");
	printf("���Ϊ��%.2f\n", EvaluateExpression());
	return 0;
}
