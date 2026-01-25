# ============================================================
# 01_analysis_bccwj.R
# 分析1：BCCWJ一般性（平均ランク，基本語彙率，未一致率）
# 出力：outputs/1/
# ============================================================

suppressPackageStartupMessages({
  library(dplyr)
  library(readr)
  library(ggplot2)
})

# 出力先フォルダ（分析1）
out_dir <- "outputs/1"
dir.create(out_dir, showWarnings = FALSE, recursive = TRUE)

# df_ranked 読み込み（共通データ）
df_ranked <- readRDS(file.path("outputs", "common", "df_ranked.rds"))

# 基本語彙の閾値（上位N位を基本語彙とみなす）
basic_rank_threshold <- 10000

song_bccwj <- df_ranked %>%
  group_by(Group, GroupDir, Title, Year, Album, Filename) %>%
  summarise(
    token_n      = sum(Freq),
    matched_n    = sum(Freq[!is.na(bccwj_rank)]),
    unmatched_rt = ifelse(token_n > 0, 1 - matched_n / token_n, NA_real_),
    mean_rank_w  = ifelse(matched_n > 0, sum(Freq * bccwj_rank, na.rm = TRUE) / matched_n, NA_real_),
    basic_rt     = ifelse(
      token_n > 0,
      sum(Freq[!is.na(bccwj_rank) & bccwj_rank <= basic_rank_threshold], na.rm = TRUE) / token_n,
      NA_real_
    ),
    .groups = "drop"
  )

# 出力CSV
write_csv(song_bccwj, file.path(out_dir, "song_bccwj.csv"))

group_summary <- song_bccwj %>%
  group_by(GroupDir) %>%
  summarise(
    n_songs = n(),
    mean_rank_w_mean  = mean(mean_rank_w, na.rm = TRUE),
    mean_rank_w_sd    = sd(mean_rank_w, na.rm = TRUE),
    basic_rt_mean     = mean(basic_rt, na.rm = TRUE),
    basic_rt_sd       = sd(basic_rt, na.rm = TRUE),
    unmatched_rt_mean = mean(unmatched_rt, na.rm = TRUE),
    unmatched_rt_sd   = sd(unmatched_rt, na.rm = TRUE),
    .groups = "drop"
  )

# グループ別統計
write_csv(group_summary, file.path(out_dir, "group_bccwj_summary.csv"))

# バープロット：感情スコア（mean_rank_w, basic_rt, unmatched_rt）のグループ別比較
p1 <- ggplot(song_bccwj, aes(x = GroupDir, y = mean_rank_w, fill = GroupDir)) +
  geom_bar(stat = "summary", fun = "mean", position = "dodge") +
  theme_bw(base_size = 12) +
  labs(x = "Group（old/new）", y = "平均ランク（頻度加重，低いほど一般的）", title = "グループ別平均BCCWJランク")
ggsave(file.path(out_dir, "plots", "bar_mean_rank_w.png"), p1, width = 6, height = 4, dpi = 200)

p2 <- ggplot(song_bccwj, aes(x = GroupDir, y = basic_rt, fill = GroupDir)) +
  geom_bar(stat = "summary", fun = "mean", position = "dodge") +
  theme_bw(base_size = 12) +
  labs(x = "Group（old/new）", y = paste0("基本語彙率（rank≤", basic_rank_threshold, "）"), title = "グループ別基本語彙率")
ggsave(file.path(out_dir, "plots", "bar_basic_rt.png"), p2, width = 6, height = 4, dpi = 200)

p3 <- ggplot(song_bccwj, aes(x = GroupDir, y = unmatched_rt, fill = GroupDir)) +
  geom_bar(stat = "summary", fun = "mean", position = "dodge") +
  theme_bw(base_size = 12) +
  labs(x = "Group（old/new）", y = "未一致率（辞書外率の目安）", title = "グループ別未一致率")
ggsave(file.path(out_dir, "plots", "bar_unmatched_rt.png"), p3, width = 6, height = 4, dpi = 200)

# 検定
run_tests <- function(df, col) {
  x <- df %>% select(GroupDir, value = all_of(col)) %>% filter(!is.na(value))
  if (n_distinct(x$GroupDir) < 2) return(tibble(metric = col, t_p = NA_real_, w_p = NA_real_))
  t_p <- tryCatch(t.test(value ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
  w_p <- tryCatch(wilcox.test(value ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
  tibble(metric = col, t_p = t_p, w_p = w_p)
}

tests <- bind_rows(
  run_tests(song_bccwj, "mean_rank_w"),
  run_tests(song_bccwj, "basic_rt"),
  run_tests(song_bccwj, "unmatched_rt")
)

# 検定結果
write_csv(tests, file.path(out_dir, "tests_bccwj.csv"))

message("分析1完了：", normalizePath(out_dir))
