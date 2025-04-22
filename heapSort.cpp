//
// Created by daleb on 4/21/2025.
//

#include "heapSort.h"

void heapSort::heapify(vector<string> &arr, int index, int size)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if(left < size && arr[left] > arr[largest])
    {
        largest = left;
    }

    if(right < size && arr[right] > arr[largest])
    {
        largest = right;
    }

    if(largest != index)
    {
        swap(arr[index], arr[largest]);
        heapify(arr, largest, size);
    }
}

void heapSort::sort(vector<string> &arr)
{
    int size = arr.size();

    for(int i =  size/2 -1; i >= 0; i--)
    {
        heapify(arr, i, size);
    }

    for(int i = size-1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}