/*
 * Q：PAT (Advanced Level) Practice 1030 Travel Plan
 * A：dijkstra algorithm to find shortest path and use a prevNode array to record prevNode for future traverse
 */
#include <stdio.h>

#define MAX_CITY 501
#define MAX_NUM 501

// find min distance/cost nextNode to traverse
int minDist(int N, int DDist[MAX_CITY], int DCost[MAX_CITY], int included[MAX_CITY]) {
    int minNode = MAX_NUM, minDist = MAX_NUM, minCost = MAX_NUM;
    for (int i = 0; i < N; ++i) {
        if (included[i] == 0) {
            if ((DDist[i] < minDist) || ((DDist[i] == minDist) && (DCost[i] < minCost))) {
                minNode = i;
                minDist = DDist[i];
                minCost = DCost[i];
            }
        }
    }
    return minNode;
}

void Dijkstra(int N, int S, int D, int Dist[MAX_CITY][MAX_CITY], int Cost[MAX_CITY][MAX_CITY],
              int DDist[MAX_CITY], int DCost[MAX_CITY], int track[MAX_CITY], int prevNode[MAX_CITY]) {
    int included[MAX_CITY] = {0};
    int nextNode = -1, nodePut = 0;

    while (nextNode != D) {
        if (nextNode == -1)
            nextNode = S;
        else
            nextNode = minDist(N, DDist, DCost, included);
        track[nodePut] = nextNode;
        included[nextNode] = 1;
        nodePut++;

        if (nextNode == S) {
            for (int i = 0; i < N; ++i) {
                DDist[i] = Dist[nextNode][i];
                DCost[i] = Cost[nextNode][i];
                if (DDist[i] < MAX_NUM)
                    prevNode[i] = nextNode;
            }
        } else {
            for (int i = 0; i < N; ++i) {
                if (included[i] == 0) {
                    //update distance and cost for new nextNode
                    int distTmp = DDist[nextNode] + Dist[nextNode][i];
                    int costTmp = DCost[nextNode] + Cost[nextNode][i];
                    if ((distTmp < DDist[i]) || ((distTmp == DDist[i]) && (costTmp < DCost[i]))) {
                        prevNode[i] = nextNode;
                        DDist[i] = distTmp;
                        DCost[i] = costTmp;
                    }
                }
            }
        }
    }
}

int main() {
    int N, M, S, D;
    int Dist[MAX_CITY][MAX_CITY] = {0}, Cost[MAX_CITY][MAX_CITY] = {0};

    //get input N,M,S,D
    scanf("%d %d %d %d", &N, &M, &S, &D);

    //initialize Dist and Cost to MAX_NUM for future comparision
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i != j) {
                Dist[i][j] = MAX_NUM;
                Cost[i][j] = MAX_NUM;
            }
        }
    }

    //get input distance and cost
    for (int i = 0; i < M; ++i) {
        int city1 = 0, city2 = 0, distance = 0, cost = 0;
        scanf("%d %d %d %d", &city1, &city2, &distance, &cost);
        Dist[city1][city2] = distance;
        Dist[city2][city1] = distance;
        Cost[city1][city2] = cost;
        Cost[city2][city1] = cost;
    }

    //Dijkstra algorithm to find shortest path, prevNode for future traverse
    int track[MAX_CITY] = {0}, DDist[MAX_CITY] = {0}, DCost[MAX_CITY] = {0}, prevNode[MAX_CITY] = {0};
    Dijkstra(N, S, D, Dist, Cost, DDist, DCost, track, prevNode);

    //print result
    int revNum = 0, Reverse[MAX_CITY] = {0};
    Reverse[0] = D;
    revNum++;
    for (; revNum < N; ++revNum) {
        Reverse[revNum] = prevNode[Reverse[revNum - 1]];
        if (Reverse[revNum] == S)
            break;
    }
    for (int i = revNum; i >= 0; --i) {
        printf("%d ", Reverse[i]);
    }
    printf("%d %d\n", DDist[D], DCost[D]);

    return 0;
}