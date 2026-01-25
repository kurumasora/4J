# ============================================================
# 04_basic_stats.R
# 分析3.1：基本統計量の算出（Token, Type）
# ============================================================

library(RMeCab)
library(dplyr)
library(readr)
library(tidyr)

# ---- 設定 ----
out_dir <- "outputs/tables"   # 結果保存先
dir.create(out_dir, recursive = TRUE, showWarnings = FALSE)

# 歌詞フォルダ
lyrics_dirs <- list(
  Old = "lyrics/old",
  New = "lyrics/new"
)

# 歌詞リスト（曲情報のマスタとして使用）
list_file <- "data/lyrics_list.csv"
song_list <- read_csv(list_file, show_col_types = FALSE)

# ---- 形態素解析と集計 ----
# グループごとに処理
stats_results <- list()

for (grp in names(lyrics_dirs)) {
  target_dir <- lyrics_dirs[[grp]]
  
  # ファイル一覧取得
  files <- list.files(target_dir, pattern = "\\.txt$", full.names = TRUE)
  
  if (length(files) == 0) {
    warning(paste(grp, "グループのファイルが見つかりません。step0を実行しましたか？"))
    next
  }
  
  # RMeCabで一括読み込み（頻度表作成）
  # type=1: 形容詞・動詞・名詞などすべての品詞を含めてカウントします
  # pos引数を指定しないことで、全語彙を対象にします
  message(paste(grp, "の解析中..."))
  df_mecab <- docDF(target_dir, type = 1)
  
  # 集計計算
  # docDFの結果は、1列目がTerm, 2-3列目が品詞情報, 4列目以降が各ファイル
  file_cols <- colnames(df_mecab)[4:ncol(df_mecab)]
  
  # 各ファイルの統計量を計算
  grp_stats <- data.frame(
    Filename = file_cols,
    Token = colSums(df_mecab[, file_cols, drop = FALSE]),     # 総語数
    Type  = colSums(df_mecab[, file_cols, drop = FALSE] > 0)  # 異なり語数
  )
  
  # ファイル名がフルパス等の場合があるため、basenameに合わせる
  grp_stats$Filename <- basename(grp_stats$Filename)
  
  stats_results[[grp]] <- grp_stats
}

# 結合
all_stats <- bind_rows(stats_results)

# ---- 結果の結合と整形 ----
# 元のリスト（曲名やアルバム名）と結合
# Filenameをキーにして結合します
final_data <- song_list %>%
  inner_join(all_stats, by = "Filename")

# ---- 【表1】グループ別基本統計量一覧の作成 ----
table1 <- final_data %>%
  group_by(Group) %>%
  summarise(
    Songs = n(),                           # 曲数
    Mean_Token = round(mean(Token), 1),    # 平均総語数
    Mean_Type  = round(mean(Type), 1),     # 平均異なり語数
    SD_Token   = round(sd(Token), 1),      # 標準偏差（参考）
    .groups = "drop"
  )

# コンソールに表示
print(table1)

# CSVとして保存（レポート用）
write_csv(table1, file.path(out_dir, "table1_basic_stats.csv"))
write_csv(final_data, file.path(out_dir, "table1_detail_per_song.csv")) # 各曲の詳細も保存

cat("\n集計完了。以下のファイルを確認してください：\n")
cat(file.path(out_dir, "table1_basic_stats.csv"), "\n")