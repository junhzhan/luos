#include <stdio.h>

int __attribute((stdcall)) print(int a, int b, int c, int d, int e, int f, int g) {
    return a + b + c + d;
}

int add() {
    return 10;
}
struct C {
    char c1;
    int i1;
    char c2;
    char c3;
};
int main() {
    int a = 1;
    char* p = &a;
    unsigned int times = 0;
    printf("%d", sizeof(struct C));
    unsigned int ebp_value;
    __asm__("mov %%ebp, %0":"=r"(ebp_value));
    printf("Value of EBP:%x\n", ebp_value);
//    for (int i = 0, len = 0x1000;i < len;i++) {
//        unsigned short* current = (p + i);
//        printf ("%x\n", current[0]);
//        if (current[0] == 1) {
//            times++;
//        }
//    }
}

