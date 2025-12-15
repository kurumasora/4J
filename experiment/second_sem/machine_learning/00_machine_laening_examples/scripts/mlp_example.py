import os
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt


class SimpleMLP(nn.Module):
    """
    シンプルな多層パーセプトロン（MLP）モデル
    入力: 1次元、隠れ層: 32ユニット、出力: 1次元
    """

    def __init__(self):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(1, 32),
            nn.ReLU(),
            nn.Linear(32, 1)
        )

    def forward(self, x):
        return self.net(x)


def main():
    """
    PyTorchによるMLP回帰のサンプルプログラム

    - ダミーデータを生成し、MLPで回帰学習
    - 学習曲線と予測結果をプロットして画像として保存
    """

    # ダミーデータ生成
    np.random.seed(0)
    X = np.linspace(-3, 3, 200).reshape(-1, 1)
    y = np.sin(X) + 0.1 * np.random.randn(*X.shape)

    # Tensorへ変換
    X_tensor = torch.from_numpy(X).float()
    y_tensor = torch.from_numpy(y).float()

    # モデル・損失関数・最適化手法
    model = SimpleMLP()
    criterion = nn.MSELoss()
    optimizer = optim.Adam(model.parameters(), lr=0.01)

    # 学習
    losses = []
    model.train()
    for epoch in range(1000):
        # 順伝播
        output = model(X_tensor)
        # 損失計算
        loss = criterion(output, y_tensor)

        # 逆伝播とパラメータ更新
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        losses.append(loss.item())

    # 予測
    model.eval()
    with torch.no_grad():
        y_pred = model(X_tensor).numpy()

    # 学習曲線のプロット
    plt.figure()
    plt.plot(losses)
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.title("MLP Training Loss")
    plt.savefig("../outputs/mlp_training_loss.png")

    # 予測結果のプロット
    plt.figure()
    plt.scatter(X, y, color="blue", label="Data")
    plt.plot(X, y_pred, color="red", label="MLP Prediction")
    plt.xlabel("X")
    plt.ylabel("y")
    plt.legend()
    plt.title("MLP Regression Example")
    plt.savefig("../outputs/mlp_regression_example.png")


if __name__ == "__main__":
    # 出力ディレクトリの作成
    os.makedirs("../outputs", exist_ok=True)

    # メイン関数の実行
    main()