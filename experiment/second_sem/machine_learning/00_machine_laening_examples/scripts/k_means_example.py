import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans


def main():
    """
    k-meansクラスタリングのサンプルプログラム

    - ダミーデータを生成し、k-meansでクラスタリング
    - 各クラスタごとに色分けしてプロット
    - クラスタ中心もプロットし、画像として保存
    """

    # ダミーデータ生成
    np.random.seed(0)
    X = np.vstack([
        np.random.randn(100, 2) + np.array([2, 2]),
        np.random.randn(100, 2) + np.array([-2, -2]),
        np.random.randn(100, 2) + np.array([2, -2])
    ])

    # k-meansクラスタリング
    kmeans = KMeans(n_clusters=3, random_state=0)
    y_pred = kmeans.fit_predict(X)

    # 結果の表示
    plt.scatter(X[:, 0], X[:, 1], c=y_pred, cmap="viridis", marker="o", label="Data")
    plt.scatter(kmeans.cluster_centers_[:, 0], kmeans.cluster_centers_[:, 1],
                c="red", marker="x", s=200, label="Centers")
    plt.xlabel("X1")
    plt.ylabel("X2")
    plt.legend()
    plt.title("k-means Clustering Example")
    plt.savefig("../outputs/k_means_example.png")


if __name__ == "__main__":
    # 出力ディレクトリの作成
    os.makedirs("../outputs", exist_ok=True)

    # メイン関数の実行
    main()
