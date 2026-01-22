# ============================================================
# 00_data_prepare.R
# データ準備：共通処理（df_ranked.rds, lyrics_list.rdsなど）
# 出力：outputs/common/
# ============================================================

suppressPackageStartupMessages({
  library(RMeCab)
  library(dplyr)
  library(tidyr)
  library(data.table)
  library(readr)
  library(stringr)
})

# ---- 入力パス（プロジェクト直下からの相対パス）----
lyrics_list_path <- file.path("data", "lyrics_list.csv")
bccwj_path       <- file.path("data", "BCCWJ_frequencylist_suw_ver1_0.tsv")
lyrics_old_dir   <- file.path("lyrics", "old")
lyrics_new_dir   <- file.path("lyrics", "new")

# 出力先共通フォルダ（outputs/common）
out_dir_common <- "outputs/common"
dir.create(out_dir_common, showWarnings = FALSE, recursive = TRUE)

# ---- 歌詞リスト読込 ----
lyrics_list <- read_csv_safe(lyrics_list_path)

# --- BCCWJ頻度表の読込 ----
if (!file.exists(bccwj_path)) stop(paste0("見つかりません：", bccwj_path))

bccwj_raw <- fread(
  bccwj_path,
  sep = "\t",
  encoding = "UTF-8",
  showProgress = FALSE,
  select = c("rank", "lemma", "lForm")
)

# ---- Groupから置き場（old/new）を決める（保険でYearも使う）----
group_norm <- tolower(lyrics_list$Group)
lyrics_list <- lyrics_list %>%
  mutate(
    GroupDir = case_when(
      group_norm %in% c("old", "group old", "pre", "before") ~ "old",
      group_norm %in% c("new", "group new", "post", "after") ~ "new",
      is.na(group_norm) | group_norm == "" ~ ifelse(Year < 2016, "old", "new"),
      TRUE ~ ifelse(Year < 2016, "old", "new")
    ),
    LyricsPath = file.path("lyrics", GroupDir, Filename)
  )

# ---- docDFはフォルダ直下しか見ないので old と new を別々に解析 ----
docdf_to_long <- function(df_wide, files_expected) {
  term_col <- intersect(names(df_wide), c("TERM", "Term", "term"))
  term_col <- term_col[1]
  doc_cols <- intersect(files_expected, colnames(df_wide))
  df_tmp <- df_wide %>%
    select(all_of(term_col), all_of(doc_cols))
  names(df_tmp)[1] <- "Term"
  
  df_tmp %>%
    pivot_longer(cols = all_of(doc_cols), names_to = "Filename", values_to = "Freq") %>%
    filter(Freq > 0) %>%
    transmute(
      Term = Term,
      Filename = Filename,
      Freq = as.numeric(Freq)
    )
}

old_files <- lyrics_list %>% filter(GroupDir == "old") %>% pull(Filename)
new_files <- lyrics_list %>% filter(GroupDir == "new") %>% pull(Filename)

df_old_wide <- docDF(lyrics_old_dir, type = 1, pos = c("名詞", "動詞", "形容詞"))
df_new_wide <- docDF(lyrics_new_dir, type = 1, pos = c("名詞", "動詞", "形容詞"))

df_old_long <- if (length(old_files) > 0) docdf_to_long(df_old_wide, old_files) else tibble(Term = character(), Filename = character(), Freq = numeric())
df_new_long <- if (length(new_files) > 0) docdf_to_long(df_new_wide, new_files) else tibble(Term = character(), Filename = character(), Freq = numeric())

df_long <- bind_rows(df_old_long, df_new_long) %>%
  inner_join(lyrics_list, by = "Filename")

# ---- BCCWJのランク付け ----
bcc_map1 <- bccwj_raw[, .(Term = lemma, bccwj_rank = as.integer(rank))]
bcc_map2 <- bccwj_raw[, .(Term = lForm, bccwj_rank = as.integer(rank))]
bcc_map  <- rbindlist(list(bcc_map1, bcc_map2), use.names = TRUE, fill = TRUE)

bcc_map <- bcc_map[!is.na(Term) & Term != "", .(bccwj_rank = min(bccwj_rank, na.rm = TRUE)), by = Term]

df_ranked <- df_long %>%
  left_join(as.data.frame(bcc_map), by = "Term")

# ---- 保存 ----
saveRDS(lyrics_list, file.path(out_dir_common, "lyrics_list.rds"))
saveRDS(df_ranked, file.path(out_dir_common, "df_ranked.rds"))
saveRDS(bcc_map, file.path(out_dir_common, "bcc_map.rds"))

message("共通データ出力完了：", normalizePath(out_dir_common))
