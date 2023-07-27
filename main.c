#include <stdio.h>

int print(int a, int b, int c, int d, int e, int f, int g) {
    return a + b + c + d;
}
int main() {
    char b = -1;
    printf("%x\n", b);
//    int a = 1;
//    char* p = &a;
//    unsigned int times = 0;
//    for (int i = 0, len = 0x1000;i < len;i++) {
//        unsigned short* current = (p + i);
//        printf ("%x\n", current[0]);
//        if (current[0] == 1) {
//            times++;
//        }
//    }
    char* p = &b;
    __asm__("sgdt %0":"=m"(*p));
}

