/*
 * 题：PAT (Advanced Level) Practice 1010 Radix
 * 解：radix检查范围（最大radix为num1+1），若直接顺序查找会超时，采用二分查找
 */
#include <stdio.h>
#include <cmath>
#include <string.h>

#define DIGIT_NUM 11
typedef long long ll;

// tansfer to radix 10
ll transfer(char N[DIGIT_NUM], int radix) {
    int digits = 0, i = 0, num = 0;
    ll sum = 0;

    while (N[i++] != '\0')
        digits++;
    for (int i = 0; i < digits; ++i) {
        if ((N[i] >= 'a') && (N[i] <= 'z'))
            num = N[i] - 'a' + 10;
        else if ((N[i] >= '0') && (N[i] <= '9'))
            num = N[i] - '0';
        else
            return -1;
        sum += pow(radix, digits - i - 1) * num;
    }

    return sum;
}

int main() {
    char num[2][DIGIT_NUM] = {};
    int tag = 0, radix = 0;
    scanf("%s %s %d %d", num[0], num[1], &tag, &radix);
    ll compareOne = transfer(num[tag - 1], radix);
    ll minRadix = 2, maxRadix = compareOne + 1;

    for (int i = 0; i < strlen(num[2 - tag]); ++i) {
        if ((num[2 - tag][i] - 'a') >= 0) {
            if ((num[2 - tag][i] - 'a' + 11) > minRadix)
                minRadix = num[2 - tag][0] - 'a' + 11;
        } else {
            if ((num[2 - tag][i] - '0' + 1) > minRadix)
                minRadix = num[2 - tag][0] - '0' + 1;
        }
    }

    ll tmpRadix = 0, lRadix = minRadix, rRadix = maxRadix;
    ll lRes = 0, rRes = 0, mRes = 0;

    if (strlen(num[2 - tag]) == 1) {
        if (transfer(num[2 - tag], minRadix) == compareOne)
            tmpRadix = minRadix;
    } else {
        while (1) {
            lRes = transfer(num[2 - tag], lRadix);
            rRes = transfer(num[2 - tag], rRadix);
            mRes = transfer(num[2 - tag], (lRadix + rRadix) / 2);
            if (lRes == compareOne) {
                tmpRadix = lRadix;
                break;
            } else if (rRes == compareOne) {
                tmpRadix = rRadix;
                break;
            } else if (mRes == compareOne) {
                tmpRadix = (lRadix + rRadix) / 2;
                break;
            } else if ((mRes < 0) || ((mRes - compareOne) > 0)) {
                if (rRadix == (lRadix + rRadix) / 2)
                    break;
                rRadix = (lRadix + rRadix) / 2;
            } else if ((mRes - compareOne) < 0) {
                if (lRadix == (lRadix + rRadix) / 2)
                    break;
                lRadix = (lRadix + rRadix) / 2;
            }

        }
    }

    if (tmpRadix == 0)
        printf("Impossible\n");
    else
        printf("%lld", tmpRadix);

    return 0;
}