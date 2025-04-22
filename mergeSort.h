//
// Created by dayri on 4/22/2025.
//

#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

using namespace std;

class mergeSort
{
public:
    void mergehelper(vector<string>& left, vector<string>& right, vector<string>& array);
    void mergesort(vector<string>& array);
};

#endif //MERGESORT_H
