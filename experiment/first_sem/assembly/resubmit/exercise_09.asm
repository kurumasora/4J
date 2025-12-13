.text
.globl main
main:
    li  $t0, 1000
    li  $t1, 3            # シフトするビット数（例: 3ビット）

    srlv $t2, $t0, $t1    # $t2 = $t0 >> $t1（論理右シフト）

    li $v0, 10            # プログラム終了
    syscall
