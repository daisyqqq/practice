/*
 * 题：PAT (Advanced Level) Practice 1006 Sign In and Sign Out
 * 解：str_len: 15+1，留最后一位存放'\0'，否则无法判断id字符串结束位置
 */
#include <string.h>
#include "stdio.h"

#define STR_LEN 16

int parse(int hr, int min, int sec) {
    return 3600 * hr + 60 * min + sec;
}

int main() {
    char id[STR_LEN], unlockId[STR_LEN], lockId[STR_LEN];
    int M = 0, hr_in = 0, min_in = 0, sec_in = 0, hr_out = 0, min_out = 0, sec_out = 0,
            earlist = 24 * 3600 + 1, latest = -1, in_tmp = 0, out_tmp = 0;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%s %d:%d:%d %d:%d:%d", id, &hr_in, &min_in, &sec_in, &hr_out, &min_out, &sec_out);
        in_tmp = parse(hr_in, min_in, sec_in);
        out_tmp = parse(hr_out, min_out, sec_out);

        if (in_tmp < earlist) {
            earlist = in_tmp;
            memcpy(unlockId, id, sizeof(char) * STR_LEN);
        }

        if (out_tmp > latest) {
            latest = out_tmp;
            memcpy(lockId, id, sizeof(char) * STR_LEN);
        }
    }
    printf("%s %s\n", unlockId, lockId);
    return 0;
}