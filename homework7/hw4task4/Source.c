//4. * Создать библиотеку функций для работы с графами.
//Рощупкин

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
	int active[N]; // состояния вершин (просмотрена или не просмотрена)
	int Route[N], Peak[N];
	int i, j, min, kMin;
	// В начале программы присваиваем начальные значения,
	// Если =1 то вершина еще не просмотрена
	for (i = 0; i < N; i++)
	{
		active[i] = 1;
		Route[i] = W[0][i];
		Peak[i] = 0;
	}
	// сразу помечаем, что вершина A(0) просмотрена,
	// с нее начинается маршрут
	active[0] = 0;
	for (i = 0; i < N - 1; i++)
	{
		// среди активных вершин
		// ищем вершину с минимальным соответствующим значением в массиве
		// R и проверяем, не лучше ли ехать через нее:
		system("cls");
		printMatrix(W);
		printInfo(Peak, Route);
		// system("pause");
		min = MaxInt;
		for (j = 0; j < N; j++)
			if (active[j] == 1 && Route[j] < min)
			{
				min = Route[j]; // Минимальный маршрут
				kMin = j; // Номер вершины с минимальным маршрутом
			}
		active[kMin] = 0; // Просмотрели эту точку
		// Проверка маршрут через вершину kMin
		// Есть ли путь, более короткий
		for (j = 0; j < N; j++)
			// Если текущий путь в вершину J (R[j],
			// больше чем путь из найденной вершины(R[kMin]+
			// путь из этой вершины W[kMin][j], то
			if (Route[j] > Route[kMin] + W[j][kMin] &&
				W[j][kMin] != MaxInt && active[j] == 1)
			{
				// мы запоминаем новое расстояние
				Route[j] = Route[kMin] + W[j][kMin];
				// и запоминаем, что можем добраться туда более
				// коротким путем в массиве P
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
	int W[N][N]; // Весовая матрица
	load(W);
	Deixtra(W);
	FloydWarshal(W);
	printf("\n");
	printMatrix(W);
	return 0;
}