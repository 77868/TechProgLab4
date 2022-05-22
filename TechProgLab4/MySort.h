#pragma once
template <typename T>
void sort(T& arr, unsigned int length, unsigned int mode = 0);
template <typename T>
void sort(T& arr, unsigned int length, unsigned int mode)
{
	for (size_t i = 0; i < length; i++)
	{
		auto tmp = arr[i];
		int index = i;
		for (size_t j = i + 1; j < length; j++)
		{
			if (mode)
			{
				if (tmp < arr[j])
				{
					tmp = arr[j];
					index = j;
				}
			}
			else
			{
				if (tmp > arr[j])
				{
					tmp = arr[j];
					index = j;
				}
			}
		}
		if (i != index)
		{
			arr[index] = arr[i];
			arr[i] = tmp;

		}
	}
}
template <>
void sort<char**>(char**& arr, unsigned int length, unsigned int mode)
{
	for (size_t i = 0; i < length; i++)
	{
		auto tmp = arr[i];
		int index = i;
		for (size_t j = i + 1; j < length; j++)
		{
			if (mode)
			{
				if (strcmp(tmp, arr[j]) < 0)
				{
					tmp = arr[j];
					index = j;
				}
			}
			else
			{
				if (strcmp(arr[j], tmp) < 0)
				{
					tmp = arr[j];
					index = j;
				}
			}
		}
		if (i != index)
		{
			arr[index] = arr[i];
			arr[i] = tmp;

		}
	}
}
template <>
void sort<List<char*>>(List<char*>& arr, unsigned int length, unsigned int mode)
{
	for (size_t i = 0; i < length; i++)
	{
		auto tmp = arr[i];
		int index = i;
		for (size_t j = i + 1; j < length; j++)
		{
			if (mode)
			{
				if (strcmp(tmp, arr[j]) < 0)
				{
					tmp = arr[j];
					index = j;
				}
			}
			else
			{
				if (strcmp(arr[j], tmp) < 0)
				{
					tmp = arr[j];
					index = j;
				}
			}
		}
		if (i != index)
		{
			arr[index] = arr[i];
			arr[i] = tmp;

		}
	}
}