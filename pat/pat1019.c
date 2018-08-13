/*
 * 题：N按照b进制转换后是否是一个对称形式
 * 解：转化为b进制形式后判断对称位置是否相等
 */
#include <stdio.h>

#define MAX_LEN 30

int main() {
    int N, b;
    scanf("%d %d", &N, &b);
    int num[MAX_LEN] = {0};
    int numlen = 0;
    while (N) {
        num[numlen] = N % b;
        N = N / b;
        numlen++;
    }
    int palin = 1;
    for (int i = 0; i < numlen / 2; ++i) {
        if (num[i] != num[numlen - 1 - i]) {
            palin = 0;
            break;
        }
    }
    if (palin)
        printf("Yes\n");
    else
        printf("No\n");
    for (int i = numlen - 1; i > 0; --i) {
        printf("%d ", num[i]);
    }
    printf("%d\n", num[0]);
    return 0;
}