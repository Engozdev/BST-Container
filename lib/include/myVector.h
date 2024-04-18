#ifndef LABWORK8_ENGOZDEV_MYVECTOR_H
#define LABWORK8_ENGOZDEV_MYVECTOR_H
#pragma once

#include <cmath>
#include <cstdint>
#include <iostream>

template<typename T, class Allocator = std::allocator<T>>
class myVector {
public:
    explicit myVector() : capacity(0), index(0), arr(nullptr) {};

    explicit myVector(int size) : capacity(static_cast<int>(pow(2, ceil(log2(static_cast<double>(size)))))),
                                  index(0) {
        arr = elem_allocator.allocate(capacity);
    }

    ~myVector() {
        elem_allocator.deallocate(arr, capacity);
        index = 0;
        capacity = 0;
    }

    myVector(const myVector& other) {
        if (&other == this || &other == nullptr)
            return;
        index = other.index;
        capacity = other.capacity;
        arr = elem_allocator.allocate(capacity);
        for (int i = 0; i < other.index; ++i)
            arr[i] = other.arr[i];
    }

    myVector& operator=(const myVector& other) {
        myVector temp(other);
        index = temp.index;
        capacity = temp.capacity;
        arr = elem_allocator.allocate(capacity);
        for (int i = 0; i < index; ++i)
            arr[i] = temp.arr[i];
        return *this;
    }
    
    void clear() {
        if (capacity < 1)
            return;
        elem_allocator.deallocate(arr, capacity);
        index = 0;
        capacity = 0;
        arr = nullptr;
    }

    T& operator[](int idx) {
        return arr[idx];
    }

    void enlargeVector() {
        capacity > 0 ? capacity <<= 1 : capacity++;
        T* temp = elem_allocator.allocate(capacity);
        for (int i = 0; i < index; ++i) temp[i] = arr[i];
        if (capacity > 1)
            elem_allocator.deallocate(arr, index);
        arr = temp;
    }

    void push_back(const T& val) {
        if (index == capacity)
            enlargeVector();
        arr[index++] = val;
    }

    void print_capacity() {
        std::cout << capacity << std::endl;
    }

    int getSize() {
        return index;
    }

    const T& getValue(int idx) const {
        return arr[idx];
    }

    T* getPointer(int idx) {
        return arr + idx;
    }

    friend bool operator==(const myVector& lhs, const myVector& rhs) {
        if (lhs.index == rhs.index) {
            for (int i = 0; i < lhs.index; ++i) {
                if (lhs.getValue(i) != rhs.getValue(i))
                    return false;
            }
            return true;
        }
        return false;
    }

private:
    T* arr;
    int index, capacity;
    std::allocator<T> elem_allocator = Allocator();
};


#endif //LABWORK8_ENGOZDEV_MYVECTOR_H
