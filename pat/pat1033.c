/*
 * Q: PAT (Advanced Level) Practice 1033 To Fill or Not to Fill
 * A: greedy algorithm
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXN 501

int cmp(const void *a, const void *b) {
    return *(double *) a - *(double *) b;
}

int reachPoint(int *startPos, int *endPos, double *cost, double tank[MAXN][3], double DPPair[MAXN][2], int point,
               double distance) {
    double distInit = distance;
    for (int j = *startPos; j < *endPos; ++j) {
        if (distance > 0) {
            if ((tank[j][2] - tank[j][1]) > distance) {
                tank[j][1] += distance;
                distance = 0;
                break;
            } else {
                distance -= tank[j][2] - tank[j][1];
                tank[j][1] = tank[j][2];
                (*cost) += tank[j][0] * tank[j][1];
                (*startPos)++;
            }
        }
    }

    //can't reach this point, output max distance
    if (distance > 0) {
        double totalDist = 0;
        totalDist = DPPair[point - 1][0] + distInit - distance;
        printf("The maximum travel distance = %.2lf\n", totalDist);
        return 0;
    }
    return 1;
}

void saveTank(int *startPos, int *endPos, double *cost, double tank[MAXN][3], double DPPair[MAXN][2], int point,
              double maxDist) {
    double spaceUsed = 0;

    //default to be last pos
    int posPut = *endPos;
    for (int i = *startPos; i < *endPos; ++i) {
        if (DPPair[point][1] >= tank[i][0])
            spaceUsed += tank[i][2] - tank[i][1];
        else {
            posPut = i;
            break;
        }
    }
    for (int i = posPut; i < *endPos; ++i) {
        *cost += tank[i][0] * tank[i][1];
    }
    tank[posPut][0] = DPPair[point][1];
    tank[posPut][1] = 0;
    tank[posPut][2] = maxDist - spaceUsed;
    *endPos = posPut + 1;
}

int main() {
    double Cmax = 0, D = 0, Davg = 0;
    int N = 0;
    scanf("%lf %lf %lf %d", &Cmax, &D, &Davg, &N);

    //distance and price pair, first column is distance, second column is price
    double DPPair[MAXN][2] = {0};
    for (int i = 0; i < N; ++i) {
        scanf("%lf %lf", &DPPair[i][1], &DPPair[i][0]);
    }
    qsort(DPPair, N, sizeof(DPPair[0]), cmp);

    double maxDist = Cmax * Davg;
    
    //first column is price, second column is distance used, third column is total distance
    double tank[MAXN][3] = {0};
    int startPos = 0, endPos = 0;
    double cost = 0;
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            if (DPPair[i][0] > 0) {
                printf("The maximum travel distance = 0.00\n");
                return 0;
            }
            tank[0][0] = DPPair[i][1];
            tank[0][1] = 0;
            tank[0][2] = maxDist;
            endPos++;
        } else {
            double distance = DPPair[i][0] - DPPair[i - 1][0];

            //use gas to reach point
            if (reachPoint(&startPos, &endPos, &cost, tank, DPPair, i, distance) == 0) {
                return 0;
            };

            //save new gas into tank
            saveTank(&startPos, &endPos, &cost, tank, DPPair, i, maxDist);

        }
    }

    double leftDist = D - DPPair[N - 1][0];

    //finish final distance after last gas station
    if (reachPoint(&startPos, &endPos, &cost, tank, DPPair, N, leftDist) == 0)
        return 0;
    for (int i = startPos; i < endPos; ++i) {
        cost += tank[i][0] * tank[i][1];
    }
    printf("%.2lf", cost / Davg);

    return 0;
}
