# ============================================================
# 03_analysis_sentiment.R 修正（多対多の関係を解消する方法）
# ============================================================

suppressPackageStartupMessages({
  library(dplyr)
  library(readr)
  library(stringr)
  library(data.table)
  library(ggplot2)
  library(httr)   # URLから直接ファイルを取得するためのライブラリ
})

# 出力先フォルダ（分析3）
out_dir <- "outputs/3"
dir.create(out_dir, showWarnings = FALSE, recursive = TRUE)

# df_ranked 読み込み（共通データ）
df_ranked <- readRDS(file.path("outputs", "common", "df_ranked.rds"))

# ---- 1. ネットから感情辞書をダウンロード ----
# URLを指定して、感情辞書を直接インポート
polarity_url <- "https://x.gd/V87oH"  # 高村さんの感情辞書URL
response <- GET(polarity_url)

# 応答が成功した場合、辞書CSVを読み込む
if (status_code(response) == 200) {
  temp_file <- tempfile(fileext = ".csv")
  writeBin(content(response, "raw"), temp_file)
  
  # 感情辞書を読み込む
  word_polarity_dict <- read.table(temp_file, sep = ":", stringsAsFactors = FALSE, 
                                   fileEncoding = "CP932", encoding = "UTF-8")
  
  # 内容確認
  print(head(word_polarity_dict))
} else {
  stop("感情辞書のダウンロードに失敗しました。URLを確認してください。")
}

# ---- 2. 辞書の整形（word, polarity, score） ----
# 辞書には、"V1"（単語）と "V4"（感情スコア）が含まれているはず
word_polarity_dict <- word_polarity_dict %>%
  rename(
    word = V1,
    score = V4
  ) %>%
  mutate(
    polarity = case_when(
      score > 0  ~ "positive",  # ポジティブ
      score < 0  ~ "negative",  # ネガティブ
      TRUE       ~ "neutral"    # 中立
    ),
    score = as.numeric(score)  # スコアを数値に変換
  )

# 重複した単語に対するスコアを平均化（多対多の関係を解消）
word_polarity_dict <- word_polarity_dict %>%
  group_by(word) %>%
  summarise(score = mean(score, na.rm = TRUE), .groups = "drop")

# ---- 3. 辞書と歌詞データを結びつける ----
df_ranked <- df_ranked %>%
  left_join(word_polarity_dict, by = c("Term" = "word"))

# ---- 4. 感情スコアの計算（頻度加重平均） ----
song_sentiment <- df_ranked %>%
  group_by(Group, GroupDir, Title, Year, Album, Filename) %>%
  summarise(
    token_n = sum(Freq),
    sentiment_score = sum(Freq * score, na.rm = TRUE) / token_n,  # 頻度加重平均
    .groups = "drop"
  )

# 出力: 感情スコア結果のCSV
write_csv(song_sentiment, file.path(out_dir, "song_sentiment.csv"))

# ---- 5. グループ別感情スコアの平均を計算 ----
song_sentiment_avg <- song_sentiment %>%
  group_by(GroupDir) %>%
  summarise(
    senti_mean_mean = mean(sentiment_score, na.rm = TRUE),  # 感情スコアの平均
    senti_mean_sd = sd(sentiment_score, na.rm = TRUE),      # 感情スコアの標準偏差
    .groups = "drop"
  )

# グループ別感情スコアの結果を保存
write_csv(song_sentiment_avg, file.path(out_dir, "group_sentiment_avg.csv"))

# ---- 6. 検定（辞書外語含む） ----
run_tests <- function(df, col) {
  x <- df %>% select(GroupDir, value = all_of(col)) %>% filter(!is.na(value))
  if (n_distinct(x$GroupDir) < 2) return(tibble(metric = col, t_p = NA_real_, w_p = NA_real_))
  t_p <- tryCatch(t.test(value ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
  w_p <- tryCatch(wilcox.test(value ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
  tibble(metric = col, t_p = t_p, w_p = w_p)
}

tests <- bind_rows(
  run_tests(song_sentiment, "sentiment_score")
)
write_csv(tests, file.path(out_dir, "tests_sentiment.csv"))

# ---- 7. 散布図（感情スコア vs. 他の指標） ----
# 散布図：感情スコア（y）とグループ別平均感情スコア（x）の関係
p1 <- ggplot(song_sentiment_avg, aes(x = senti_mean_mean, y = senti_mean_sd, color = GroupDir)) +
  geom_point(alpha = 0.7) +
  theme_bw(base_size = 12) +
  labs(x = "グループ別平均感情スコア", y = "感情スコアの標準偏差", title = "グループ別感情スコアの平均と標準偏差")

# 散布図を保存
ggsave(file.path(out_dir, "plots", "scatter_senti_mean_avg.png"), p1, width = 6, height = 4, dpi = 200)

message("分析3完了：", normalizePath(out_dir))
