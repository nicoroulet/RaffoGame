#pragma once

template<typename T, typename comp>
class sorted_array {
private:
    T * array;
    int _size;


public:
    sorted_array(int max_size) {
        array = new T[max_size];
        _size = 0;
    }

    ~sorted_array() {
        delete[] array;
    }

    void insert(T t) {
        array[_size] = t;
        int i = _size;
        while (--i >= 0 && comp()(array[i], array[i+1])) {
            T aux = array[i];
            array[i] = array[i+1];
            array[i+1] = aux;
        }
        ++_size;
    }

    void resort() {
        for (int i = 0; i < _size; ++i)
        {
            int j = i;
            while (--j >= 0 && comp()(array[j+1], array[j])) {
                T aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
            }
        }
    }

    void erase(int i) {
        --_size;
        for (int j = i; j < _size; ++j)
        {
            array[j] = array[j+1];
        }
    }

    int size() {
        return _size;
    }


    T & operator[](int i) {
        return array[i];
    }

    class iterator {
    private:
        T * it;
    public:
        iterator(T * t) : it(t) {}
        iterator operator++() {
            ++it;
            return *this;
        }
        iterator operator--() {
            --it;
            return *this;
        }
        T& operator*() {
            return *it;
        }
        bool operator!=(const iterator &other) {
            return it != other.it;
        }
    };

    class reverse_iterator {
    private:
        T * it;
    public:
        reverse_iterator(T * t) : it(t) {}
        reverse_iterator & operator++() {
            --it;
            return *this;
        }
        reverse_iterator & operator--() {
            ++it;
            return *this;
        }
        T& operator*() {
            return *it;
        }

        bool operator!=(const reverse_iterator &other) {
            return it != other.it;
        }
    };
    iterator begin() {return iterator(array);}

    iterator end() {return iterator(array + _size);}

    reverse_iterator rbegin() {return reverse_iterator(array + _size - 1);}

    reverse_iterator rend() {return reverse_iterator(array - 1);}
};