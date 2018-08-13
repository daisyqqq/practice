/*
 * 题：PAT (Advanced Level) Practice 1020 Tree Traversals
 * 解：以数组形式存放二叉树节点
 */
#include <stdio.h>

#define MAX_NUM 30
#define MAX_NODE 10000

void treeSet(int res[MAX_NODE], int *post, int *in, int len, int rootId) {
    res[rootId] = *(post + len - 1);
    int *temp = in;
    while (1) {
        if ((*temp) == *(post + len - 1))
            break;
        temp++;
    }

    int llen = (temp - in), rlen = len - (temp - in) - 1;
    if (llen > 0)
        treeSet(res, post, in, llen, 2 * rootId + 1);
    if (rlen > 0)
        treeSet(res, post + (temp - in), temp + 1, rlen, 2 * rootId + 2);
}

int main() {
    int N = 0, postorder[MAX_NUM] = {0}, inorder[MAX_NUM] = {0};
    int res[MAX_NODE] = {0};

    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &postorder[i]);
    }
    for (int i = 0; i < N; ++i) {
        scanf("%d", &inorder[i]);
    }
    treeSet(res, postorder, inorder, N, 0);

    int cnt = 0;
    for (int j = 0; j < MAX_NODE; ++j) {
        if (res[j] > 0) {
            cnt++;
            if (cnt < N)
                printf("%d ", res[j]);
            else {
                printf("%d\n", res[j]);
                break;
            }
        }
    }

    return 0;
}