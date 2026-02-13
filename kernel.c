// kernel.c
/* 定義 VGA 顯示記憶體位置 */
volatile char *video_memory = (volatile char*)0xB8000;

/* 顏色定義 */
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW 0xE
#define WHITE 0xF

/* 清除螢幕並填滿顏色 */
void clear_screen(char color) {
    for (int i = 0; i < 80 * 25 * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = color;
    }
}

/* 在指定位置寫字 */
void print_string(int x, int y, char *string, char color) {
    int index = (y * 80 + x) * 2;
    for (int i = 0; string[i] != 0; i++) {
        video_memory[index + i * 2] = string[i];
        video_memory[index + i * 2 + 1] = color;
    }
}

/* 畫一個方框 (視窗) */
void draw_box(int x, int y, int width, int height, char color, char border_color) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = ((y + i) * 80 + (x + j)) * 2;
            video_memory[index] = ' '; // 內部空白
            video_memory[index + 1] = color;

            // 繪製邊框
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                video_memory[index] = '#'; // 簡單的邊框樣式
                video_memory[index + 1] = border_color;
            }
        }
    }
}

/* 核心進入點 */
void kernel_main() {
    // 1. 設定背景為藍色 (經典藍白當機風格，但這是運作正常的藍色！)
    clear_screen((BLUE << 4) | WHITE);

    // 2. 畫一個主視窗
    draw_box(20, 5, 40, 15, (LIGHT_GREY << 4) | BLACK, (BLACK << 4) | WHITE);

    // 3. 畫標題列
    draw_box(20, 5, 40, 3, (RED << 4) | YELLOW, (BLACK << 4) | WHITE);
    print_string(28, 6, " GEMINI OS KERNEL ", (RED << 4) | YELLOW);

    // 4. 顯示歡迎訊息
    print_string(25, 9, "Welcome back, Commander.", (LIGHT_GREY << 4) | BLACK);
    print_string(25, 11, "System Status: ONLINE", (LIGHT_GREY << 4) | GREEN);
    print_string(25, 12, "Security Level: MAXIMUM", (LIGHT_GREY << 4) | RED);
    
    // 5. 底部狀態列
    print_string(0, 24, " [F1] Help  [F2] Reboot  [F12] Self-Destruct", (BLACK << 4) | WHITE);
}
