#include "../include/myVector.h"

template<typename T>
class ReverseIterator {
public:
    using iterator_caotegory = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = myVector<value_type>*;
//    using reference = value_type &;

    explicit ReverseIterator(pointer ptr) : m_ptr(ptr), idx(0) {}

    ReverseIterator(pointer ptr, int index) : m_ptr(ptr), idx(index) {}

    ReverseIterator(const ReverseIterator& other) : m_ptr(other.m_ptr), idx(other.idx) {}

    ReverseIterator& operator=(const ReverseIterator& other) {
        m_ptr = other.m_ptr;
        idx = other.idx;
        return *this;
    }

    const T& operator*() const { return m_ptr->getValue(idx); };

    T* operator->() { return m_ptr->getPointer(idx); };

    ReverseIterator& operator++() {
        if (idx >= 0)
            idx--;
        return *this;
    }

    ReverseIterator operator++(int) {
        const ReverseIterator temp = *this;
        if (idx >= 0)
            idx--;
        return temp;
    }

    ReverseIterator& operator--() {
        if (idx < m_ptr->getSize())
            idx++;
        return *this;
    }

    ReverseIterator operator--(int) {
        const ReverseIterator temp = *this;
        if (idx < m_ptr->getSize())
            idx++;
        return temp;
    }

    friend bool operator==(const ReverseIterator& lhs, const ReverseIterator& rhs) {
        return lhs.idx == rhs.idx && lhs.m_ptr->getValue(lhs.idx) == rhs.m_ptr->getValue(rhs.idx);
    };

    friend bool operator!=(const ReverseIterator& lhs, const ReverseIterator& rhs) {
        return !(lhs == rhs);
    };

private:
    pointer m_ptr;
    int idx;
};