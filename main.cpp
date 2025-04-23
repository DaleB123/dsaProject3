#include <iostream>
#include "heapSort.h"
int main()
{
    vector<string> arr =  {
        "banana", "apple", "grape", "orange", "mango"
    };
    heapSort heap;
    heap.sort(arr);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}