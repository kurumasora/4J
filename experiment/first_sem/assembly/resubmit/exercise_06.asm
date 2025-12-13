	.text
.globl main
main:
    # 比較対象の値を設定
    li $t0, 10     # 比較対象1
    li $t1, 5      # 比較対象2
    li $t2, 3      # 比較対象3

    # 比較: $t0 > $t1
    slt $t4, $t1, $t0    # $t4 = ($t0 > $t1) ? 1 : 0

    # 比較: $t0 > $t2
    slt $t5, $t2, $t0    # $t5 = ($t0 > $t2) ? 1 : 0

    # 両方満たされていれば AND = 1
    and $t3, $t4, $t5    # $t3 = ($t4 & $t5)

    # 終了
    li $v0, 10
    syscall
