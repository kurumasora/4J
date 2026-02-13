
/*
 * Project Name: algo-data-29-6
 * File Name: algo-data-29-6.c
 * Description: ランレングス法を用いた文字列の圧縮と展開
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 10005 // 最大入力長さ10000文字 + 安全マージン

// 整数の桁数を計算する補助関数
int get_digit_count(int n) {
    char buffer[20];
    sprintf(buffer, "%d", n);
    return strlen(buffer);
}

int main(void) {
    int mode;
    int input_len_param; // 入力として与えられる文字数
    char str[MAX_LEN];
    
    // 1. 入力の読み込み
    // モード (1:圧縮, 2:展開)
    if (scanf("%d", &mode) != 1) return 1;
    
    // 文字列の長さ
    if (scanf("%d", &input_len_param) != 1) return 1;
    
    // 文字列データ (空白スキップのために先頭にスペースを入れるか、scanfの特性を利用)
    if (scanf("%s", str) != 1) return 1;

    // 実際の文字列長を取得（入力値と実際のデータを確認するため）
    int actual_len = strlen(str);

    // ---------------------------------------------------------
    // モード1: 圧縮処理
    // ---------------------------------------------------------
    if (mode == 1) {
        // 圧縮後の長さを計算するための変数
        int compressed_len = 0;
        
        // ランレングス圧縮ロジック
        int count = 1;
        for (int i = 0; i < actual_len; i++) {
            // 次の文字と同じかチェック (配列外参照防止のため i < actual_len - 1)
            if (i < actual_len - 1 && str[i] == str[i+1]) {
                count++;
            } else {
                // 文字が切り替わった、または文字列の最後
                
                // 出力: 回数 + 文字 (例: 5A)
                printf("%d%c", count, str[i]);
                
                // 圧縮後の長さ計算: 数字の桁数 + 文字(1byte)
                compressed_len += get_digit_count(count) + 1;
                
                // カウントリセット
                count = 1;
            }
        }
        printf("\n"); // 1行目の出力終了

        // 2行目: 圧縮率の出力 (圧縮後 / 元データ)
        // 実行例に合わせて "M/L [圧縮後]/[元] [比率]" の形式で出力
        double ratio = (double)compressed_len / (double)actual_len;
        printf("M/L %d/%d %.3f\n", compressed_len, actual_len, ratio);
    }
    
    // ---------------------------------------------------------
    // モード2: 展開処理 (解答には必須ではない可能性がありますが、問題文に「展開は2」とあるため実装)
    // ---------------------------------------------------------
    else if (mode == 2) {
        // 展開後の文字列長
        int decompressed_len = 0;
        int i = 0;
        
        while (i < actual_len) {
            int count = 0;
            
            // 数字部分の解析 (複数桁対応)
            while (i < actual_len && isdigit(str[i])) {
                count = count * 10 + (str[i] - '0');
                i++;
            }
            
            // 文字部分の取得
            if (i < actual_len) {
                char c = str[i];
                // 指定回数分文字を出力
                for (int j = 0; j < count; j++) {
                    printf("%c", c);
                }
                decompressed_len += count;
                i++;
            }
        }
        printf("\n"); // 1行目の出力終了

        // 2行目: 圧縮率の出力 (元のデータサイズに対する圧縮後のデータ長さの比率)
        // 展開処理の場合、入力が「圧縮データ」、出力が「元データ」に相当します。
        // 比率 = 入力(圧縮) / 出力(展開)
        double ratio = (double)actual_len / (double)decompressed_len;
        printf("M/L %d/%d %.3f\n", actual_len, decompressed_len, ratio);
    }

    return 0;
}