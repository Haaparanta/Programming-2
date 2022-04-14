#include "array_operations.hh"

int greatest_v1(int* itemptr, int size){
    int max = 0;
    int* pointer = itemptr;

    for (;pointer < itemptr + size; pointer++) {

        if (*pointer > max){
            max = *pointer;
        }
    }
    return max;
}

int greatest_v2(int* itemptr, int* endptr){
    int max = 0;

    for (;itemptr < endptr; itemptr++){
        if (*itemptr > max){
            max = *itemptr;
        }
    }
    return max;
}

void copy(int* itemptr, int* endptr, int* targetptr){
    for (;endptr > itemptr; itemptr++){
        *targetptr = *itemptr;
        targetptr++;
    }
}

void reverse(int* leftptr, int* rightptr){
    for (;--rightptr > leftptr; ++leftptr){
        int cache = *leftptr;
        *leftptr = *rightptr;
        *rightptr = cache;
    }
}
