#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "static3d.h"

#define SWP(A, B, T) T = A; A = B; B = T;

static int qsval = 0;

static void quicksort(triangle *tri, int first, int last) {
    int pivot, j, i;
    double td;
    int ti;

    // Limit the sorting so it doesn't overflow the stack
    qsval++;
    if (qsval > 100) {
        qsval--;
        return;
    }

    if (first < last) {
        pivot = first;
        i = first;
        j = last;
        double zp = zentroid(&tri[pivot]);

        while (i < j) {
            while (zentroid(&tri[i]) <= zp && i < last) {
                i++;
            }
            while (zentroid(&tri[j]) > zp) {
                j--;
            }
            if (i < j) {
                SWP(tri[i].a.x, tri[j].a.x, td);
                SWP(tri[i].a.y, tri[j].a.y, td);
                SWP(tri[i].a.z, tri[j].a.z, td);
                SWP(tri[i].b.x, tri[j].b.x, td);
                SWP(tri[i].b.y, tri[j].b.y, td);
                SWP(tri[i].b.z, tri[j].b.z, td);
                SWP(tri[i].c.x, tri[j].c.x, td);
                SWP(tri[i].c.y, tri[j].c.y, td);
                SWP(tri[i].c.z, tri[j].c.z, td);
                SWP(tri[i].color, tri[j].color, ti);
                SWP(tri[i].flags, tri[j].flags, ti);
            }
        }
        SWP(tri[pivot].a.x, tri[j].a.x, td);
        SWP(tri[pivot].a.y, tri[j].a.y, td);
        SWP(tri[pivot].a.z, tri[j].a.z, td);
        SWP(tri[pivot].b.x, tri[j].b.x, td);
        SWP(tri[pivot].b.y, tri[j].b.y, td);
        SWP(tri[pivot].b.z, tri[j].b.z, td);
        SWP(tri[pivot].c.x, tri[j].c.x, td);
        SWP(tri[pivot].c.y, tri[j].c.y, td);
        SWP(tri[pivot].c.z, tri[j].c.z, td);
        SWP(tri[pivot].color, tri[j].color, ti);
        SWP(tri[pivot].flags, tri[j].flags, ti);
        quicksort(tri, first, j-1);
        quicksort(tri, j+1, last);
    }
    qsval--;
}

#endif
