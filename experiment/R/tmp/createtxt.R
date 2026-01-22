# -------------------------------------------------------
# 歌詞ファイル自動生成スクリプト
# -------------------------------------------------------

# 1. 管理用CSVを読み込む
# ※Windowsなら "CP932", Macなら "UTF-8" に変更してください
csv_file <- "radwimps_target_list.csv"

if (file.exists(csv_file)) {
  meta_data <- read.csv(csv_file, fileEncoding = "CP932", stringsAsFactors = FALSE)
} else {
  stop("エラー: 'radwimps_target_list.csv' が見つかりません。作業フォルダを確認してください。")
}

# 2. 保存用フォルダを作成する
dirs <- c("corpus/Old", "corpus/New")

for (d in dirs) {
  if (!dir.exists(d)) {
    dir.create(d, recursive = TRUE)
    message(paste("フォルダを作成しました:", d))
  }
}

# 3. ファイルを生成するループ
count <- 0

for (i in 1:nrow(meta_data)) {
  
  # 必要な情報を取り出す
  grp      <- meta_data$Group[i]    # Old or New
  filename <- meta_data$Filename[i] # ファイル名
  title    <- meta_data$Title[i]    # 曲名
  
  # 保存パスを作る (例: corpus/Old/old_01_yushinron.txt)
  file_path <- file.path("corpus", grp, filename)
  
  # ファイルがまだなければ作成する
  if (!file.exists(file_path)) {
    
    # 歌詞を貼る時の目印として、1行目に曲名だけ書いておく
    # (分析時はこの1行目を削除するか、そのままでも大きな影響はありません)
    writeLines(c(paste("【ここに", title, "の歌詞を貼り付けてください】")), file_path)
    
    count <- count + 1
  }
}

# 4. 完了メッセージ
message("-------------------------------------------------------")
message(paste(count, "個のファイルを生成しました！"))
message("corpus/Old と corpus/New フォルダの中身を確認してください。")
message("各ファイルを開いて、歌詞をコピペして上書き保存してください。")
