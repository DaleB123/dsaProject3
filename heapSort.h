//
// Created by daleb on 4/21/2025.
//

#ifndef HEAPSORT_H
#define HEAPSORT_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class heapSort {
    public:
        void heapify(vector<string> &arr, int index, int size);
        void sort(vector<string>& arr);
};



#endif //HEAPSORT_H
