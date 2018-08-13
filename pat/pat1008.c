/*
 * 题：PAT (Advanced Level) Practice 1008 Elevator
 * 解：略
 */
#include <stdio.h>

#define MAX_REQUEST 100

int main() {
    int N, request[MAX_REQUEST] = {0};
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &request[i]);
    }

    for (int j = N - 1; j > 0; --j) {
        request[j] = request[j] - request[j - 1];
    }
    int time = 0;
    for (int k = 0; k < N; ++k) {
        if (request[k] > 0)
            time += request[k] * 6;
        else if (request[k] < 0)
            time += (-request[k]) * 4;
    }
    time += N * 5;
    printf("%d\n", time);

    return 0;
}