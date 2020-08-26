//3. * ����������� ���� ������ ��������� �� ���� ����� �����, ��������, ���������� ����� � �������
//������������ ��� ������, ���������� �� ������.
//�������� ������ � �������� ������ ������.���������� ����� �� ������ - ������ ���� ���� ������
//(�������, ���)
//��������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>

/* ��������� ��� �������� ���������� ��� ������ �������� */
typedef struct tagITEM
{
    char Surname[20], Name[20];
    int Age;
} ITEM;

/* ������ �������� �� 20 ������� */
ITEM Men[20];

/* ���������� ������� ��������� � ������� */
int Number;

/* ������� ��� ������ ���� ��������� */
void Print(void)
{
    int i;

    printf(" N  Surname              FirstName                  Age\n");
    for (i = 0; i < Number; i++)
        printf("%2i. %-20s %-20s %3i\n", i + 1, Men[i].Surname,
            Men[i].Name, Men[i].Age);
} /* End of 'Print' function */

void Search() {
    int age;
    printf("Enter needed age: ");
    scanf_s("%d", &age);
    int i;
    printf(" N  Surname              FirstName                  Age\n");
    for (i = 0; i < Number; i++)
    {
        if (Men[i].Age == age)
            printf("%2i. %-20s %-20s %3i\n", i + 1, Men[i].Surname,
                Men[i].Name, Men[i].Age);
    }
}

/* ������� ��� ���������� �������� */
void Add(void)
{
    if (Number == 19)
    {
        fprintf(stderr, "It`s impossiple to add one more item\n");
        return;
    }

    printf("Enter the surname > ");
    scanf("%s", Men[Number].Surname);
    printf("Enter the first name > ");
    scanf("%s", Men[Number].Name);
    printf("Enter the age > ");
    scanf("%i", &Men[Number].Age);

    Number++;
} /* End of 'Add' function */

/* ������� ��� �������� �������� */
void Del(void)
{
    int i;

    Print();
    printf("Enter the removing item`s number > ");
    scanf("%i", &i);
    if (i < 1 || i > Number)
    {
        fprintf(stderr, "Item with number %i doesn`t exist\n", i);
        return;
    }

    for (i--; i < Number - 1; i++)
        Men[i] = Men[i + 1];

    Number--;
} /* End of 'Del' function */

/* ������� ��� ���������� ������� � ����� */
void Save(void)
{
    FILE* F;
    int i;

    if ((F = fopen("task1.dat", "wt")) == NULL)
    {
        fprintf(stderr, "It`s impossible to open for writing 'task1.dta'\n");
        return;
    }

    fprintf(F, "%i\n", Number);
    for (i = 0; i < Number; i++)
        fprintf(F, "%s\n%s\n%i\n", Men[i].Surname, Men[i].Name, Men[i].Age);

    fclose(F);
} /* End of 'Save' function */

/* ������� ��� ������ ������� �� ����� */
void Load(void)
{
    FILE* F;
    int i;

    if ((F = fopen("task3.txt", "rt")) == NULL)
    {
        fprintf(stderr, "It`s impossiple to open 'task3.txt'\n");
        return;
    }

    fscanf(F, "%i", &Number);
    for (i = 0; i < Number; i++)
        fscanf(F, "%s%s%i", Men[i].Surname, Men[i].Name, &Men[i].Age);

    fclose(F);
} /* End of 'Load' function */

/* ������� ��� �������������� ������� �� ������� */
void Sort(void)
{
    int i, j;
    ITEM Temp;

    for (j = Number - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (strcmp(Men[i].Surname, Men[i + 1].Surname) > 0)
            {
                Temp = Men[i];
                Men[i] = Men[i + 1];
                Men[i + 1] = Temp;
            }
} /* End of 'Sort' function */

/* ����� ���� � ������ ������ ���������� ������ */
int Menu(void)
{
    int c = 0;

    while ((c < '0' || c > '7') && c != 27)
    {
        printf("0 : Exit\n"
            "1 : Add\n"
            "2 : Save\n"
            "3 : Upload\n"
            "4 : Print\n"
            "5 : Sort\n"
            "6 : Delete\n"
            "7 : Search with Age\n"
            ">");
        c = _getch();
        printf("%c\n", c);
    }
    return c;
} /* End of 'Menu' function */

/* �������� ������� */
void main(void)
{
    int Selection;

    Number = 0;
    while ((Selection = Menu()) != '0' && Selection != 27)
        switch (Selection)
        {
        case '1':
            Add();
            break;
        case '2':
            Save();
            break;
        case '3':
            Load();
            break;
        case '4':
            Print();
            break;
        case '5':
            Sort();
            break;
        case '6':
            Del();
            break;
        case '7':
            Search();
            break;
        }
} /* End of 'main' function */

/* End of 'task_1_1.c' file */