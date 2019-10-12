#pragma once


template<typename T>
void insertionSort(T *start, T *end);

template<typename T>
T pivot_func(const T *start, const T *end);

template<typename T, typename Compare>
void QSort(T *first, T *last, const Compare &comp);

#include "QSort.cpp"