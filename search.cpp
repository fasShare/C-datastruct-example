#include <search.h>
#include <string.h>

int kmp(const char *src, const char *sub, int next[]) {
    int i = 0, j = 0;

    while((i < strlen(src)) && (j < strlen(sub))) {
        if (src[i] == sub[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
            if (j == -1) {
                j = 0;
                ++i;
            }
        }
    }

    if (j == strlen(sub)) {
        return i - strlen(sub);
    }
    return -1;
}

void getnext(const char* sub, int next[]) {
    int i = 0, j = -1;
    next[0] = -1;

    while(i < strlen(sub)) {
        if ((j == -1) || (sub[i] == sub[j])) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int binarySearch(int src[], int low, int high, int obj) {
    if (low > high) {
        return -1;
    }

    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (obj == src[mid]) {
            return mid;
        } else if (obj < src[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

