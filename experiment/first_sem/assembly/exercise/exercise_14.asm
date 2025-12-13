	.data
	.text

	.globl	fib
fib:                            #フィボナッチ関数　C言語でいうスタックとは違う
	addi 	$sp, $sp, -12 
	sw   	$ra, 0($sp)
	sw 		$a0, 4($sp)         #a0は引数(項数)　swはスタックに入れる

#フィボナッチの定義場合分け
	slti	$t0, $a0, 2         #引数が2より小さければt0を１にする
	beq		$t0, $zero, L3      #引数は2以上
	beq		$a0, $zero, L1      #引数が0の時
	j		L2                  #それ以外->引数が１の時


	.globl L1
L1:
	addi	$v0, $zero, 0       #v0は戻り値->0
	addi	$sp, $sp, 12        #スタックポインタを元の位置に戻す
	jr		$ra                 #raはプログラム全部が終了した時に、次に飛ぶアドレスを保存

	.globl L2
L2:
	addi	$v0, $zero, 1       
	addi	$sp, $sp, 12
	jr 		$ra

	.globl	L3
L3:
	addi	$a0, $a0, -1        #デクリメントみたいなもん　フィボナッチ数列の定義より
	jal		fib
	sw		$v0, 8($sp)         

	lw		$a0, 4($sp)
	addi	$a0, $a0, -2
	jal 	fib

	lw		$t1, 8($sp)
	add 	$v0, $v0, $t1       #-1したやつと-2したやつをたす

	lw		$ra, 0($sp)         #raのロード
	lw		$a0, 4($sp)
	addi	$sp, $sp, 12

	jr		$ra                 #保存したアドレスに飛ぶ
	
	.globl main
main:	
	li		$t0, 10
	addi 	$sp, $sp, -8
	sw 		$t0  0($sp)
	sw		$ra, 4($sp)

	move	$a0, $t0            #a0==t0
	jal 	fib                 #raの値を保存　　jalは飛んだ時にraを自動的に保存
	move 	$t1, $v0            #raにこの行のアドレスが保存される t1は一番最後に入れる結果==v0は戻り値

	lw		$t0, 0($sp)
	lw		$ra, 4($sp)
	addi	$sp, $sp, 8         #スタックをポップする

	jr 		$ra