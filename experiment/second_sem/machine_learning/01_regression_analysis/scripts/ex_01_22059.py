







import numpy as np
import matplotlib.pyplot as plt


def load_csv(path: str):
    """CSVファイルを読み込み，ヘッダーとデータを返す関数

    numpy.genfromtxtとnumpy.loadtxtを用いてCSVを読み込む

    Parameters
    ----------
    path: str
        CSVファイルのパス

    Returns
    -------
    header : list
        ヘッダー名のリスト
    data : numpy.ndarray of float, shape (n_rows, n_cols)
        データの数値配列
    """

    # ヘッダーを取得（1行目）
    header = np.genfromtxt(path, delimiter=',', dtype=str, max_rows=1)
    header = [h.strip() for h in header.tolist()]

    # 2行目以降のデータを取得
    data = np.loadtxt(path, delimiter=',', skiprows=1)

    return header, data


def regression_analysis(x: np.ndarray, y: np.ndarray,) -> np.ndarray:
    """回帰分析によりパラメータ推定する関数
    
    設計行列xと目的変数yに対して，正規行列によりパラメータを推定

    Parameters
    ----------
    x : numpy.ndarray of float, shape (n_samples, n_features_plus1)
        切片用の 1 列を含む設計行列
    y : numpy.ndarray of float, shape (n_samples,)
        目的変数ベクトル

    Returns
    -------
    w : numpy.ndarray of float, shape (n_features_plus1,)
        切片を含む全パラメータベクトル
    """

    w = np.linalg.inv(x.T @ x) @ (x.T @ y)# [TASK] 正規方程式を用いてパラメータベクトルwを算出
    return w



def predict(x: np.ndarray, w: np.ndarray) -> np.ndarray:
    """設計行列とパラメータベクトルから予測値を計算する

    Parameters
    ----------
    x : ndarray of float, shape (n_samples, n_features_plus1)
        切片列を含む設計行列
    w : ndarray of float, shape (n_features_plus1,)
        切片を含むパラメータベクトル

    Returns
    -------
    y_pred : ndarray of float, shape (n_samples,)
        予測値
    """

    y_pred = x @ w# [TASK] 設計行列xとパラメータベクトルwから予測値y_predを算出
    return y_pred

#[assignment]R^2
def coefficient_of_determination(y: np.ndarray, y_pred: np.ndarray) -> np.ndarray:
    
    square_R = 1 - ((y - y_pred).T @ (y - y_pred)) / ((y - np.mean(y)).T @ (y - np.mean(y)))
    return square_R

#[assignment]RMSE
def root_mean_squared_error(y: np.ndarray, y_pred: np.ndarray) -> np.ndarray:

    RMSE = np.sqrt(((y - y_pred).T @ (y - y_pred)) / y.shape[0])
    return RMSE

def main():

    # CSVファイルの読み込み
    data_path="../data/advertising.csv"
    header, data = load_csv(data_path)

    # 説明変数と目的変数に分割
    x = data[:, :-1]
    y = data[:, -1]
    
    # 目的変数の列名を除去(説明変数だけのリストにする)
    header = header[:-1]

    #[assignment]相互作用項
    tr = x[:,0] * x[:,1]    #TV * Radio
    tn = x[:,0] * x[:,2]    #TV * Newspaper
    rn = x[:,1] * x[:,2]    #Radio * Newspaper

    #[assignment]行列xに配列を追加
    x = np.hstack([x, tr.reshape(-1, 1)])   #引数-1は自動計算
    x = np.hstack([x, tn.reshape(-1, 1)])
    x = np.hstack([x, rn.reshape(-1, 1)])

    #[assignment]ラベルを追加
    header.append("TV * Radio")
    header.append("TV * Newspaper")
    header.append("Radio * Newspaper")

    #[assignment]回帰係数の入力を追加
    print("表示する回帰係数を選択(スペース区切り)")
    print("1:TV, 2:Radio, 3:Newspaper, 4:TV * Radio, 5:TV * Newspaper, 6:Radio * Newspaper")
    choices =  input(": ")
    idx = [int(n) - 1 for n in choices.split()]
    x = x[:, idx]
    header = [header[i] for i in idx]
    
    # バイアス項：要素1の列ベクトル，xの行数×1
    # np.ones の shape はタプルで渡す（例: (n_rows, 1)）
    bias = np.ones((x.shape[0], 1))  # [TASK] xの行数に合わせたバイアス項の列ベクトルを作成

    
    # 説明変数に切片列を追加して設計行列を作成
    # np.hstack は配列のリストを受け取るので [bias, x] のように渡す
    x = np.hstack([bias, x])  # [TASK] バイアス項の列を説明変数xの先頭に結合して設計行列を作成

    # 回帰分析
    w = regression_analysis(x, y)

    # 切片と回帰係数に分割
    intercept = w[0]
    coefs = w[1:]

    # 予測値の計算と評価指標の算出
    y_pred = predict(x, w)

    #[assignment]R^2
    square_R = coefficient_of_determination(y, y_pred)    
    #[assignment]RMSE       
    RMSE = root_mean_squared_error(y, y_pred)



    # 求めたパラメータの表示
    
    print("=====================================")
    print("回帰分析結果")
    print(f"切片: {intercept}") 
    for i in range(len(coefs)):
        print(f"回帰係数({header[i]}): {coefs[i]}")
    
    print("=====================================")

    # NumPyを用いて回帰分析（確認用）
    # SVDにより安定した数値をを解を算出しているため，結果が異なる場合がある
    w, residuals, rank, s = np.linalg.lstsq(x, y, rcond=None)
    intercept = w[0]
    coefs = w[1:]


    print("NumPyによる回帰分析結果（確認用）")
    print(f"切片: {intercept}") 
    for i in range(len(coefs)):
        print(f"回帰係数({header[i]}): {coefs[i]}")

    print("=====================================")
    print("モデル評価")
    print(f"R^2: {square_R}")
    print(f"RMSE: {RMSE}")

    


    # グラフに描画(横軸が実測値，縦軸が予測値の散布図)
    # 直線上に点が分布していれば予測精度が高いことを示す
    plt.figure(figsize=(6,6))
    plt.scatter(y, y_pred, alpha=0.7)
    plt.xlabel("Actual Sales")
    plt.ylabel("Predicted Sales")
    plt.plot([y.min(), y.max()], [y.min(), y.max()], 'r--')
    plt.tight_layout()
    plt.savefig('../outputs/assignment_advertising_actual_vs_predicted.png')



if __name__ == "__main__":
    main()