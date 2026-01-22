# ============================================================
# 02_analysis_guiraud.R
# 分析2：Guiraud Index = V / sqrt(N)
# 出力：outputs/2/
# ============================================================

suppressPackageStartupMessages({
  library(dplyr)
  library(readr)
  library(ggplot2)
})

# 出力先フォルダ（分析2）
out_dir <- "outputs/2"
dir.create(out_dir, showWarnings = FALSE, recursive = TRUE)

# df_ranked 読み込み（共通データ）
df_ranked <- readRDS(file.path("outputs", "common", "df_ranked.rds"))

song_guiraud <- df_ranked %>%
  group_by(Group, GroupDir, Title, Year, Album, Filename) %>%
  summarise(
    token_n = sum(Freq),
    type_v  = n_distinct(Term),
    guiraud = ifelse(token_n > 0, type_v / sqrt(token_n), NA_real_),
    .groups = "drop"
  )

# 出力CSV
write_csv(song_guiraud, file.path(out_dir, "song_guiraud.csv"))

group_summary <- song_guiraud %>%
  group_by(GroupDir) %>%
  summarise(
    n_songs = n(),
    guiraud_mean = mean(guiraud, na.rm = TRUE),
    guiraud_sd   = sd(guiraud, na.rm = TRUE),
    token_n_mean = mean(token_n, na.rm = TRUE),
    type_v_mean  = mean(type_v, na.rm = TRUE),
    .groups = "drop"
  )

# グループ別統計
write_csv(group_summary, file.path(out_dir, "group_guiraud_summary.csv"))

# 検定
x <- song_guiraud %>% select(GroupDir, guiraud) %>% filter(!is.na(guiraud))
t_p <- tryCatch(t.test(guiraud ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
w_p <- tryCatch(wilcox.test(guiraud ~ GroupDir, data = x)$p.value, error = function(e) NA_real_)
tests <- tibble(metric = "guiraud", t_p = t_p, w_p = w_p)

# 検定結果
write_csv(tests, file.path(out_dir, "tests_guiraud.csv"))

# 可視化（箱ひげ）
p <- ggplot(song_guiraud, aes(x = GroupDir, y = guiraud)) +
  geom_boxplot() +
  theme_bw(base_size = 12) +
  labs(x = "Group（old/new）", y = "Guiraud Index（V/sqrt(N)）")
ggsave(file.path(out_dir, "plots", "box_guiraud.png"), p, width = 6, height = 4, dpi = 200)

message("分析2完了：", normalizePath(out_dir))
