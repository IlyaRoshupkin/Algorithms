//1. Реализовать простейшую хеш - функцию.На вход функции подается строка, на выходе сумма кодов символов.
//Рощупкин
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int  hash(char* S)
{
    int i, r = 0;
    while (*S)
    {
        r += (int)(*S);
        S++;
    }
    return r;
}
int main()
{
    char input[100];
    printf("Enter the string: ");
    scanf("%[^\n]%*c", input);
    int hashCode;
    hashCode = hash(input);
    printf("\nResult: %d", hashCode);
    return 0;
}