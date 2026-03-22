#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class ArrayException {};

class Array {
    int* ptr;
    int size;
    int capacity;

    void increaseCapacity(int newCapacity);

public:
    explicit Array(int startCapacity = 10);
    ~Array();
    Array(const Array& arr);
    Array& operator=(const Array& arr);

    int& operator[](int index);
    void insert(int elem, int index);
    void insert(int elem);
    void remove(int index);
    int getSize() const;

    friend std::ostream& operator<<(std::ostream& out, const Array& arr);
};

#endif