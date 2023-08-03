#include <stdio.h>

int __attribute((stdcall)) print(int a, int b, int c, int d, int e, int f, int g) {
    return a + b + c + d;
}

int add() {
    return 10;
}
struct C {
    char c1;
    char c2;
    char c3;
}__attribute((packed));
int main() {
    int a = 1;
    char* p = &a;
    unsigned int times = 0;
    for (int i = 0, len = 0x1000;i < len;i++) {
        unsigned short* current = (p + i);
        printf ("%x\n", current[0]);
        if (current[0] == 1) {
            times++;
        }
    }
}

