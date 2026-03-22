#include "array.h"
#include <iostream>

Array::Array(int startCapacity) {
    if (startCapacity <= 0)
        capacity = 10;
    else
        capacity = startCapacity;
    ptr = new int[capacity];
    size = 0;
}

Array::~Array() {
    delete[] ptr;
}

Array::Array(const Array& arr) {
    ptr = new int[arr.capacity];
    size = arr.size;
    capacity = arr.capacity;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
}

Array& Array::operator=(const Array& arr) {
    if (this == &arr)
        return *this;
    if (capacity != arr.capacity) {
        delete[] ptr;
        ptr = new int[arr.capacity];
        capacity = arr.capacity;
    }
    size = arr.size;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
    return *this;
}

int& Array::operator[](int index) {
    if (index >= size || index < 0)
        throw ArrayException();
    return ptr[index];
}

void Array::insert(int elem, int index) {
    if (index < 0 || index > size)
        throw ArrayException();
    if (size == capacity)
        increaseCapacity(size + 1);
    for (int j = size - 1; j >= index; j--)
        ptr[j + 1] = ptr[j];
    size++;
    ptr[index] = elem;
}

void Array::insert(int elem) {
    insert(elem, size);
}

void Array::remove(int index) {
    if (index < 0 || index >= size)
        throw ArrayException();
    for (int j = index; j < size - 1; j++)
        ptr[j] = ptr[j + 1];
    ptr[size - 1] = 0;
    size--;
}

void Array::increaseCapacity(int newCapacity) {
    capacity = newCapacity < capacity * 2 ? capacity * 2 : newCapacity;
    int* newPtr = new int[capacity];
    for (int i = 0; i < size; i++)
        newPtr[i] = ptr[i];
    delete[] ptr;
    ptr = newPtr;
}

int Array::getSize() const {
    return size;
}

std::ostream& operator<<(std::ostream& out, const Array& arr) {
    out << "Total size: " << arr.size << std::endl;
    for (int i = 0; i < arr.size; i++)
        out << arr.ptr[i] << " ";
    return out;
}

using namespace std;

int main() {
    try {
        Array arr(5);

        for (int i = 0; i < 5; i++) {
            arr.insert(i * 10);
        }

        cout << "Initial array:" << endl;
        cout << arr << endl;

        arr.insert(99, 2);
        cout << "After insert 99 at index 2:" << endl;
        cout << arr << endl;

        arr.remove(4);
        cout << "After removing index 4:" << endl;
        cout << arr << endl;

        cout << "Element at index 0: " << arr[0] << endl;

    }
    catch (const ArrayException&) {
        cout << "Error: Array index out of range!" << endl;
    }

    return 0;
}