/*
 * 题：PAT (Advanced Level) 1029 Median
 * 解：1. long int会内存超界，int能过, 不知为啥
 *    2. 归并，但第二行可以边读边遍历
 */
#include <stdio.h>

#define MAX_LEN 200005

int main() {
    int N1 = 0, N2 = 0;
    int Seq1[MAX_LEN] = {0};
    scanf("%d", &N1);
    for (int i = 0; i < N1; ++i) {
        scanf("%d", &Seq1[i]);
    }
    scanf("%d", &N2);
    int Seq2num = 0;
    int tmpN2 = N2 - 1;
    if (tmpN2 >= 0) {
        scanf("%d", &Seq2num);
    }

    int midPos = 0;
    int median = 0;
    if ((N1 + N2) % 2 == 0)
        midPos = (N1 + N2) / 2;
    else
        midPos = (N1 + N2) / 2 + 1;

    for (int i = 0; i < N1; ++i) {
        int upper = Seq1[i];
        while ((Seq2num <= upper) && (tmpN2 >= 0)) {
            midPos--;
            median = Seq2num;
            if (midPos == 0) {
                printf("%d\n", median);
                return 0;
            }

            tmpN2--;
            if (tmpN2 >= 0)
                scanf("%d", &Seq2num);
        }
        midPos--;
        median = upper;
        if (midPos == 0) {
            printf("%d\n", median);
            return 0;
        }
    }

    while (tmpN2 >= 0) {
        midPos--;
        median = Seq2num;
        if (midPos == 0) {
            printf("%d\n", median);
            return 0;
        }
        tmpN2--;
        scanf("%d", &Seq2num);
    }
}