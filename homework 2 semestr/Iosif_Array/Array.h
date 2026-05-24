#pragma once
#include <iostream>

const int DEFAULT_CAPACITY = 15; 

class ArrayException {};

class Array {
private:
    int* dataBuffer; 
    int currentSize;
    int maxCapacity;

    void reallocateMemory(int suggestedCapacity);

public:
    explicit Array(int initialCapacity = DEFAULT_CAPACITY);
    ~Array();
    Array(const Array& other);
    Array& operator=(const Array& other);

    int& operator[](int index);
    const int& operator[](int index) const;

    void insert(int value, int index);
    void insert(int value);
    void remove(int index);

    int getSize() const;

    friend std::ostream& operator<<(std::ostream& output, const Array& arrayInstance);
};