import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression


def main():
    """
    線形回帰分析のサンプルプログラム

    - ダミーデータを生成し、線形回帰モデルを学習
    - 回帰係数と切片を表示
    - 回帰直線とデータ点をプロットして画像として保存
    """

    # ダミーデータ生成
    np.random.seed(0)
    X = 2 * np.random.rand(100, 1)
    y = 4 + 3 * X + np.random.randn(100, 1)

    # 線形回帰モデルの作成と学習
    model = LinearRegression()
    model.fit(X, y)

    # 予測
    X_new = np.array([[0], [2]])
    y_pred = model.predict(X_new)

    # 回帰係数と切片の表示
    print("回帰係数: ", model.coef_[0][0])
    print("切片: ", model.intercept_[0])

    # 結果の表示
    plt.scatter(X, y, color="blue", label="Data")
    plt.plot(X_new, y_pred, color="red", linewidth=2, label="Prediction")
    plt.xlabel("X")
    plt.ylabel("y")
    plt.legend()
    plt.title("Linear Regression Example")
    plt.savefig("../outputs/linear_regression_example.png")


if __name__ == "__main__":
    # ディレクトリの作成
    os.makedirs("../outputs", exist_ok=True)

    # メイン関数の実行
    main()
