#include <stdio.h>

/* 解の個数をカウントするグローバル変数 */
int count = 0;

/* 盤面の初期化 */
void init_board(int board[8][8])
{
    int row;
    int col;

    row = 0;
    while (row < 8)
    {
        col = 0;
        while (col < 8)
        {
            board[row][col] = 0;
            col++;
        }
        row++;
    }
}

/* * 盤面と解の番号を出力する関数 
 * 演習5-9の機能を実装、黒(1)と白(0)で出力 [cite: 4]
 * 数値の間は空白で区切り、解の番号(Y)を出力 
 */
void print_board(int queen_position[8])
{
    int r;
    int c;

    for (r = 0; r < 8; r++)
    {
        for (c = 0; c < 8; c++)
        {
            if (queen_position[r] == c)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }

            /* 数値の間は空白文字で区切る  */
            if (c < 7)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    /* 解の番号を出力 */
    printf("%d\n", count);
    /* 盤面の出力は区切る  */
    printf("------------------\n");
}

/* 盤上の任意の点から縦横斜めにdを加える */
void change_board(int board[8][8], int row, int col, int d)
{
    int i;
    int j;

    i = 0;
    while (i < 8)
    {
        board[row][i] += d;
        board[i][col] += d;
        i++;
    }

    i = row;
    j = col;
    while (i < 8 && j < 8)
    {
        board[i][j] += d;
        i++;
        j++;
    }

    i = row;
    j = col;
    while (i >= 0 && j >= 0)
    {
        board[i][j] += d;
        i--;
        j--;
    }

    i = row;
    j = col;
    while (i < 8 && j >= 0)
    {
        board[i][j] += d;
        i++;
        j--;
    }

    i = row;
    j = col;
    while (i >= 0 && j < 8)
    {
        board[i][j] += d;
        i--;
        j++;
    }
}

/* 再帰的にクイーンを配置する関数 */
void set_queen(int queen_position[8], int board[8][8], int row)
{
    int col;

    /* 8行目まで配置できたら解として出力 */
    if (row == 8)
    {
        count++;
        print_board(queen_position);
        return;
    }

    /* チェスの盤上に座布団を重ねていくようなイメージ、三次元的な処理 */
    for (col = 0; col < 8; col++)
    {
        if (board[row][col] == 0)
        {
            /* board[row][col]の位置にクイーンを配置 */
            queen_position[row] = col;
            /* 縦横斜めを使用禁止にするためおけない場所に座布団を+1 */
            change_board(board, row, col, 1);
            /* 次の行のクイーンの位置を決める */
            set_queen(queen_position, board, row + 1);
            /* 重ねた座布団を-1 */
            change_board(board, row, col, -1);
        }
    }
}

int main(void)
{
    int queen_position[8];
    int board[8][8];

    init_board(board);
    set_queen(queen_position, board, 0);

    return 0;
}