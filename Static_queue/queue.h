
#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef> // gives access to size_t 
#include <utility>
#include <stdexcept>
#include <iostream>

class queue_error : std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
};


template < typename T, unsigned N > 
class Queue {
    public:

        static_assert(N > 0, "Must have space for at least 1 value");

        void enqueue(T value);
        T dequeue(); 
        bool empty() const; 
        bool full() const; 
        void clear(); 
        T const& front() const;

        template <unsigned M> 
        Queue<T,N+M> copy_and_expand();

    private:
        unsigned head {};
        unsigned tail {};
        T data[N] {};
        unsigned size {};
};

#include "queue.tcc"
#endif