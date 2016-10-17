#include <stdio.h>
#include <stdlib.h>

#include "sort.h"


int main() {
    int a[] = {1,5,2,4,7,9,11,3,4,56,34,12,32,14,17,23,26,78,91};
    int len = sizeof(a)/sizeof(int);
    insertSort(a, len);
    for (int i = 0; i < len; ++i)
    	printf("%d ", a[i]);
    printf("\n%d\n", len);

    int b[] = {1,5,2,4,7,9,11,3,4,56,34,12,32,14,17,23,26,78,91};
    selectSort(b, len);
    for (int i = 0; i < len; ++i)
    	printf("%d ", b[i]);
    printf("\n%d\n", len);

    int c[] = {1,5,2,4,7,9,11,3,4,56,34,12,32,14,17,23,26,78,91};
    bubleSort(c, len);
    for (int i = 0; i < len; ++i)
    	printf("%d ", c[i]);
    printf("\n%d\n", len);

    int d[] = {1,5,2,4,7,9,11,3,4,56,34,12,32,14,17,23,26,78,91,19,29,46,58,59};
    len = sizeof(d)/sizeof(int);
    fastSort(d, len);
    for (int i = 0; i < len; ++i)
    	printf("%d ", d[i]);
    printf("\n%d\n", len);


    int e[] = {1,5,2,4,7,9,11,3,4,56,34,12,32,14,17,23,26,78,91,19,29,46,58,59};
    len = sizeof(e)/sizeof(int);
    shellSort(e, len);
    for (int i = 0; i < len; ++i)
    	printf("%d ", e[i]);
    printf("\n%d\n", len);

	return 0;
}