# 設定 Multiboot 標準參數
.set ALIGN,    1<<0             # 頁面對齊
.set MEMINFO,  1<<1             # 提供記憶體地圖
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002       # 核心魔數 (GRUB 識別用)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 預留 16 KiB 堆疊空間
stack_top:

.section .text
.global _start
_start:
	mov $stack_top, %esp    # 設定堆疊指針
	extern kernel_main
	call kernel_main        # 進入 C 語言核心
	cli
1:	hlt                     # 當核心結束時進入死迴圈
	jmp 1b
