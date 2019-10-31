#pragma once

template<typename T>
class Array {
	int capacity;
	int size;
	T* data;
public:
	Array();
	Array(int c);
	Array(const Array& arr) {
		capacity = arr.capacity;
		size = arr.size;
		data = new T[arr.capacity];
		for (int i = 0; i < arr.size; i++) {
			data[i] = arr.data[i];
		}
	}
	~Array();
	void insert(T& value);
	void insert(int index, const T& value);
	void remove(int index);
	const T& operator[](int index) const;
	T& operator[](int index);
	int get_size() const;
	Array& operator=(const Array& arr) {
		if (this == &arr)
			return *this;

		capacity = arr.capacity;
		size = arr.size;
		data = new T[arr.capacity];
		for (int i = 0; i < arr.size; i++) {
			data[i] = arr.data[i];
		}
		return *this;
	}

	class Iterator
	{
		Array* i_array;
		T* cur;
	public:
		Iterator(Array<T>* a);
		const T& get() const;
		void set(const T& value);
		void remove();
		void insertIt(const T& value);
		void next();
		void prev();
		void toIndex(int index);
		bool hasNext() const;
		bool hasPrev() const;
	};
	Iterator iterator()
	{
		Iterator it(this);
		return it;
	}
};

#include"Source.cpp"
