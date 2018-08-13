/*
 * 题：PAT (Advanced Level) Practice 1012 The Best Rank
 * 解：注意同分情况
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_M 10

int comp(const void *a, const void *b) {
    return *((int *) b + 1) - *((int *) a + 1);
}

int main() {
    int N, M, stuId[MAX_N] = {0}, scoreC[MAX_N][3] = {0}, scoreM[MAX_N][3] = {0}, scoreE[MAX_N][3] = {0},
            scoreA[MAX_N][3] = {0}, compId[MAX_M] = {0};
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d %d %d %d", &stuId[i], &scoreC[i][1], &scoreM[i][1], &scoreE[i][1]);
        scoreA[i][1] = (scoreC[i][1] + scoreM[i][1] + scoreE[i][1]) / 3;
        scoreC[i][0] = i;
        scoreM[i][0] = i;
        scoreE[i][0] = i;
        scoreA[i][0] = i;
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d", &compId[i]);
    }
    qsort(scoreC, N, sizeof(scoreC[0]), comp);
    qsort(scoreM, N, sizeof(scoreM[0]), comp);
    qsort(scoreE, N, sizeof(scoreE[0]), comp);
    qsort(scoreA, N, sizeof(scoreA[0]), comp);

    /* deal with same score */
    scoreC[0][2] = 0;
    scoreM[0][2] = 0;
    scoreE[0][2] = 0;
    scoreA[0][2] = 0;
    for (int i = 1; i < N; ++i) {
        if (scoreC[i][1] == scoreC[i - 1][1])
            scoreC[i][2] = scoreC[i - 1][2];
        else
            scoreC[i][2] = i;

        if (scoreM[i][1] == scoreM[i - 1][1])
            scoreM[i][2] = scoreM[i - 1][2];
        else
            scoreM[i][2] = i;

        if (scoreE[i][1] == scoreE[i - 1][1])
            scoreE[i][2] = scoreE[i - 1][2];
        else
            scoreE[i][2] = i;

        if (scoreA[i][1] == scoreA[i - 1][1])
            scoreA[i][2] = scoreA[i - 1][2];
        else
            scoreA[i][2] = i;
    }

    int rank[MAX_N][4] = {0};
    for (int i = 0; i < N; ++i) {
        int a = 0, b = 0;
        a = scoreC[i][0];
        b = scoreC[i][2];
        rank[scoreC[i][0]][1] = scoreC[i][2];
        a = scoreM[i][0];
        b = scoreM[i][2];
        rank[scoreM[i][0]][2] = scoreM[i][2];
        a = scoreE[i][0];
        b = scoreE[i][2];
        rank[scoreE[i][0]][3] = scoreE[i][2];
        a = scoreA[i][0];
        b = scoreA[i][2];
        rank[scoreA[i][0]][0] = scoreA[i][2];
    }

    char symbols[4] = {'A', 'C', 'M', 'E'};
    for (int i = 0; i < M; ++i) {
        int indexId = -1, topRank = MAX_N + 1;
        char symbol;
        for (int j = 0; j < N; ++j) {
            if (compId[i] == stuId[j]) {
                indexId = j;
                break;
            }
        }
        if (indexId == -1) {
            printf("N/A\n");
        } else {
            for (int k = 0; k < 4; ++k) {
                if (rank[indexId][k] < topRank) {
                    topRank = rank[indexId][k];
                    symbol = symbols[k];
                }
            }
            printf("%d %c\n", topRank + 1, symbol);
        }
    }

    return 0;
}