template<typename T>
void insertionSort(T *start, T *end)
{
	T temp;
	int length = end - start;
	int item;
	for (int counter = 1; counter < length; counter++)
	{
		temp = start[counter];
		item = counter - 1;
		while (item >= 0 && start[item] > temp)
		{
			start[item + 1] = start[item];
			start[item] = temp;
			item--;
		}
	}
}

template<typename T>
T pivot_func(const T *start, const T *end) {
	const int temp_size = 3;
	T temp_arr[temp_size];
	temp_arr[0] = *start;
	temp_arr[1] = *(start + (end - start) / 2);
	temp_arr[2] = *(end - 1);
	insertionSort(temp_arr, temp_arr + temp_size);
	return temp_arr[1];
}



template<typename T, typename Compare>
void QSort(T *first, T *last, const Compare &comp) {
	T *i;
	T *j;
	T tmp;
	T pivot;
	while (first != last) {
		i = first;
		j = last;
		pivot = pivot_func(i, j);
		while (i <= j) {
			while (comp(*i, pivot))
				i++;
			while (comp(pivot, *j))
				j--;
			if (i <= j) {
				tmp = *i;
				*i = *j;
				*j = tmp;
				i++;
				j--;
			}
		}
		if (i > j)
		{
			T *temp = i;
			i = j;
			j = temp;
		}
		if ((i - first) < (last - j))
		{
			if (first < j)
			{
				QSort(first, j - 1, comp);
			}
			if ((last - j) <= 13)
			{

				insertionSort(j, j + (last - j + 1));
				break;
			}
			else
			{
				first = j;
			}
		}
		else
		{
			if (i < last)
			{
				QSort(i + 1, last, comp);

			}
			if (i - first <= 13)
			{

				insertionSort(first, first + (i - first + 1));
				break;
			}
			else
			{
				last = i;
			}
		}
	}
}