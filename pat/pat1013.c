/*
 * 题：PAT (Advanced Level) Practice 1013 Battle Over Cities
 * 解：深搜找components数量，lost city打上-1标记标志由此连出的道路均失效
 */
#include <stdio.h>
#include <string.h>

#define MAX_N 1000

void deepIn(int rootId, int N, int edge[MAX_N][MAX_N], int nodeGet[MAX_N]) {
    nodeGet[rootId] = 1;
    for (int i = 0; i < N; ++i) {
        if ((nodeGet[i] == 0) && (edge[rootId][i] == 1))
            deepIn(i, N, edge, nodeGet);
    }
}

int main() {
    int N, M, K;
    int edge[MAX_N][MAX_N] = {0};
    scanf("%d %d %d", &N, &M, &K);
    int start, end;
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &start, &end);
        edge[start - 1][end - 1] = 1;
        edge[end - 1][start - 1] = 1;
    }

    int city = 0, components = 0;
    int nodeGet[MAX_N] = {0};
    for (int i = 0; i < K; ++i) {
        scanf("%d", &city);
        city = city - 1;
        components = 0;
        memset(nodeGet, 0, sizeof(nodeGet));
        nodeGet[city] = -1;
        for (int j = 0; j < N; ++j) {
            if (nodeGet[j] == 0) {
                deepIn(j, N, edge, nodeGet);
                components++;
            }
        }
        printf("%d\n", components - 1);
    }

    return 0;
}