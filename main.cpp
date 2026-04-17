#include <iostream>
#include <string>
using namespace std;

struct Movie {
    string title;
    string duration;
    string rating;
    string showtimes[];
};

int* push(int* arr, int& size, int value) {
    int* newArr = new int[size + 1];

    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];
            
    newArr[size] = value;
    size++;

    delete[] arr;
    return newArr;
}