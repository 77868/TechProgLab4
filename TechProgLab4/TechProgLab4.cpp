//Задание 1
//Написать функцию - шаблон, которая выполняет сортировку выбором как для сортировки по возрастанию, так и по убыванию.
//Задание 2
//Создать параметризованный список, перегрузить оператор потокового ввода / вывода, [] для доступа к элементу заданной позиции, +для объединения двух списков.

#include <iostream>
#include <string>
#include <locale>
#include "List.h"
#include "MySort.h"


template<typename T>
void demonstrate();

int main()
{
	setlocale(LC_ALL,"Russian");
	std::cout << "Выберите тип данных:" << std::endl
		<< "1) int " << std::endl
		<< "2) char" << std::endl
		<< "3) float" << std::endl
		<< "4) double" << std::endl
		<< "5) char*" << std::endl;
	unsigned int choise=0;
	std::cin >> choise;
	while (!std::cin.good() || choise < 1 || choise>5)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> choise;
		std::cout << std::endl << "Введены неверные данные. Попробуйте ещё раз" << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	switch (choise)
	{
	case 1:
		demonstrate<int>();
		break;
	case 2:
		demonstrate<char>();
		break;
	case 3:
		demonstrate<float>();
		break;
	case 4:
		demonstrate<double>();
		break;
	case 5:
		demonstrate<char*>();
		break;
	default:
		break;
	}
	return 1;
}
template<typename T>
void demonstrate()
{
	
	List<T>** listArray=nullptr;
	unsigned int arrLength=0;
	while (true)
	{
		system("cls");
		showArr(listArray, arrLength);
		
		std::cout << "Выберите действие" << std::endl
			<< "1) создание списка " << std::endl
			<< "2) удаление списка" << std::endl
			/*<< "3) слияние двух других очередей " << std::endl*/
			<< "3) сортировка по возрастанию" << std::endl
			<< "4) сортировка по убыванию" << std::endl
			<< "5) добавление элемента в список" << std::endl
			<< "6) выход" << std::endl;
		unsigned int choise = 0;
		std::cin >> choise;
		if (!std::cin.good() || choise < 1 || choise>6)
		{
			std::cerr << std::endl << "Введены неверные данные. Попробуйте ещё раз" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("pause");
			continue;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (choise)
		{
		case 1:
			addElement(listArray,arrLength);
			break;
		case 2:
		{
			try {
				removeElement(listArray, arrLength, choiseElement(listArray, arrLength));
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				system("pause");
			}
		}
			break;
		/*case 3:
			mergeElements(listArray,arrLength);
			break;*/
		case 3:
		{
			try {
				auto tmp = choiseElement(listArray, arrLength);
				sort(*tmp, tmp->getLength());
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				system("pause");
			}
			break;
		}
		case 4:
		{
			try {
				auto tmp = choiseElement(listArray, arrLength);
				sort(*tmp, tmp->getLength(), 1);
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				system("pause");
			}
		}
			break;
		case 5:
		{
			try {
				auto tmp = choiseElement(listArray, arrLength);
				std::cout << "Введите значение" << std::endl;
				std::cin >> *tmp;
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				system("pause");
			}
		}
			break;
		case 6:
		{
			if (listArray != nullptr)
			{
				for (size_t i = 0; i < arrLength; i++)
				{
					delete listArray[i];
				}
				delete[] listArray;
			}
			return;
			break;
		}
		}
	}
}
template<typename T>
void showArr(List<T>**& arr, unsigned int length)
{
	for (size_t i = 0; i < length; i++)
	{
		std::cout << i << ") " << *(arr[i]) << std::endl;
	}
}
template<typename T>
void addElement(List<T>**& arr, unsigned int& length)
{
	if (!length)
	{
		try {
			arr = new List<T>*[1];
			arr[0] = new List<T>;
			length = 1;
			return;
		}
		catch(const char* msg)
		{
			std::cerr << msg << std::endl;
			system("pause");
		}
	}
	else
	{
		auto tmp = new List<T>*[length + 1];
		try {
			for (size_t i = 0; i < length; i++)
			{
				tmp[i] = arr[i];
			}
			tmp[length] = new List<T>;
			length++;
			delete[] arr;
			arr = tmp;
			return;
		}
		catch(const char* msg)
		{
			delete[] tmp;
			std::cerr << msg << std::endl;
			system("pause");
			return;
		}
	}
}

template<typename T>
List<T>* choiseElement(List<T>**& arr, unsigned int& length)
{
	system("cls");
	showArr(arr, length);
	std::cout << "Выберите необходимый список" << std::endl;
	unsigned int choise;
	std::cin >> choise;
	if (!std::cin.good() || choise >= length)
	{
		throw("Некорректный индекс числа");
	}
	return arr[choise];
}

template<typename T>
void removeElement(List<T>**& arr, unsigned int& length,List<T>* remElement )
{
	if (!length || remElement == nullptr)
	{
		throw("Ошибка при удалении");
	}
	if (length == 1)
	{
		delete arr[0];
		delete[] arr;
		arr = nullptr;
		length--;
	}
	else
	{
		List<T>** newList = new List<T> * [length - 1];
		List<T>** tmp = newList;
		for (size_t i = 0; i < length; i++)
		{
			if (!(arr[i] == remElement))
			{
				*(tmp++) = arr[i];
			}
		}
		delete remElement;
		delete[] arr;
		arr = newList;
		length--;
	}
}
//template<typename T>
//void mergeElements(List<T>**& arr, unsigned int& length)
//{
//	List<T>* leftEl,* rightEl;
//	try
//	{
//		 leftEl = choiseElement(arr,length);
//		 rightEl = choiseElement(arr,length);
//	}
//	catch (const char* msg)
//	{
//		std::cerr << msg << std::endl;
//		system("pause");
//		return;
//	}
//
//	List<T>** tmp = new List<T>*[length + 1];
//	try {
//		for (size_t i = 0; i < length; i++)
//		{
//			tmp[i] = arr[i];
//		}
//		tmp[length] = new List<T>;
//		*(tmp[length]) = (*leftEl) + (*rightEl);
//		length++;
//		delete[] arr;
//		arr = tmp;
//		return;
//	}
//	catch (const char* msg)
//	{
//		delete[] tmp;
//		std::cerr << msg << std::endl;
//		system("pause");
//		return;
//	}
//}