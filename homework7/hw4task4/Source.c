//4. * ������� ���������� ������� ��� ������ � �������.
//��������

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define N 5
const char* filename = "task4.txt";
const int MaxInt = 20000000;
int load(int W[N][N])
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Can't open file");
		exit(1);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			int a;
			fscanf(file, "%d", &a);
			if (a == 0)
				W[i][j] = MaxInt;
			else
				W[i][j] = a;
		}
	fclose(file);
	return 0;
}
void printMatrix(int W[N][N])
{
	printf("%s", " ");
	for (int i = 0; i < N; i++)
		printf("%c(%d) ", 65 + i, i);
	printf("\n");
	for (int i = 0; i < N; i++)
	{
		printf("%c(%d)", 65 + i, i);
		for (int j = 0; j < N; j++)
			printf("%5d", (W[i][j] == MaxInt) ? 0 : W[i][j]);
		printf("\n");
	}
}
void printInfo(int P[N], int R[N])
{
	printf("P:\n");
	for (int i = 0; i < N; i++)
		printf("%c(%d) %c(%d)\n", P[i] + 65, P[i], i + 65, i);
	printf("R:\n");
	for (int i = 0; i < N; i++)
		printf("%c%10d\n", i + 65, R[i]);
}
void FloydWarshal(int W[N][N])
{
	printf("\nUsing FloydWarshal`s Method:\n");
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (W[i][k] + W[k][j] < W[i][j])
					W[i][j] = W[i][k] + W[k][j];
}
void Deixtra(int W[N][N]) {
	printf("\nUsing Deixtra`s Method:\n");
	int active[N]; // ��������� ������ (����������� ��� �� �����������)
	int Route[N], Peak[N];
	int i, j, min, kMin;
	// � ������ ��������� ����������� ��������� ��������,
	// ���� =1 �� ������� ��� �� �����������
	for (i = 0; i < N; i++)
	{
		active[i] = 1;
		Route[i] = W[0][i];
		Peak[i] = 0;
	}
	// ����� ��������, ��� ������� A(0) �����������,
	// � ��� ���������� �������
	active[0] = 0;
	for (i = 0; i < N - 1; i++)
	{
		// ����� �������� ������
		// ���� ������� � ����������� ��������������� ��������� � �������
		// R � ���������, �� ����� �� ����� ����� ���:
		system("cls");
		printMatrix(W);
		printInfo(Peak, Route);
		// system("pause");
		min = MaxInt;
		for (j = 0; j < N; j++)
			if (active[j] == 1 && Route[j] < min)
			{
				min = Route[j]; // ����������� �������
				kMin = j; // ����� ������� � ����������� ���������
			}
		active[kMin] = 0; // ����������� ��� �����
		// �������� ������� ����� ������� kMin
		// ���� �� ����, ����� ��������
		for (j = 0; j < N; j++)
			// ���� ������� ���� � ������� J (R[j],
			// ������ ��� ���� �� ��������� �������(R[kMin]+
			// ���� �� ���� ������� W[kMin][j], ��
			if (Route[j] > Route[kMin] + W[j][kMin] &&
				W[j][kMin] != MaxInt && active[j] == 1)
			{
				// �� ���������� ����� ����������
				Route[j] = Route[kMin] + W[j][kMin];
				// � ����������, ��� ����� ��������� ���� �����
				// �������� ����� � ������� P
				Peak[j] = kMin;
				printMatrix(W);
				printInfo(Peak, Route);
			}
	}
	i = N - 1;
	while (i != 0)
	{
		printf("%c ", i + 65);
		i = Peak[i];
	}
	printf("A");
}
int main(int argc, char* argv[])
{
	int W[N][N]; // ������� �������
	load(W);
	Deixtra(W);
	FloydWarshal(W);
	printf("\n");
	printMatrix(W);
	return 0;
}