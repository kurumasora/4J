#include <stdio.h>

void hanoi_move(int disk_id, int from_peg, int to_peg, int* count)
{
    if (disk_id > 1)
    {
        hanoi_move(disk_id - 1, from_peg, 6 - from_peg - to_peg, count);//開始軸から中間軸の移動
        
    }
    printf("%d %d %d\n", disk_id, from_peg, to_peg);
    (*count)++;
    if (disk_id > 1)
    {
        hanoi_move(disk_id - 1, 6 - from_peg - to_peg, to_peg, count);//中間軸から目的軸への移動
        
    }
    
}

int main()
{
    int count = 0;
    int n = 0;
    printf("n?:");
    scanf("%d", &n);
    hanoi_move(n, 1, 3, &count);
    printf("%d\n", count);
    return 0;
}