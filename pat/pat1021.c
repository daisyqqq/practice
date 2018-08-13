/*
 * 题：PAT (Advanced Level) Practice 1021 Deepest Root
 * 解：任一节点出发得到最深的一个叶节点，再从该叶节点出发得到的所有最深叶节点包括此根节点为deepest root
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 10000


int comp(const void *a, const void *b)//用来做比较的函数。
{
    return *(int *) a - *(int *) b;
}

void deepIn(int rootId, int edge[MAX_NUM * 2][2], int neighbor[MAX_NUM], int nodeGet[MAX_NUM], int N) {
    int startPos = 0;
    while ((edge[startPos][0] != rootId) && (startPos < 2 * N))
        startPos++;
    if (startPos == 2 * N)
        return;
    for (int i = 0; i < neighbor[rootId]; ++i) {
        if (nodeGet[edge[startPos + i][1]] == -1) {
            nodeGet[edge[startPos + i][1]] = nodeGet[rootId] + 1;
            deepIn(edge[startPos + i][1], edge, neighbor, nodeGet, N);
        }
    }
}

int main() {
    int N = 0;
    int edge[MAX_NUM * 2][2] = {0};
    memset(edge, -1, sizeof(edge));
    scanf("%d", &N);
    int cnt = N;
    int start = 0, end = 0, edgeCnt = 0;

    if (N == 1) {
        printf("1\n");
        return 0;
    }
    while (--cnt) {
        scanf("%d %d", &start, &end);
        edge[edgeCnt][0] = start - 1;
        edge[edgeCnt++][1] = end - 1;
        edge[edgeCnt][0] = end - 1;
        edge[edgeCnt++][1] = start - 1;
    }
    qsort(edge, (N - 1) * 2, sizeof(int) * 2, comp);//调用qsort排序

    int neighbor[MAX_NUM];
    for (int i = 0; i < 2 * (N - 1); ++i) {
        neighbor[edge[i][0]]++;
    }

    int deepest[MAX_NUM] = {0};
    int nodeGet[MAX_NUM] = {0};
    int components = 0;
    memset(nodeGet, -1, sizeof(nodeGet));
    for (int i = 0; i < N; ++i) {
        if (nodeGet[i] == -1) {
            nodeGet[i] = 0;
            deepIn(i, edge, neighbor, nodeGet, N);
            components++;
        }
    }
    int secondPos = 0, maxDepth = 0;
    if (components == 1) {
        for (int i = 0; i < N; ++i) {
            if (nodeGet[i] > maxDepth) {
                maxDepth = nodeGet[i];
                secondPos = i;
            }
        }
        for (int k = 0; k < N; ++k) {
            if (nodeGet[k] == maxDepth)
                deepest[k] = 1;
        }
        memset(nodeGet, -1, sizeof(nodeGet));
        nodeGet[secondPos] = 0;
        deepIn(secondPos, edge, neighbor, nodeGet, N);
        maxDepth = 0;
        for (int i = 0; i < N; ++i) {
            if (nodeGet[i] > maxDepth) {
                maxDepth = nodeGet[i];
            }
        }
        for (int k = 0; k < N; ++k) {
            if (nodeGet[k] == maxDepth)
                deepest[k] = 1;
        }
        for (int j = 0; j < N; ++j) {
            if (deepest[j] == 1)
                printf("%d\n", j + 1);
        }
    } else {
        printf("Error: %d components\n", components);
    }

    return 0;
}