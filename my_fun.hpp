#ifndef MY_FUNC_H_
#define MY_FUNC_H_

#include<cmath>
#include<iostream>
#include<random>
#include<stdlib.h>

using namespace std;

template <class T> int select_index(T* arr, int start_index, const int final_index, const T sele_value)
{
	int m = start_index;
	int n = final_index;
	int k;
	for (k = 0; k <= final_index; k++)
	{
		if (arr[k] == sele_value)
		{
			T temp = arr[k];
			arr[k] = arr[0];
			arr[0] = temp;
			break;
		}
	}
	T start_value = arr[0];
	while (m < n)
	{
		while (m < n && arr[n] > sele_value)
		{
			n--;
		}
		arr[m] = arr[n];
		if (m < n)
		{
			m++;
		}
		while (m < n && arr[m] <= sele_value)
		{
			m++;
		}
		arr[n] = arr[m];
		if (m < n)
		{
			n--;
		}
	}
	arr[m] = start_value;
	return m;
}

template <class T> T random_partion(T* arr, int start_index, const int final_index, const int select_ith)
{
	if (start_index == final_index)
	{
		return arr[start_index];
	}
	int random_index = rand() % (final_index - start_index + 1) + start_index;
	T temp = arr[random_index];
	arr[random_index] = arr[start_index];
	arr[start_index] = temp;
	int m = 0;
	int n = final_index - start_index;
	T select_value = arr[start_index];
	while (m < n)
	{
		while (m < n && arr[start_index + n] >= select_value)
		{
			n--;
		}
		arr[start_index + m] = arr[start_index + n];
		while (m < n && arr[start_index + m] <= select_value)
		{
			m++;
		}
		arr[start_index + n] = arr[start_index + m];
	}
	arr[start_index + m] = select_value;
	if (select_ith == m)
	{
		return arr[start_index + m];
	}
	else if (select_ith < m)
	{
		return random_partion(arr, start_index, m, select_ith);
	}
	else
	{
		return random_partion(arr, m, final_index, select_ith - m);
	}
}

template <class T> T select_ith(const T* array, int i, int array_length)
{
	if (array_length < i)
	{
		cout << "Array lengh can not small than select index!" << endl;
		exit(1);
	}
	T* copy_arr = new T[array_length];
	int k;
	for (k = 0; k < array_length; k++)
	{
		copy_arr[k] = array[k];
	}
	T select_value = random_partion(copy_arr, 0, array_length - 1, i);
	delete[] copy_arr;
	return select_value;
}


template <class T>T middle_value_assert(T* array, int start_index, int length)
{
	int i = 0;
	for (i = 1; i < length; i++)
	{
		int k = i;
		while (k > 0 && array[start_index + k] < array[start_index + k - 1])
		{
			T temp = array[start_index + k];
			array[start_index + k] = array[start_index + k - 1];
			array[start_index + k - 1] = temp;
			k--;
		}
	}
	int middle_index;
	if (length % 2 == 0)
	{
		middle_index = int(length / 2) - 1;
	}
	else
	{
		middle_index = int(length / 2);
	}
	return array[start_index + middle_index];
}

template <class T>T linear_select_ith(T* array, int i_index, int array_length)
{
	if (array_length < i_index)
	{
		cout << "Array lengh can not small than select index!" << endl;
		exit(1);
	}
	if (array_length == 1)
	{
		return array[0];
	}
	int i;

	int num_groups = int(array_length / 5);
	if (array_length % 5 != 0)
	{
		num_groups += 1;
	}
	T* middle_value_list = new T[num_groups];
	int j;
	int no_middle_value = 0;
	for (i = 0; i < array_length; i += 5)
	{
		int k = 0;
		while (k < 5 && i + k < array_length)
		{
			k++;
		}
		k--;
		j = i + k;
		if (i != j)
		{
			middle_value_list[no_middle_value] = middle_value_assert(array, i, k + 1);
			no_middle_value++;
		}
		else
		{
			middle_value_list[no_middle_value] = array[i];
			no_middle_value++;
		}
	}
	int middle_middle_index;
	if (num_groups % 2 == 0)
	{
		middle_middle_index = int(num_groups / 2);
	}
	else
	{
		middle_middle_index = int(num_groups / 2) + 1;
	}
	T middle_of_middle = linear_select_ith(middle_value_list, middle_middle_index, num_groups);
	delete[] middle_value_list;
	int q = select_index(array, 0, array_length - 1, middle_of_middle);
	if (q == i_index - 1)
	{
		return middle_of_middle;
	}
	else if (i_index < q + 1)
	{
		int new_array_length = q;
		return linear_select_ith(array, i_index, new_array_length);
	}
	else
	{
		int new_array_length = array_length - q - 1;
		T* new_arr = array + q + 1;
		return linear_select_ith(new_arr, i_index - q - 1, new_array_length);
	}
}

template <class T> T linear_select_main(const T* array, int i_index, int array_length)
{
	T* copy_array = new T[array_length];
	int k; 
	for (k = 0; k < array_length; k++)
	{
		copy_array[k] = array[k];
	}
	T result_value = linear_select_ith(copy_array, i_index, array_length);
	delete[] copy_array;
	return result_value;
}

#endif