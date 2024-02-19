#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INI_MAX 999
typedef struct
{
	int weight;
	int parent, lchild, rchild;
} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
void Select(HuffmanTree &HT, int a, int &s1, int &s2)
{
	int w1, w2, i;
    w1 = w2 = INI_MAX;
    for(i = 1; i<= a; i++)
    {
    	if(HT[i].parent != 0)
    	{
    		continue;
		}
		if(HT[i].weight < w1)
		{
			s2 = s1;
			w2 = w1;
			s1 = i;
			w1 = HT[i].weight;
		}
		else if(HT[i].weight >= w1 && HT[i].weight < w2)
		{
			s2 = i;
			w2 = HT[i].weight;
		}
	}
}
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int i, j, m, s1, s2, start;
	char *cd;
	unsigned int c, f;
	if(n <= 1)
	{
		return;
	}
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));
	for(i = 1; i <= n; i++)
	{
		HT[i].weight = w[i-1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for(i = n + 1; i <= m; i++)
	{
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for(i = n + 1; i <= m; i++)
	{
		Select(HT, i-1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n+1) * sizeof(char *));
	cd = (char *)malloc(n * sizeof(char));
	cd[n-1] = '\0';
	for(i = 1; i <= n; ++i)
	{
		start = n-1;
		for(c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
		{
			if(HT[f].lchild == c)
			{
				cd[--start] = '0';
			}
			else
			{
				cd[--start] = '1';
			}
		}
		HC[i] = (char *)malloc((n-start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}
void PrintHuffmanCode(HuffmanCode HC, int *w, int n)
{
    for(int i = 1; i <= n; i++)
    {
    	printf("Ȩֵ��%d ���������룺%s\n", w[i-1], HC[i]);
	}
}
int main()
{
	int w[] = {2, 8, 7, 6, 5, 9, 3};
	int n = 7;
	HuffmanTree ht;
	HuffmanCode hc;
	HuffmanCoding(ht, hc, w, n);
	PrintHuffmanCode(hc, w, n);
	return 0;
}
