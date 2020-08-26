//2. Переписать программу, реализующую двоичное дерево поиска.
//а) Добавить в него обход дерева различными способами;
//б) Реализовать поиск в двоичном дереве поиска;
//в)* Добавить в программу обработку командной строки, с помощью которой можно указывать, из какого файла считывать данные, каким образом обходить дерево.
#define _CRT_SECURE_NO_WARNINGS
//Рощупкин
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef int T;
typedef struct Node {
	int key;
	T data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
} Node;
// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node* root) {
	if (root)
	{
		printf("%d", root->data);
		if (root->left || root->right)
		{
			printf("(");
			if (root->left)
				printTree(root->left);
			else
				printf("NULL");
			printf(",");
			if (root->right)
				printTree(root->right);
			else
				printf("NULL");
				printf(")");
		}
	}
}
// Создание нового узла
Node* getFreeNode(T value, Node* parent) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	tmp->data = value;
	tmp->parent = parent;
	return tmp;
}
// Вставка узла
void insert(Node** head, int value) {
	Node* tmp = NULL;
	if (*head == NULL)
	{
		*head = getFreeNode(value, NULL);
		return;
	}
	tmp = *head;
	while (tmp)
	{
		if (value > tmp->data)
		{
			if (tmp->right)
			{
				tmp = tmp->right;
				continue;
			}
			else
			{
				tmp->right = getFreeNode(value, tmp);
				return;
			}
		}
		else if (value < tmp->data)
		{
			if (tmp->left)
			{
				tmp = tmp->left;
				continue;
			}
			else
			{
				tmp->left = getFreeNode(value, tmp);
				return;
			}
		}
		else
		{
			exit(2); // дерево построено неправильно
		}
	}
}
void preOrderTravers(Node * root) {
	if (root) {
		printf("%d ", root->data);
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}
void postOderTravers(Node* root)
{
	if (root == NULL)
		return;
	postOderTravers(root->left);
	postOderTravers(root->right);
	if (root)
		printf("%d ", root->data);
}
void inOderTravers(Node* root)
{
	if (root == NULL)
		return;
	inOderTravers(root->left);
	if (root)
		printf("%d ", root->data);
	inOderTravers(root->right);
}
Node* search(Node* root, int value)
{
	// Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
	if ((root == NULL) || (root->data = value)) {
		printf("\nThe element was found: %d ", root->data);
		return root;
	}
	// Поиск нужного узла
	if (value < root->data)
		return search(root->left, value);
	else return search(root->right, value);
}
int main()
{
	Node* Tree = NULL;
	char fileName[100];
	printf("Enter the file`s name (I recomend to enter \"data.txt\"):\n");
	scanf("%[^\n]%*c", fileName);
	FILE* file = fopen(fileName, "r");
	if (file == NULL)
	{
		puts("Can't open file!");
		exit(1);
	}
	else
	{
		puts("File exists!\n");
	}
	int count;
	fscanf(file, "%d", &count);
	int i;
	for (i = 0; i < count; i++)
	{
		int value;
		fscanf(file, "%d", &value);
		insert(&Tree, value);
	}
	printTree(Tree);
	int q = 1;
	printf("\nChoose the method of travers:\n");
	while (q == 1) {
		printf("\n1 - PreOrder 2 - PostOrder 3 - InOrder 0 - Exit\n");
		int choise;
		scanf_s("%d", &choise);
		switch (choise)
		{
		case 1:
			printf("\nPreOrderTravers:");
			preOrderTravers(Tree);
			break;
		case 2:
			printf("\nPostOrderTravers:");
			postOderTravers(Tree);
			break;
		case 3:
			printf("\nInOrderTravers:");
			inOderTravers(Tree);
			break;
		case 0:
			q = 0;
			break;
		default:
			break;
		}
	}
	
	search(Tree, 10);
	return 0;
}
