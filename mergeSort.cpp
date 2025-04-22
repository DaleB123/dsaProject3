//
// Created by Bobby on 4/22/2025.
//

#include "mergeSort.h"

void mergeSort::mergehelper(vector<string>& left, vector<string>& right, vector<string>& array)
{
    int leftSize  = left.size();
    int rightSize = right.size();
    int l = 0, r = 0, i = 0;


    while (l < leftSize && r < rightSize) {
        if (left[l] < right[r]) {
            array[i] = left[l];
            l++;
        }
        else {
            array[i] = right[r];
            r++;
        }
        i++;
    }

    while (l < leftSize) {
        array[i] = left[l];
        l++;
        i++;
    }

    while (r < rightSize) {
        array[i] = right[r];
        r++;
        i++;
    }
}

void mergeSort::mergesort(vector<string>& array) {
    int length = array.size();
    if (length <= 1) {
        return;
    }
    int middle = length / 2;
    vector<string> left(middle);
    vector<string> right(length - middle);
    for (int i = 0; i < length; i++) {
        if (i < middle) {
            left[i] = array[i];
        }
        else
            right[i - middle] = array[i];
    }

    mergesort(left);
    mergesort(right);
    mergehelper(left, right, array);
}
