// kernel.c
void graphics_init();
void mouse_install();

void kernel_main() {
    graphics_init();
    mouse_install();

    const char *str = "Hello, MyOS is Running!";
    char *video_memory = (char*) 0xB8000;
    for (int i = 0; str[i] != '\0'; i++) {
        video_memory[i * 2] = str[i];
        video_memory[i * 2 + 1] = 0x07;
    }
}
