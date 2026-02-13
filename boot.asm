; boot.asm
global start
extern kernel_main

section .multiboot
    align 4
    dd 0x1BADB002            ; Magic number
    dd 0x00                  ; Flags
    dd - (0x1BADB002 + 0x00) ; Checksum

section .text
bits 32
start:
    cli                     ; 關閉中斷
    mov esp, stack_space    ; 設定堆疊指標
    call kernel_main        ; 呼叫 C 語言核心
    hlt                     ; 停止執行

section .bss
resb 8192                   ; 8KB 堆疊空間
stack_space:
