#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"


int Numbers_count(char* filename) //count numbers from txt file
{
	FILE* fin;
	fin = fopen(filename, "r");
	int Number_count = 0; // strings counter
	while (!feof(fin))
	{
		if (fgetc(fin) == ' ') Number_count++;
	}
	Number_count++;
	fclose(fin);
	return Number_count;
}

int length_of_number(int n) //count amount of figures in number
{
	int k = 0;
	if (n < 0) {
		n = n * (-1);
		k = 1;
	}
	if (n / 10 == 0)
		return 1;
	else
	{

		while (n > 0)
		{

			n = n / 10;
			k++;

		}
		return k;
	}

}

void ReadMassiv(char* filename, int* Massiv, int N) //scan data from txt file to Massiv
{
	FILE* fin;
	fin = fopen(filename, "r");
	for (int i = 0; i < N; i++) {
		int a;
		fscanf(fin, "%d ", &a);
		Massiv[i] = a;
	}
	fclose(fin);
}

tree* ReadTree(char* filename, int* Massiv, int* i) //write data from Massiv to tree
{
	int p, p_l, p_r;
	p = Massiv[*i];
	p_l = Massiv[*i + 1];
	p_r = Massiv[*i + 2];
	tree* t;
	t = malloc(sizeof(tree));
	t->number = p;
	t->left = NULL;
	t->right = NULL;
	if (p_l != 0) {
		*i = *i + 3;
		t->left = ReadTree(filename, Massiv, i);
		if (p_r != 0) {
			*i = *i + 3;
			t->right = ReadTree(filename, Massiv, i);

		}
	}
	else if (p_r != 0) {
		*i = *i + 3;
		t->right = ReadTree(filename, Massiv, i);
	}
	return t;
}

int** fill_array(int f, int high) //create array and fill it with "-1"
{
	high = high * 2; //we need to write matrix and height in this massiv
	int** Massiv = malloc(high * sizeof(int*));
	for (int i = 0; i < high; i++) {
		Massiv[i] = malloc(f * sizeof(int));
		for (int y = 0; y < f; y++) {
			Massiv[i][y] = -1;
		}
	}
	return Massiv;
}

int Tree_Height(tree* tr) // count height of tree
{
	int l, r, e;
	if (tr != NULL) {
		l = (tr->left != NULL) ? Tree_Height(tr->left) : 0;
		r = (tr->right != NULL) ? Tree_Height(tr->right) : 0;
		if (l > r) e = l + 1;
		else e = r + 1;
		return e;
	}
	return 0;
}

void PrintTree(int** Massiv, tree* Res, int y, int* x) //nodes and heights of nodes are written to an array
{
	if (Res->left != NULL) PrintTree(Massiv, Res->left, y +1, x);
	Massiv[y * 2 + 1][*x] = abs(Tree_Height(Res->left)- Tree_Height(Res->right));
	Massiv[y * 2][*x] = Res->number;
	*x = *x + 1;
	if (Res->right != NULL) PrintTree(Massiv, Res->right, y+1 , x);

}



void Print_Massiv(int** Massiv, int columns, int lines) //print array in console
{
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			if (i % 2 != 1) {
				if (Massiv[i][j] == -1) {
					printf("  ");
				}
				else printf("%d", Massiv[i][j]);
			}
			else {
				if (Massiv[i][j] == -1) {
					printf("  ");
				}
				else printf("(%d)", Massiv[i][j]);
			}
		}
		printf("\n");
	}
}
