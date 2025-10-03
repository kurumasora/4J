
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
  algo-data-13-1.c
  Heapsort implementation that counts:
    - dhc: number of calls to downheap
    - sc : number of swaps
  Constraints:
    - No switch
    - No unconditional-true loops (while(1), for(;;))
    - Braces for single-statement blocks as well
    - No global variables
  Note:
    - On macOS/BSD, libc exposes a function named `heapsort`. To avoid a
      name clash, this implementation uses the function name `heap_sort`.
*/

static void swap_int(int *a, int *b, long long *sc) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    (*sc)++;
}

static void downheap(int *arr, int start, int heap_size, long long *dhc, long long *sc) {
    (*dhc)++;

    int parent = start;
    bool moved = true;
    while (moved) {
        moved = false;
        int left = 2 * parent + 1;
        int right = left + 1;
        int largest = parent;

        if (left < heap_size) {
            if (arr[left] > arr[largest]) {
                largest = left;
            }
        }

        if (right < heap_size) {
            if (arr[right] > arr[largest]) {
                largest = right;
            }
        }

        if (largest != parent) {
            swap_int(&arr[parent], &arr[largest], sc);
            parent = largest;
            moved = true;
        }
    }
}

static void build_max_heap(int *arr, int n, long long *dhc, long long *sc) {
    if (n <= 1) {
        return;
    }
    for (int i = (n - 2) / 2; i >= 0; i--) {
        downheap(arr, i, n, dhc, sc);
    }
}

static void heap_sort(int *arr, int n, long long *dhc, long long *sc) {
    build_max_heap(arr, n, dhc, sc);
    for (int end = n - 1; end > 0; end--) {
        swap_int(&arr[0], &arr[end], sc);
        downheap(arr, 0, end, dhc, sc);
    }
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    if (n < 0) {
        return 0;
    }
    if (n > 10000) {
        return 0;
    }

    int *a = (int *)malloc(sizeof(int) * (n > 0 ? n : 1));
    if (a == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            return 0;
        }
    }

    long long dhc = 0;
    long long sc = 0;

    heap_sort(a, n, &dhc, &sc);

    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i + 1 < n) {
            printf(" ");
        }
    }
    printf("\n");
    printf("%lld\n", dhc);
    printf("%lld\n", sc);

    free(a);
    return 0;
}

