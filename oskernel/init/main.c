

void kernel_main(int x, short y) {
    int a = x;
    int b = y;
    char d = 0x1ff;
    int c = sizeof(long);
    char* video = (char*)0xb8000;
    *video = 'G';
}