#include <stdint.h>

// 向連接埠輸出資料
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void mouse_install() {
    // 簡單的 PS/2 滑鼠啟用序列
    outb(0x64, 0xA8); // 啟用第二個 PS/2 設備 (滑鼠)
    outb(0x64, 0x20); // 讀取控制暫存器
    // ... 後續還需要中斷處理 (IDT)，此處僅為結構範例
}
