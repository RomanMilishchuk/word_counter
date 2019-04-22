#include "concurrent_queue.h"


template<class T>
void ConcurrentQueue<T>::push(T element) {
    std::unique_lock<std::mutex> locker(deque_mutex);
    data.push_back(element);
    queue_check.notify_one();
}

template<class T>
T ConcurrentQueue<T>::pop() {
    std::unique_lock<std::mutex> locker(deque_mutex);
    queue_check.wait(locker, [this]{return !data.empty();});
    T a = data.front();
    data.pop_front();
    return a ;
}