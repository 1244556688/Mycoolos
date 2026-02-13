# 設定 Multiboot 標準參數
.set ALIGN,    1<<0             
.set MEMINFO,  1<<1             
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002       
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
    
	# 注意：在 GNU as 中，不需要寫 extern kernel_main
	call kernel_main        
    
	cli
1:	hlt                     
	jmp 1b
