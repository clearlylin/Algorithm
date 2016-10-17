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


static void merge(int a[], int b1, int l1, int b2, int l2)
{
	int* buf = (int*)malloc(sizeof(int) * (l1 + l2));
	int i = b1, j = b2, k = 0;
	while(i < b1 + l1 && j < b2 + l2) {
		if(a[i] > a[j])
			buf[k++] = a[j++];
		else if(a[i] < a[j])
			buf[k++] = a[i++];
		else {
			buf[k++] = a[i++];
			buf[k++] = a[j++];
		}
	}
	for(int i = 0; i < l1 + l2; ++i)
		a[begin++] = buf[i];
	free(buf);
}

void mergeSort(int a[], int size)
{

}

