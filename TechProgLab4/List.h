#pragma once
#include "Node.h"
#include <iostream>
#include <stdio.h>

template<class T>
class List
{
private:
	Node<T>* root;
	unsigned int length;
public:
	List()
	{
		std::cout << "¬ведите длину списка" << std::endl;
		length = 0;
		std::cin >> length;
		if (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw("¬ведены некорректные данные.");
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (length > 0)
		{
			auto currentPtr = root = new Node<T>;
			root->prev = nullptr;
			for (size_t i = 1; i < length; i++)
			{
				std::cout << "¬ведите значение элемента" << std::endl;
				std::cin >> currentPtr->value;
				if (!std::cin.good())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					while (root != currentPtr)
					{
						auto tmpPtr = root;
						root = root->next;
						delete tmpPtr;
					}
					delete root;
					throw("¬ведены некорректные данные.");
				}
				currentPtr->next = new Node<T>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
			}
			std::cout << "¬ведите значение элемента" << std::endl;
			std::cin >> currentPtr->value;
			if (!std::cin.good())
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				while (root != currentPtr)
				{
					auto tmpPtr = root;
					root = root->next;
					delete tmpPtr;
				}
				delete root;
				throw("¬ведены некорректные данные.");
			}
			currentPtr->next = nullptr;
		}
	}
	List(const List<T>& original)
	{
		length = original.length;
		if (original.length)
		{
			auto currentPtr = root = new Node<T>;
			auto origPtr = original.root;
			root->prev = nullptr;
			root->value = origPtr->value;
			for (; origPtr->next != nullptr;)
			{
				currentPtr->next = new Node<T>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
				origPtr = origPtr->next;
				currentPtr->value = origPtr->value;
			}
			currentPtr->next = nullptr;
		}
	}

	~List()
	{
		if (length)
		{
			auto currentPtr = root;
			while (currentPtr->next != nullptr)
			{
				currentPtr = currentPtr->next;
				delete currentPtr->prev;
			}
			delete currentPtr;
		}
	}


	void append(T newElement)
	{
		if (length)
		{
			auto currentPtr = root;
			for (; currentPtr->next != nullptr; currentPtr = currentPtr->next) {}
			currentPtr->next = new Node<T>;
			currentPtr->next->prev = currentPtr;
			currentPtr->next->next = nullptr;
			currentPtr->next->value = newElement;
		}
		else
		{
			root = new Node<T>;
			root->next = root->prev = nullptr;
			root->value = newElement;
		}
		length++;
	}

	bool isEmpty()
	{
		return length ? false : true;
	}
	unsigned int getLength()
	{
		return length;
	}

	T& operator[](unsigned int index)
	{
		Node<T>* currentPtr = root;
		for (size_t i = 0; i < index; i++, currentPtr = currentPtr->next) {}
		return currentPtr->value;
	}
	List<T> operator+(List<T> rightValue)
	{
		List<T> result(*this);
		for (size_t i = 0; i < rightValue.length; i++)
		{
			result.append(rightValue[i]);
		}
		return result;
	}
	List<T>& operator=(List<T>& rightValue)
	{
		if (this == &rightValue)
			return *this;
		if (length)
		{
			auto currentPtr = root;
			while (currentPtr->next != nullptr)
			{
				currentPtr = currentPtr->next;
				delete currentPtr->prev;
			}
			delete currentPtr;
		}
		length = rightValue.length;
		if (rightValue.length)
		{
			auto currentPtr = root = new Node<T>;
			root->prev = nullptr;
			root->value = rightValue[0];
			for (size_t i = 1; i < rightValue.length; i++)
			{
				currentPtr->next = new Node<T>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
				currentPtr->value = rightValue[i];
			}
			currentPtr->next = nullptr;
			currentPtr->value = rightValue[length - 1];
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, List<T>& list)
	{
		for (size_t i = 0; i < list.length; i++)
		{
			out << list[i]<<" " ;
		}
		return out;
	}

	
	friend std::istream& operator>>(std::istream& in, List<T>& list)
	{
		T tmp = 0;
		in >> tmp;
		if (!in.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw("¬ведены некоректные значени€");
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		list.append(tmp);
		return in;
	}
	
};

template<>
class List<char*>
{
private:
	Node<char*>* root;
	unsigned int length;
public:
	List()
	{
		std::cout << "¬ведите длину списка" << std::endl;
		length = 0;
		std::cin >> length;
		if (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			throw("¬ведены некорректные данные.");
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (length > 0)
		{
			auto currentPtr = root = new Node<char*>;
			root->prev = nullptr;
			for (size_t i = 1; i < length; i++)
			{
				std::cout << "¬ведите значение элемента" << std::endl;
				currentPtr->value = new char[1000];
				strcpy_s(currentPtr->value,1000, "\0");
				std::cin>>currentPtr->value;
				if (!std::cin.good())
				{
					delete[] currentPtr->value;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					while (root != currentPtr)
					{
						delete[] root->value;
						auto tmpPtr = root;
						root = root->next;
						delete tmpPtr;
					}
					delete root;
					throw("¬ведены некорректные данные.");
				}
				currentPtr->next = new Node<char*>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
			}
			std::cout << "¬ведите значение элемента" << std::endl;
			currentPtr->value = new char[1000];
			strcpy_s(currentPtr->value, 1000, "\0");
			std::cin >> currentPtr->value;
			if (!std::cin.good())
			{
				delete[] currentPtr->value;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				while (root != currentPtr)
				{
					delete[] root->value;
					auto tmpPtr = root;
					root = root->next;
					delete tmpPtr;
				}
				delete root;
				throw("¬ведены некорректные данные.");
			}
			currentPtr->next = nullptr;
		}
	}
	List(const List<char*>& original)
	{
		length = original.length;
		if (original.length)
		{
			auto currentPtr = root = new Node<char*>;
			auto origPtr = original.root;
			root->prev = nullptr;
			currentPtr->value = new char[1000];
			strcpy_s(currentPtr->value, 1000, origPtr->value);
			for (; origPtr->next != nullptr;)
			{
				currentPtr->next = new Node<char*>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
				origPtr = origPtr->next;

				currentPtr->value = new char[1000];
				strcpy_s(currentPtr->value, 1000, origPtr->value);
			}
			currentPtr->next = nullptr;
		}
	}

	~List()
	{
		if (length)
		{
			auto currentPtr = root;
			while (currentPtr->next != nullptr)
			{
				delete[] currentPtr->value;
				currentPtr = currentPtr->next;
				delete currentPtr->prev;
			}
			delete[] currentPtr->value;
			delete currentPtr;
		}
	}


	void append(char* newElement)
	{
		if (length)
		{
			auto currentPtr = root;
			for (; currentPtr->next != nullptr; currentPtr = currentPtr->next) {}
			currentPtr->next = new Node<char*>;
			currentPtr->next->prev = currentPtr;
			currentPtr->next->next = nullptr;
			currentPtr->next->value = newElement;
		}
		else
		{
			root = new Node<char*>;
			root->next = root->prev = nullptr;
			root->value = newElement;
		}
		length++;
	}

	bool isEmpty()
	{
		return length ? false : true;
	}
	unsigned int getLength()
	{
		return length;
	}

	char*& operator[](unsigned int index)
	{
		Node<char*>* currentPtr = root;
		for (size_t i = 0; i < index; i++, currentPtr = currentPtr->next) {}
		return currentPtr->value;
	}
	List<char*> operator+(List<char*> rightValue)
	{
		List<char*> result(*this);
		for (size_t i = 0; i < rightValue.length; i++)
		{
			char * tmp = new char[1000];
			strcpy_s(tmp,1000,rightValue[i]);
			result.append(tmp);
		}
		return result;
	}
	List<char*>& operator=(List<char*>& rightValue)
	{
		if (this == &rightValue)
			return *this;
		if (length)
		{
			auto currentPtr = root;
			while (currentPtr->next != nullptr)
			{
				currentPtr = currentPtr->next;
				delete currentPtr->prev;
			}
			delete currentPtr;
		}
		length = rightValue.length;
		if (rightValue.length)
		{
			auto currentPtr = root = new Node<char*>;
			root->prev = nullptr;
			currentPtr->value = new char[1000];
			strcpy_s(currentPtr->value, 1000, rightValue[0]);
			for (size_t i = 1; i < rightValue.length; i++)
			{
				currentPtr->next = new Node<char*>;
				currentPtr->next->prev = currentPtr;
				currentPtr = currentPtr->next;
				currentPtr->value = new char[1000];
				strcpy_s(currentPtr->value, 1000, rightValue[i]);
			}
			currentPtr->next = nullptr;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, List<char*>& list)
	{
		for (size_t i = 0; i < list.length; i++)
		{
			out << list[i] << " ";
		}
		return out;
	}


	friend std::istream& operator>>(std::istream& in, List<char*>& list)
	{
		char* tmp = new char[1000];
		strcpy_s(tmp,1000,"\0");
		std::cin>>tmp;
		if (!in.good())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			delete[] tmp;
			throw("¬ведены некоректные значени€");
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		list.append(tmp);
		return in;
	}

};






