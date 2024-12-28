

template <typename T, unsigned N>
void Queue<T, N>::enqueue(T value) {
    if (full()) {
        throw queue_error {"Cannot enqueue to a full queue."};
    }
    data[(tail++) % N] = value;
    ++size;
}

template <typename T, unsigned N>
T Queue<T,N>::dequeue() {
    if (empty()) {
        throw queue_error {"Cannot dequeue a empty queue."};
    }
    T value {std::move(data[(head++) % N])};
    --size;
    return value; 
}

template <typename T, unsigned N>
bool Queue<T,N>::empty() const {
    return size == 0;
}

template <typename T, unsigned N>
bool Queue<T,N>::full() const{
    return size == N;
}

template <typename T, unsigned N>
void Queue<T,N>::clear() {
    head = tail = size = 0;
}

template <typename T, unsigned N>
T const& Queue<T,N>::front() const {
    if (empty()) {
        throw queue_error {"Cannot peek in a empty queue" };
    }
    return data[head % N];
}

template <typename T, unsigned N>
template <unsigned M> 
Queue<T,N+M> Queue<T,N>::copy_and_expand() {
    Queue<T, N+M> result;
    for (unsigned int i{0}; i < size; ++i) {
        T value = data[ (i+head) % N];
        result.enqueue(value);
    }
    return result;
}