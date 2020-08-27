//1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран.
//Рощупкин
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

void main()
{
    int i, j, k, n;
    FILE* f;
    int** arr;
    printf("array.txt:\n");
    

    f = fopen("array.txt", "r");
    fscanf(f, "%d", &n);
    arr = (int**)malloc(n * sizeof(int));
    for (i = 0; i < n; ++i)
    {
        arr[i] = malloc(n * sizeof(int));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            fscanf(f, "%d", &arr[i][j]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%d  ", arr[i][j]);

        printf("\n");

        fclose(f);
    }
}