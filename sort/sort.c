#include "sort.h"

#include <stdlib.h>

void insertSort(int a[], int size)
{
	int i = 1, j, tmp;
	for(; i < size; ++i) {
		tmp = a[i];
		j = i - 1;
		while(a[j] > tmp) {
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = tmp;
	}
}

void selectSort(int a[], int size)
{
	int i = 0, j;
	int t, index;
	for(; i < size; ++i) {
		t = a[0];
		index = 0;
		for(j = 1; j < size - i; ++j)
			if(a[j] > t) {
				t = a[j];
				index = j;
			}
		a[index] = a[j - 1];
		a[j - 1] = t;
	}
}

void bubleSort(int a[], int size)
{
	int i = 0, j, t, change;
	for(; i < size; ++i){
		change = 0;
		for(j = 1; j < size - i; ++j)
			if (a[j - 1] > a[j]) {
				t = a[j];
				a[j] = a[j - 1];
				a[j - 1] = t;
				change = 1;
			}
		if (change == 0)
			break;
	}
}

static void fSort(int a[], int begin, int end)
{
	if (end <= begin)
		return;
	int t = a[begin];
	int i = begin, j = end;
	while(i < j) {
		while(a[j] >= t && j > i)
			--j;
		a[i++] =  a[j];
		while(a[i] < t && i < j)
			++i;
		a[j] = a[i];
	}
	a[j] = t;
	fSort(a, begin, j - 1);
	fSort(a, j + 1, end);
}

void fastSort(int a[], int size)
{
	fSort(a, 0, size - 1);
}


void shellSort(int a[], int size)
{
	int step = size / 2, i, t, j;
	for(; step >= 1; --step)
		for(i = step ; i < size; i += step) {
			t = a[i];
			j = i - step;
			while(j >= 0 && a[j] > t) {
				a[j + step] = a[j];
				j -= step;
			}
			a[j + step] = t;
		}
}


static void merge(int a[], int low, int mid, int high)
{
	int *buf = (int*)malloc(sizeof(int) * (high - low + 1));
	int i = low, j = mid + 1, k = 0;
	while(i <= mid && j <= high) {
		if(a[i] < a[j])
			buf[k++] = a[i++];
		else
			buf[k++] = a[j++];
	}
	while(i <= mid)
		buf[k++] = a[i++];

	while(j <= high)
		buf[k++] = a[j++];

	for(i = 0; i < k; ++i)
		a[low++] = buf[i];
	free(buf);
}

static void mergetSort_(int a[], int begin, int end)
{
	if (begin < end) {
		int mid = (begin + end) / 2;
		mergetSort_(a, begin, mid);
		mergetSort_(a, mid + 1, end);
		merge(a, begin, mid, end);
	}
}

void mergeSort(int a[], int size)
{
	mergetSort_(a, 0, size - 1);
}


static void heapAjust(int a[], int low, int size)
{
	int lf = 2 * low + 1, tmp;
	for(; lf < size; lf = 2 * lf + 1) {
		if (lf < size - 1 && a[lf + 1] > a[lf])
			++lf; //right bigger than left.
		if (a[low] < a[lf]) {
			//change value, check lf;
			tmp = a[low];
			a[low] = a[lf];
			a[lf] = tmp;
			low = lf;
		}
		else break;
	}
}

void heapSort(int a[], int size)
{
	int i = size / 2 - 1, t;
	for(; i >= 0; --i)
		heapAjust(a, i, size);
	for(i = size - 1; i > 0; --i) {
		t = a[0];
		a[0] = a[i];
		a[i] = t;
		heapAjust(a, 0, i);
	}
}

