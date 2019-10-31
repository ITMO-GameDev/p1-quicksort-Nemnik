#include "Header.h"

template<typename T>
Array<T>::Array() {
	capacity = 16;
	size = 0;
	data = new T[capacity];
};


template<typename T>
Array<T>::Array(int c) {
	capacity = c;
	size = 0;
	data = new T[capacity];
};

template<typename T>
Array<T>::~Array() {
	delete[] data;
};

template<typename T>
void Array<T>::insert(T& value) {
	if (size == capacity) {
		T* t = data;
		capacity *= 2;
		data = new T[capacity];
		for (int i = 0; i < size; i++) {
			data[i] = t[i];
		}
		delete[] t;
	}
	data[size] = value;
	size++;
}

template<typename T>
void Array<T>::insert(int index, const T& value) {
	if (size == capacity) {
		T* t = data;
		capacity *= 2;
		data = new T[capacity];
		for (int i = 0; i < size; i++) {
			data[i] = t[i];
		}
		delete[] t;
	}
	T* t = new T[size - index];
	for (int i = index; i < size; i++) {
		t[i - index] = data[i];
	}
	data[index] = value;
	size++;
	for (int i = index + 1; i < size; i++) {
		data[i] = t[i - (index + 1)];
	}
	delete[] t;
}

template<typename T>
void Array<T>::remove(int index) {
	int nindex = index + 1;
	T* t = new T[size - nindex];
	for (int i = nindex; i < size; i++) {
		t[i - nindex] = data[i];
	}
	size--;
	for (int i = index; i < size; i++) {
		data[i] = t[i - index];
	}
	delete[] t;
}

template<typename T>
int Array<T>::get_size() const {
	return size;
}

template<typename T>
const T& Array<T>::operator[](int index) const {
	if (index >= 0 && index < size)
		return data[index];
}

template<typename T>
T& Array<T>::operator[](int index) {
	if (index >= 0 && index < size)
		return data[index];
}

template<typename T>
Array<T>::Iterator::Iterator(Array<T>* a) {
	i_array = a;
	cur = a->data;
}

template<typename T>
const T& Array<T>::Iterator::get() const
{
	return *cur;
}

template<typename T>
void Array<T>::Iterator::set(const T& value)
{
	*cur = value;
}

template<typename T>
void Array<T>::Iterator::remove()
{
	int index = cur - i_array->data;
	i_array->remove(index);
}

template<typename T>
void Array<T>::Iterator::insertIt(const T& value)
{
	int index = cur - i_array->data;
	i_array->insert(value, index);
}

template<typename T>
void Array<T>::Iterator::next()
{
	cur++;
}

template<typename T>
void Array<T>::Iterator::prev()
{
	cur--;
}

template<typename T>
void Array<T>::Iterator::toIndex(int index)
{
	cur = &i_array->data[index];
}

template<typename T>
bool Array<T>::Iterator::hasNext() const
{
	if (cur == i_array->data + i_array->size - 1)
	{
		return false;
	}
	return true;
}

template<typename T>
bool Array<T>::Iterator::hasPrev() const
{
	if (cur == i_array->data)
	{
		return false;
	}
	return true;
}