#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* p1, const void* p2)
{
    return *(const int*)p1 - *(const int*)p2;
}

#define SIZE 100000

#define MAX_ARRAY_VALUE 100000

void ShellSort(int size, int mass[])
{
	int i, j, step;
	int tmp;
	int counter = 0;
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				counter++;
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
	printf("\nShell`s counter: %d", counter);
}

void quick_sort(int a[], int l, int u,int *counter)
{
	int j;
	(*counter)++;
	if (l < u)
	{
		j = partition(a, l, u,&(*counter));
		quick_sort(a, l, j - 1,&(*counter));
		quick_sort(a, j + 1, u,&(*counter));
	}
}

int partition(int a[], int l, int u,int *counter)
{
	int v, i, j, temp;
	v = a[l];
	i = l;
	j = u + 1;

	do
	{
		do
			i++;

		while (a[i] < v && i <= u);

		do
			j--;
		while (v < a[j]);

		(*counter)++;
		if (i < j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	} while (i < j);

	a[l] = a[j];
	a[j] = v;

	return(j);
}


void merge(int a[], int i1, int j1, int i2, int j2,int*counter)
{
	int temp[SIZE*2];	//array used for merging
	int i, j, k;
	i = i1;	//beginning of the first list
	j = i2;	//beginning of the second list
	k = 0;

	while (i <= j1 && j <= j2)	//while elements in both lists
	{
		(*counter)++;
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= j1)	//copy remaining elements of the first list
		temp[k++] = a[i++];

	while (j <= j2)	//copy remaining elements of the second list
		temp[k++] = a[j++];

	//Transfer elements from temp[] back to a[]
	for (i = i1, j = 0; i <= j2; i++, j++)
		a[i] = temp[j];
}
void mergesort(int a[], int i, int j,int*counter)
{
	int mid;
	(*counter)++;
	if (i < j)
	{
		mid = (i + j) / 2;
		mergesort(a, i, mid,&(*counter));		//left recursion
		mergesort(a, mid + 1, j, &(*counter));	//right recursion
		merge(a, i, mid, mid + 1, j, &(*counter));	//merging of two sorted sub-arrays
	}
}

void down_adjust(int heap[], int i,int*counter)
{
	int j, temp, n, flag = 1;
	n = heap[0];

	while (2 * i <= n && flag == 1)
	{
		j = 2 * i;	//j points to left child
		(*counter)++;
		if (j + 1 <= n && heap[j + 1] > heap[j])
			j = j + 1;
		(*counter)++;

		if (heap[i] > heap[j])
			flag = 0;
		else
		{
			temp = heap[i];
			heap[i] = heap[j];
			heap[j] = temp;
			i = j;
		}
	}
}
void create(int heap[],int*counter)
{
	int i, n;
	n = heap[0]; //no. of elements
	for (i = n / 2; i >= 1; i--)
		down_adjust(heap, i, &(*counter));
}


void heap_sort(int heap[],int size,int*counter) 
{
	int  i, last, temp;
	heap[0] = size;
	create(heap,&(*counter));

	//sorting
	while (heap[0] > 1)
	{
		//swap heap[1] and heap[last]
		last = heap[0];
		temp = heap[1];
		heap[1] = heap[last];
		heap[last] = temp;
		heap[0]--;
		down_adjust(heap, 1, &(*counter));
	}
}

void bubble_sort(int* a, int n) {
	int i, j, temp;
	int counter = 0;
	for (i = 1; i < n; ++i)
		for (j = 0; j < (n - i); ++j) {
			counter++;
			if (a[j] > a[j + 1])
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	printf("\nBubble`s counter: %d", counter);
}
void sheiker_sort(int size, int arr[])
{
	int l, r, i, k, temp;
	int counter = 0;
	k = l = 0;
	r = size - 2;

	while (l <= r)

	{
		for (i = l; i <= r; i++)
		{
			counter++;
			if (arr[i] > arr[i + 1])

			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				k = i;
			}
		}
			

		r = k - 1;
		for (i = r; i >= l; i--) {
			counter++;
			if (arr[i] > arr[i + 1])

			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				k = i;
			}
		}
			
		l = k + 1;
	}
	printf("Shaker`s counter: %d", counter);
}

int main()
{
    int array1[SIZE];
	int counter = 0;
    size_t i;
    srand(time(0));
    for (i = 0; i < SIZE; i++)
        array1[i] = rand() % (MAX_ARRAY_VALUE + 1);
	
	clock_t start, end;

	start = clock();

	quick_sort(array1, 0, SIZE - 1,&counter);
	//ShellSort(SIZE, array1);
	//mergesort(array1, 0, SIZE - 1,&counter);
	//heap_sort(array1,SIZE-1,&counter);
	//bubble_sort(array1, SIZE);
	//sheiker_sort(SIZE, array1);


	end = clock();
	printf("\n%lf\n", ((double)(end - start)) / CLOCKS_PER_SEC);
	printf("\nCounter: %d", counter);

	return 0;
}