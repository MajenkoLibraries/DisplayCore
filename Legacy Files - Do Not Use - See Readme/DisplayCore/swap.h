#ifndef _SWAP_H
#define _SWAP_H

static void inline swap(int &i0, int &i1) {
    int i2 = i0;
    i0 = i1;
    i1 = i2;
}

#endif

