<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>21-22059-PHP</title>
    
</head>

<body>
    <?php
    // タイムゾーンを東京に設定
    date_default_timezone_set('Asia/Tokyo');

    // 今日の日付を表示
    echo date('<\p>今日はY年n月j日</p>');

    // 表示上の改行（簡易）
    echo "</br>";

    // 現在時刻を表示
    echo date('<\p>現在の時刻はh時i分s秒</p>');
    ?>


    <!-- ユーザ入力フォーム -->
    <form name="form" id="form" action="" method="POST">
        <!-- ID 入力欄: ユーザ識別子 -->
        <label for="id">ID</label>
        <input name="id" id="id" type="text" value="">

        <!-- パスワード入力欄: ブラウザ側は伏せ字表示 -->
        <label for="pass">PASSWORD</label>
        <input name="pass" id="pass" type="password" value="">

        <!-- 各ボタンで POST 送信し、サーバ側で処理を分岐する -->
        <input type="submit" name="regist" value="登録">
        <input type="submit" name="auth" value="認証">
        <input type="submit" name="delete" value ="削除">
    </form>

    <?php
    
    //登録処理
    if (isset($_POST['regist'])) {
        // 登録ボタンが押されたとき
        if (empty($_POST['id']) || empty($_POST['pass'])) {
            echo '未入力のため登録せず';
        } else {
            // フォームからの入力を受け取る
            $id = $_POST['id']; // ユーザが入力したID
            $pass = $_POST['pass']; // ユーザが入力したパスワード

            
            
            $conn = mysqli_connect("172.23.205.150", "pi", "raspberry", "jikken");

            // ID の重複チェック（同じ ID が既にあるか確認）
            $result = mysqli_query($conn, "SELECT * FROM web WHERE ID = '$id';");

            if (mysqli_num_rows($result) != 0) {
                // 既に同じ ID が存在する
                echo $id . 'の登録失敗';
            } else {
                // 新規登録
                mysqli_query($conn, "INSERT INTO web VALUES(NULL, '$id', '$pass');");
                echo $id . 'の登録完了';
                mysqli_close($conn); // 接続を閉じる
            }
        }
    }

    //認証処理 
    if (isset($_POST['auth'])) {
        // 認証ボタンが押されたとき
        $id = $_POST['id']; // 入力されたID
        $pass = $_POST['pass']; // 入力されたパスワード
        // DB接続
        $conn = mysqli_connect("172.23.205.150", "pi", "raspberry", "jikken");

        // IDとPASSWORD の組が存在するかを検索
        $result = mysqli_query($conn, "SELECT * FROM web WHERE ID = '$id' AND PASSWORD = '$pass';");
        if (mysqli_num_rows($result) != 0) {
            // レコードが見つかれば認証成功
            echo $id . 'の認証成功';
        } else {
            // 見つからなければ認証失敗
            echo $id . 'の認証失敗';
        }
        mysqli_close($conn); // 接続を閉じる
    }

    //消去処理
    if (isset($_POST['delete'])) {
        // 削除ボタンが押されたとき
        $id = $_POST['id']; // 削除対象の ID
        $pass = $_POST['pass']; // 確認用パスワード
        // DB 接続
        $conn = mysqli_connect("172.23.205.150", "pi", "raspberry", "jikken");

        // 指定の ID と PASSWORD の組が存在するか確認
        $result = mysqli_query($conn, "SELECT * FROM web WHERE ID = '$id' AND PASSWORD = '$pass';");

        if (mysqli_num_rows($result) > 0) {
            // 存在する場合は削除
            mysqli_query($conn, "DELETE FROM web WHERE ID = '$id' AND PASSWORD = '$pass';");
            echo $id . 'の削除成功';
        } else {
            // 存在しない場合は削除失敗
            echo $id . 'の削除失敗';
        }
        mysqli_close($conn); // 接続を閉じる
    }

    ?>

</body>

</html>