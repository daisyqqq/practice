/*
 * 题：PAT (Advanced Level) Practice 1011 World Cup Betting
 * 解：取三个最大值
 */
#include <stdio.h>

int main() {
    double rate[3][3] = {0};
    char choose[3] = {'W', 'T', 'L'};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%lf", &rate[i][j]);
        }
    }
    double maxRate[3] = {0};
    int odd = 0;
    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < 3; ++i) {
            if (rate[k][i] > maxRate[k]) {
                maxRate[k] = rate[k][i];
                odd = i;
            }
        }
        printf("%c ", choose[odd]);
    }
    double sum = (maxRate[0] * maxRate[1] * maxRate[2] * 0.65 - 1) * 2;
    sum = (sum * 100 + 0.5) / 100;
    printf("%.2lf\n", sum);
    return 0;
}