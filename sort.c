#include <sort.h>

void adjustDown(int src[], int st, int len) {
    int temp = src[st];
    int i = 0;
    for (i = 2 * st; i < len; i *= 2) {
        if (i < len -1 && src[i] < src[i + 1]) {
            i++;
        }
        if (temp >= src[i]) {
            break;
        }
        src[st] = src[i];
        st = i;
    }
    src[st] = temp;
}

void buildHeap(int src[], int len) {
    int i = 0;
    for (i = len / 2; i >= 0; --i) {
        adjustDown(src, i, len);
    }
}

void heapSort(int src[], int len) {
    buildHeap(src, len);
    int i = 0;
    for (i = len - 1; i >= 0; --i) {
        int temp = src[i];
        src[i] = src[0];
        src[0] = temp;
        adjustDown(src, 0, i);
    }
}

void __quickSort(int src[], int low, int high) {
    int lowt = low, hight = high;
    if (low < high) {
        int pivot = src[low];
        while (low < high) {
            while (low < high && src[high] >= pivot) --high;
            src[low] = src[high];
            while (low < high && src[low] <= pivot) ++low;
            src[high] = src[low];
        }
        src[low] = pivot;
        __quickSort(src, lowt, low -1);
        __quickSort(src, low + 1, hight);
    }
}

void quickSort(int src[], int len) {
   if (len > 0) {
       __quickSort(src, 0, len);
   }
}

void shellSort(int src[], int len) {
    int i = 0, j = 0;

    for (i = (len) / 2; i > 0; i = i / 2) {
        for (j = i; j < len; j++) {
            if (src[j - i] >= src[j]) {
                int temp = src[j];
                src[j] = src[j - i];
                src[j - i] = temp;
            }
        }
    }
}

void bubbleSort(int src[], int n) {
    int i = 0, j = 0, flag = 1;

    for (i = n - 1; i >= 1; --i) {
        flag = 0;
        for (j = 1; j <= i; j++) {
            if (src[j - 1] > src[j]) {
                int temp = src[j];
                src[j] = src[j - 1];
                src[j - 1] = temp;

                flag = 1;
            }
        }

        if (flag = 0) {
            break;
        }
    }
}

void binaryInsertSort(int src[], int len) {
    int j = 1, k = j;
    int insertPos = 0;
    int temp = src[j];
    while (j < len) {
        temp = src[j];
        int low = 0, high = j - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (temp < src[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        for (k = j - 1; k >= low; --k) {
            src[k + 1] = src[k];
        }
        src[k + 1] = temp;
        ++j;
    }
}
