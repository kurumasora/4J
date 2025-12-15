#!/bin/bash

# ========================================================
# 設定
# ========================================================
# Pythonスクリプトのファイル名
PYTHON_SCRIPT="assignment_1.py"

# 実行コマンド
# uvを使っている場合は "uv run"、使っていない場合は "python3" などに変更してください
CMD="uv run" 
# CMD="python3" 

# 結果を保存する一時ファイル
RESULT_FILE="results_best_model.txt"
# ========================================================

# 1. 準備確認
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "エラー: '$PYTHON_SCRIPT' が見つかりません。"
    echo "このスクリプトと同じ場所にPythonファイルを置いてください。"
    exit 1
fi

# 結果ファイルを空にする
echo "" > $RESULT_FILE

echo "6つの変数から3つを選ぶ全組み合わせ (20通り) を実行中..."
echo "-------------------------------------------------------"

# 2. 3重ループで組み合わせ生成 (1~6の中から重複なしで3つ選ぶ)
# i: 1つ目の変数 (1〜4)
for ((i=1; i<=4; i++)); do
    # j: 2つ目の変数 (iの次 〜 5)
    for ((j=i+1; j<=5; j++)); do
        # k: 3つ目の変数 (jの次 〜 6)
        for ((k=j+1; k<=6; k++)); do
            
            # 入力文字列を作成 (例: "1 2 3")
            INPUT_STR="$i $j $k"
            
            # 進行状況を表示
            echo -ne "Testing combination: [ $INPUT_STR ] ... "

            # 3. Pythonを実行
            # echoで入力をパイプし、エラー出力も含めて変数に格納
            OUTPUT=$(echo "$INPUT_STR" | $CMD $PYTHON_SCRIPT 2>&1)

            # 4. 結果の抽出 (R^2 と RMSE)
            # grepで行を探し、awkで数値部分(2列目)を取り出す
            R2=$(echo "$OUTPUT" | grep "R^2:" | awk '{print $2}')
            RMSE=$(echo "$OUTPUT" | grep "RMSE:" | awk '{print $2}')

            # 成功判定
            if [ -n "$R2" ]; then
                echo "OK (R^2 = $R2)"
                # 結果ファイルに書き込む (R2 RMSE 組み合わせ)
                echo "$R2 $RMSE $INPUT_STR" >> $RESULT_FILE
            else
                echo "FAILED"
                echo "  -> エラー内容: $OUTPUT"
            fi
        done
    done
done

echo "-------------------------------------------------------"
echo "実行完了。集計結果を表示します。"
echo ""

# 5. 結果の集計と表示
if [ -s $RESULT_FILE ]; then
    echo "=== 最も精度が高いモデル (R^2 最大) ==="
    echo "R^2       RMSE      Combination"
    # R^2(1列目)で降順ソートして先頭1行を表示
    sort -nr -k1 $RESULT_FILE | head -n 1
    
    echo ""
    echo "=== トップ5 ランキング ==="
    sort -nr -k1 $RESULT_FILE | head -n 5
else
    echo "エラー: 有効な結果が得られませんでした。"
fi

# 一時ファイルを削除
rm $RESULT_FILE