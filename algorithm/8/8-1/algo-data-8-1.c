#include <stdio.h>
#include <stdlib.h>

int BinarySearch(int n, int value[], int key)
{
    int left = 0;
    int right = n-1;
    
   

    while (left <= right)
    {
        int mid = (right + left) / 2;
        if (value[mid] == key)
        {
            return mid;
        }
        else if (key < value[mid])
        {
            right = mid-1;//midは除外するため
        }
        else
        {
            left = mid+1;//midは除外するため
        }


    }
    return -1;
}

int main()
{
    int n = 0;
    int x = 0;
    printf("n?:");
    scanf("%d", &n);
    int *value = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value[i]);
    }
    printf("k?:");
    int k = 0;
    scanf("%d", &k);
    int index = BinarySearch(n, value, k);//配列の添え字をreturn

    if (index > -1)
    {
        printf("Found: %d %d\n", index, k);
    }
    else if (index == -1)
    {
        printf("Not Found: %d\n", k);
    }
    free(value);
    return 0;
}
