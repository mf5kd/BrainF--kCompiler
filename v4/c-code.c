// Auto-generated Brainfuck to C compiler output
#include <stdio.h>

char tape[30000] = {0};
char *ptr = tape;

typedef void (*LoopFunc)(void);
LoopFunc funcTape[256] = {NULL};

void saved_loop_0() {
    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);
    while (*ptr) {
        (*ptr)--;
    }
    ptr--;
}


int main() {
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    while (*ptr) {
        ptr++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        (*ptr)++;
        ptr++;
        (*ptr)++;
        ptr--;
        ptr--;
        (*ptr)--;
    }
    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);
    ptr++;
    (*ptr)++;
    (*ptr)++;
    while (*ptr) {
        (*ptr)--;
    }
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    putchar(*ptr);
    ptr--;
    printf("%d", *ptr);
    ptr++;
    putchar(*ptr);
    ptr--;
    printf("%d", (int)(ptr - tape));
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    (*ptr)++;
    funcTape[(unsigned char)(*ptr)] = saved_loop_0;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    ptr++;
    ptr++;
    ptr++;
    if (funcTape[(unsigned char)(*ptr)] != NULL) {
        funcTape[(unsigned char)(*ptr)]();
    }
    if (funcTape[(unsigned char)(*ptr)] != NULL) {
        funcTape[(unsigned char)(*ptr)]();
    }
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    int temp; scanf("%d", &temp); *ptr = temp;
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    printf("%d", *ptr);
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    *ptr = getchar();
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    ptr++;
    putchar(*ptr);
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    ptr--;
    putchar(*ptr);
    printf("\n");
    return 0;
}
