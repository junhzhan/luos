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
}__attribute__((packed));
struct point {
    int x;
    int y;
};

struct point make_point(int x, int y) {
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

int main() {
    int a = 1;
    char* p = &a;
    unsigned int times = 0;
    printf("%d", sizeof(struct C));
    unsigned int ebp_value;
    __asm__("mov %%ebp, %0"::"m"(*p));
    printf("Value of EBP:%x\n", a);
    struct point x = make_point(2, 3);

//    for (int i = 0, len = 0x1000;i < len;i++) {
//        unsigned short* current = (p + i);
//        printf ("%x\n", current[0]);
//        if (current[0] == 1) {
//            times++;
//        }
//    }
}

