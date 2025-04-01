#include <iostream>

void *memmove(void *dest, const void *src, size_t count) {
    char* pSrc = (char*) src;
    char* pDest = (char*) dest;
    int i = 0;
    if (src > dest) {
        while (i < count) {
            *pDest = *(pSrc+i);
            i++;
        }
    } else {
        i = count - 1;
        while (i >= 0) {
            *pDest = *(pSrc + i);
            i--;
        }
    }
}