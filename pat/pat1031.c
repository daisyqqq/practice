/*
 * Q: PAT (Advanced Level) Practice 1031 Hello World for U
 * A: omit
 */
#include <stdio.h>
#include <memory.h>

#define MAX_CHAR 10

int main() {
    char str[MAX_CHAR] = {'\0'};
    scanf("%s", str);
    int N = strlen(str);
    int n1 = (N + 2) / 3 - 1, n2 = N - n1 * 2;
    for (int i = 0; i < n1; ++i) {
        printf("%c", str[i]);
        for (int j = 0; j < n2 - 2; ++j) {
            printf(" ");
        }
        printf("%c\n", str[N - 1 - i]);
    }
    for (int i = 0; i < n2 - 1; ++i) {
        printf("%c", str[i + n1]);
    }
    printf("%c\n", str[n1 + n2 - 1]);
    printf("Hello, World!\n");
    return 0;
}