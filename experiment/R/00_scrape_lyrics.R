# ============================================================
# 00_scrape_lyrics.R
# Uta-Netから歌詞を取得して保存するスクリプト
# ============================================================

library(rvest)
library(dplyr)
library(readr)
library(stringr)

# ---- 設定 ----
list_file <- "data/lyrics_list.csv" # アップロードされたリスト
out_base  <- "lyrics"          # 保存先フォルダ

# フォルダ作成
dir.create(file.path(out_base, "old"), recursive = TRUE, showWarnings = FALSE)
dir.create(file.path(out_base, "new"), recursive = TRUE, showWarnings = FALSE)

# リスト読み込み
if (!file.exists(list_file)) stop("lyrics_list.csv が見つかりません")
song_list <- read_csv(list_file, show_col_types = FALSE)

# ---- スクレイピング関数 ----
get_lyrics_utanet <- function(title, artist = "RADWIMPS") {
  # 検索URL作成（アーティスト名 + 曲名で検索して精度を高める）
  query <- URLencode(paste(artist, title))
  search_url <- paste0("https://www.uta-net.com/search/?Keyword=", query)
  
  tryCatch({
    # 検索結果ページ取得
    page <- read_html(search_url)
    
    # 曲名リンクを探す（最初の /song/xxxx/ リンクを採用）
    # ※検索精度に依存するため、異なる曲が取れる可能性もゼロではありません
    link_node <- page %>% html_node("td.sp-w-100 a") 
    
    if (is.na(link_node)) return(NULL) # 見つからない場合
    
    song_url <- paste0("https://www.uta-net.com", html_attr(link_node, "href"))
    
    # 歌詞ページ取得
    song_page <- read_html(song_url)
    
    # 歌詞テキスト抽出（id="kashi_area"）
    lyrics_text <- song_page %>% 
      html_node("#kashi_area") %>% 
      html_text()
    
    # 全角スペース等のクリーニング
    lyrics_text <- str_replace_all(lyrics_text, "　", " ")
    
    return(lyrics_text)
    
  }, error = function(e) {
    message(paste("Error:", title, e$message))
    return(NULL)
  })
}

# ---- 実行ループ ----
cat("歌詞の取得を開始します（全", nrow(song_list), "曲）...\n")

for (i in 1:nrow(song_list)) {
  row <- song_list[i, ]
  
  # 保存パス
  group_dir <- ifelse(row$Group == "Old", "old", "new")
  save_path <- file.path(out_base, group_dir, row$Filename)
  
  # 既にファイルがあればスキップ
  if (file.exists(save_path)) {
    cat(sprintf("[%d/%d] Skip (Exist): %s\n", i, nrow(song_list), row$Title))
    next
  }
  
  # 取得
  cat(sprintf("[%d/%d] Downloading: %s ... ", i, nrow(song_list), row$Title))
  lyrics <- get_lyrics_utanet(row$Title)
  
  if (!is.null(lyrics)) {
    write_lines(lyrics, save_path)
    cat("OK\n")
  } else {
    cat("Failed (Not Found)\n")
  }
  
  # サーバー負荷軽減のため待機（重要）
  Sys.sleep(1.5)
}

cat("完了しました。\n")