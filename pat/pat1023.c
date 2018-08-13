/*
 * 题：PAT (Advanced Level) Practice 1023 Have Fun with Numbers
 * 解：模拟加法过程，同时开两个数组记录0-9数字在前后数据中的个数
 */
#include <stdio.h>

#define MAX_DIGIT 21

int main() {
    int num[MAX_DIGIT] = {0}, init[10] = {0}, doub[10] = {0}, offset[MAX_DIGIT] = {0};
    char digit;
    int numlen = 0;
    while (scanf("%c", &digit) && (digit != '\n')) {
        num[numlen] = digit - '0';
        numlen++;
    }

    int temp = 0;
    for (int i = numlen - 1; i >= 0; --i) {
        init[num[i]] = 1;
        temp = num[i] * 2 + offset[i + 1];
        if (temp >= 10) {
            offset[i] = 1;
        }
        num[i] = temp % 10;
        doub[num[i]] = 1;
    }

    if (offset[0] == 1) {
        printf("No\n");
    } else {
        int same = 1;
        for (int i = 0; i < 10; ++i) {
            if (init[i] != doub[i]) {
                same = 0;
                break;
            }
        }
        if (same == 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
    
    if (offset[0] == 1)
        printf("1");
    for (int i = 0; i < numlen; ++i) {
        printf("%d", num[i]);
    }

    printf("\n");
    return 0;
}