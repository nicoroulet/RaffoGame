#pragma once

template <typename T>
class static_queue {
public:
	static_queue(int s): size(s) {
		array = new T[s];
		begin = end = 0;
	}
	~static_queue() {
		delete[] array;
	}
	void push(T t){
		array[end++] = t;
		end *= (end == size);
	}
	T pop(){
		int aux = begin++;
		begin *= (begin == size);
		return array[aux];
	}

	T top(){
		return array[begin];
	}
	bool isEmpty(){
		return (end == begin);
	}
	
private:
	T * array;
	int begin;
	int end;
	int size;
};


// template <typename T>
// void static_queue<T>::push(T & t) {
// 	array[end++] = t;
// 	end *= (end == size);
// }

// template <typename T>
// T & static_queue<T>::pop() {
// 	int aux = begin++;
// 	begin *= (begin == size);
// 	return array[aux];
// }


// template <typename T>
// T & static_queue<T>::top() {
// 	return array[begin];
// }

// template <typename T>
// bool static_queue<T>::isEmpty() {
// 	return (end == begin);
// }