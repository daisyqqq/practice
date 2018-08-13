/*
 * 题：PAT (Advanced Level) Practice 1015 Reversible Primes
 * 解：略
 */
#include <stdio.h>
#include <math.h>

// tansfer to radix 10
int transfer(int N, int radix) {
    int sum = 0;
    while (N > 0) {
        sum = sum * radix + N % radix;
        N = N / radix;
    }
    return sum;
}

int isPrime(int n) {
    if (n == 1) {
        return 0;
    } else if (n == 2) {
        return 1;
    } else if (n % 2 == 0) {
        return 0;
    } else {
        for (int i = 3; i <= ceil(sqrt(n)); i = i + 2) {
            if (n % i == 0)
                return 0;
        }
        return 1;
    }
}

int main() {
    int num = 0, radix = 0;
    while (scanf("%d %d", &num, &radix) && (num > 0)) {
        if (isPrime(num) && isPrime(transfer(num, radix)))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}