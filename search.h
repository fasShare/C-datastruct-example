#ifndef SEARCH_H
#define SEARCH_H

int kmp(const char *src, const char *sub, int next[]);
void getnext(const char* sub, int next[]);
int binarySearch(int src[], int low, int high, int obj);

#endif // SEARCH_H
