

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TEXT_LEN 1024

/* 改行文字を削除するヘルパー関数 */
void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/* Nextテーブル（部分一致テーブル）を作成する関数 */
void create_next_table(const char *pattern, int m, int *next) {
    int len = 0; // 直前の最長接頭辞の長さ
    next[0] = 0; // 最初の文字の次は常に0
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            next[i] = len;
            i++;
        } else {
            if (len != 0) {
                // 一つ前のインデックスの長さに戻る
                len = next[len - 1];
            } else {
                next[i] = 0;
                i++;
            }
        }
    }
}

/* KMP法による検索関数 */
int kmp_search(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    // パターンが空の場合は0を返す（仕様によるが、ここでは便宜上0とする）
    if (m == 0) return 0;

    // Nextテーブルのメモリ確保
    int *next = (int *)malloc(sizeof(int) * m);
    if (next == NULL) {
        fprintf(stderr, "メモリ確保エラー\n");
        exit(1);
    }

    // Nextテーブルの作成
    create_next_table(pattern, m, next);

    int i = 0; // テキストのインデックス
    int j = 0; // パターンのインデックス

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            // パターンが見つかった場合
            free(next);
            return i - j; // 開始位置（添字）を返す
        } else if (i < n && pattern[j] != text[i]) {
            // 不一致の場合
            if (j != 0) {
                j = next[j - 1];
            } else {
                i++;
            }
        }
    }

    free(next);
    return -1; // 見つからなかった場合
}

int main(void) {
    char text[MAX_TEXT_LEN];
    char pattern[MAX_TEXT_LEN];

    // テキストの入力 [cite: 4]
    printf("テキストを入力してください (最大1024文字): ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }
    remove_newline(text);

    // パターンの入力 [cite: 4]
    printf("パターンを入力してください: ");
    if (fgets(pattern, sizeof(pattern), stdin) == NULL) {
        return 1;
    }
    remove_newline(pattern);

    // 検索実行
    int result = kmp_search(text, pattern);

    // 結果出力 [cite: 6]
    if (result != -1) {
        printf("パターンに合致するテキストの開始位置: %d\n", result);
    } else {
        printf("パターンは見つかりませんでした。\n");
    }

    return 0;
}