#pragma once

#include <iostream>
#include <vector>

template <typename T>
class static_queue {
public:
    static_queue(int s): size(s), array(s) {
        begin = end = 0;
        std::cerr << size << " sq\n";
    }
    ~static_queue() {
        std::cerr << "Destroying static_queue\n";
    }
    // ~static_queue() {
    //  delete[] array;
    // }
    void push(T t){
        // array[end++] = t;
        // end *= (end == size);
        array[end] = t;
        std::cerr << end << " push\n";
        end = (end+1) % size;
    }
    T pop(){
        // int aux = begin++;
        // begin *= (begin == size);
        std::cerr << end << " pop\n";
        int aux = begin;
        begin = (begin + 1) % size;
        return array[aux];
    }

    T front(){
        std::cerr << end << " front\n";
        return array[begin];
    }
    bool empty(){
        return (end == begin);
    }

private:
    std::vector<T> array;
    int begin;
    int end;
    int size;
};


// template <typename T>
// void static_queue<T>::push(T & t) {
//  array[end++] = t;
//  end *= (end == size);
// }

// template <typename T>
// T & static_queue<T>::pop() {
//  int aux = begin++;
//  begin *= (begin == size);
//  return array[aux];
// }


// template <typename T>
// T & static_queue<T>::top() {
//  return array[begin];
// }

// template <typename T>
// bool static_queue<T>::isEmpty() {
//  return (end == begin);
// }