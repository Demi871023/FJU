/*
 * hw.s
 *
 *  Created on: Sep 24, 2019
 *      Author: CS2019
 */
	.equ	num, 101
	.equ	test, 2
	.equ	multiple, 1

.section .rodata
.align 2
.LC0:
	.string "%d "

.LC1:
	.string "\n"

.LC2:
	.string "Prime Generator <100:\n"
	.text
	.global memcpy
	.global main

main:
memcpy:

	la	$r0, .LC2
	bal	printf

	la	$r6, number	!r6載入array的基準位置
	li	$r7, num	!counter

	movi	$r5, #0
	!為了swm.bim指令,給r5數值

.initial:

	smw.bim	$r5, [$r6], $r5, 0
	addi	$r7, $r7, #-1
	bnez	$r7, .initial

	!初始化結束

	la	$r6, number
	!li	$r7, num	!counter

	move	$r7, test
	movi	$r8, #4
	movi	$r15, #1
	movi	$r2, #1

.start:
	sltsi	$r5, $r7, 101	!while(test < 101)
	beqz	$r5, .Finish
	!進入while迴圈
	mul		$r4, $r8, $r7
	add		$r9, $r4, $r6	!得到number[test]的位置地址

	lwi		$r5, [$r9+(0<<2)]
	bnez	$r5, .check	!if(number[test] == 0)

.isPrime:

	sltsi	$r5, $r2, 10
	bnez	$r5, .nochangline
	la		$r0, .LC1
	push	$lp
	bal		printf
	pop		$lp
	movi	$r2, #0

.nochangline:
	move	$r1, $r7
	la		$r0, .LC0
	push	$lp
	bal		printf
	pop		$lp
	addi	$r2, $r2, 1

.check:
	move	$r3, multiple	!int multiple = 1
	mul		$r10, $r7, $r3	!temp = test * multiple

.secondwhile:
	sltsi	$r5, $r10, 101	!while(temp <101)
	beqz	$r5, .NextRound
	!進入while迴圈
	mul		$r4, $r8, $r10
	add		$r9, $r4, $r6
	swi		$r15, [$r9+(0<<2)]
	addi	$r3, $r3, #1
	mul		$r10, $r7, $r3
	j		.secondwhile

.NextRound:
	addi	$r7, $r7, #1
	j	.start

.Finish:
	la	$r0, .LC1
	bal		printf
	ret

number:.skip num * 4
	   .end

