#include "Array.h"

void Array::reallocateMemory(int suggestedCapacity) {
    int newCapacity = (maxCapacity * 3) / 2 + 1;
    if (newCapacity < suggestedCapacity) {
        newCapacity = suggestedCapacity;
    }

    int* tempBuffer = new int[newCapacity];
    for (int i = 0; i < currentSize; ++i) {
        tempBuffer[i] = dataBuffer[i];
    }

    delete[] dataBuffer;
    dataBuffer = tempBuffer;
    maxCapacity = newCapacity;
}

Array::Array(int initialCapacity) {
    maxCapacity = (initialCapacity > 0) ? initialCapacity : DEFAULT_CAPACITY;
    currentSize = 0;
    dataBuffer = new int[maxCapacity];
}

Array::~Array() {
    delete[] dataBuffer;
}

Array::Array(const Array& other) {
    maxCapacity = other.maxCapacity;
    currentSize = other.currentSize;
    dataBuffer = new int[maxCapacity];
    for (int i = 0; i < currentSize; ++i) {
        dataBuffer[i] = other.dataBuffer[i];
    }
}

Array& Array::operator=(const Array& other) {
    if (this != &other) {
        int* tempBuffer = new int[other.maxCapacity];
        for (int i = 0; i < other.currentSize; ++i) {
            tempBuffer[i] = other.dataBuffer[i];
        }
        
        delete[] dataBuffer;
        dataBuffer = tempBuffer;
        maxCapacity = other.maxCapacity;
        currentSize = other.currentSize;
    }
    return *this;
}

int& Array::operator[](int index) {
    if (index < 0 || index >= currentSize) {
        throw ArrayException();
    }
    return dataBuffer[index];
}

const int& Array::operator[](int index) const {
    if (index < 0 || index >= currentSize) {
        throw ArrayException();
    }
    return dataBuffer[index];
}

void Array::insert(int value, int index) {
    if (index < 0 || index > currentSize) {
        throw ArrayException();
    }
    
    if (currentSize >= maxCapacity) {
        reallocateMemory(currentSize + 1);
    }

    int i = currentSize;
    while (i > index) {
        dataBuffer[i] = dataBuffer[i - 1];
        --i;
    }
    
    dataBuffer[index] = value;
    ++currentSize;
}

void Array::insert(int value) {
    if (currentSize >= maxCapacity) {
        reallocateMemory(currentSize + 1);
    }
    dataBuffer[currentSize] = value;
    ++currentSize;
}

void Array::remove(int index) {
    if (index < 0 || index >= currentSize) {
        throw ArrayException();
    }

    for (int i = index; i < currentSize - 1; ++i) {
        dataBuffer[i] = dataBuffer[i + 1];
    }
    --currentSize;
}

int Array::getSize() const {
    return currentSize;
}

std::ostream& operator<<(std::ostream& output, const Array& arrayInstance) {
    for (int i = 0; i < arrayInstance.currentSize; ++i) {
        output << arrayInstance.dataBuffer[i];
        if (i < arrayInstance.currentSize - 1) {
            output << ", ";
        }
    }
    return output;
}