#!/bin/bash

# ==========================================
# 設定
# ==========================================
PYTHON_SCRIPT="ex_01_22059.py"

# 実行コマンド
# uv を使用している場合は "uv run" に書き換えてください
# CMD="uv run"
CMD="uv run"

# 比較したい入力パターンのリスト
INPUTS=(
    "1"
    "2"
    "3"
    "1 2 3"
    "1 2 3 4"
    "1 2 3 5"
    "1 2 3 6"
    "1 2 3 4 5 6"
    "1 2 4"
)
# ==========================================

# ファイルの存在確認
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "エラー: $PYTHON_SCRIPT が見つかりません。"
    exit 1
fi

echo "モデル精度の比較を開始します..."
echo "=========================================================="
# ヘッダーの表示 (printfで綺麗に整形)
printf "%-20s | %-15s | %-15s\n" "入力パターン" "R^2" "RMSE"
echo "----------------------------------------------------------"

# ループ処理
for input_val in "${INPUTS[@]}"; do
    
    # Pythonを実行し、入力をパイプで渡す
    # 結果を変数 output に格納 (エラー出力は画面に出さないよう /dev/null へ)
    output=$(echo "$input_val" | $CMD "$PYTHON_SCRIPT" 2>/dev/null)

    # grep と awk を使って R^2 と RMSE の数値を抽出
    r2=$(echo "$output" | grep "R^2:" | awk '{print $2}')
    rmse=$(echo "$output" | grep "RMSE:" | awk '{print $2}')

    # 数値が取れなかった場合の処理（エラー判定）
    if [ -z "$r2" ]; then
        r2="Error"
        rmse="Error"
    fi

    # 結果を整形して表示
    printf "%-20s | %-15s | %-15s\n" "$input_val" "$r2" "$rmse"

done

echo "=========================================================="
echo "完了"