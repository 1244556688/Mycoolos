void kernel_main() {
    extern void graphics_init();
    extern void mouse_install();

    graphics_init(); // 初始化畫面
    mouse_install(); // 安裝滑鼠驅動

    // 在螢幕上印出歡迎訊息 (直接寫入 VGA 緩衝區)
    const char *str = "Hello, MyOS is Running with Graphics and Mouse!";
    char *video_memory = (char*) 0xB8000;
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07; // 灰底白字
    }
}
