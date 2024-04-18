#include "../include/myVector.h"

template<typename T>
class Iterator {
public:
    using iterator_caotegory = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = myVector<value_type>*;
//    using reference = value_type&;

    explicit Iterator(pointer ptr) : m_ptr(ptr), idx(0) {}

    Iterator(pointer ptr, int index) : m_ptr(ptr), idx(index) {}

    Iterator(const Iterator& other) : m_ptr(other.m_ptr), idx(other.idx) {}

    Iterator& operator=(const Iterator& other) {
        m_ptr = other.m_ptr;
        idx = other.idx;
        return *this;
    }

    const T& operator*() { return m_ptr->getValue(idx); };

    T* operator->() { return m_ptr->getPointer(idx); };

    Iterator& operator++() {
        if (idx < m_ptr->getSize())
            idx++;
        return *this;
    }

    Iterator operator++(int) {
        const Iterator temp = *this;
        if (idx < m_ptr->getSize())
            idx++;
        return temp;
    }

    Iterator& operator--() {
        if (idx >= 0)
            idx--;
        return *this;
    }

    Iterator operator--(int) {
        const Iterator temp = *this;
        if (idx >= 0)
            idx--;
        return temp;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
        return lhs.idx == rhs.idx && lhs.m_ptr->getValue(lhs.idx) == rhs.m_ptr->getValue(rhs.idx);
    };

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
        return !(lhs == rhs);
    };

private:
    pointer m_ptr;
    int idx;
};