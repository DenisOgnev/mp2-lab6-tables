#pragma once
#include "table.h"
#include <vector>
#include <list>
#include <math.h>

int HashFunction(int key, int size)
{
	return (key + size / 2) % size;
}

int HashFunction(std::string key, int size)
{
	int result = 0;
	for (int i = 0; i < key.length(); i++)
		result += + key[i] * pow(double(size), double(i));
	return result % size;
}

template<class Key>
int _HashFunction(Key key, int size)
{
	return 0;
}

template<class Key, class Data>
class HashTable
{
protected:
	std::list<Record<Key, Data>>* dataArray;
	int size;
	int (*hashFunction)(Key, int);

public:

	HashTable(int _size, bool useYourFunction) : size(_size)
	{
		dataArray = new std::list<Record<Key, Data>>[size];
		if (useYourFunction)
			hashFunction = _HashFunction;
		else
			hashFunction = HashFunction;
	}

	void add(Key key, Data data)
	{
		int index = hashFunction(key, size);
		Record<Key, Data> rec;
		rec.key = key;
		rec.data = data;
		dataArray[index].push_back(rec);
	}

	Data find(Key key)
	{
		int index = hashFunction(key, size);
		typename std::list<Record<Key, Data>>::iterator it = dataArray[index].begin();
		while (it->key != key)
			it++;
		return it->data;
	}
	void del(Key key)
	{
		int index = hashFunction(key, size);
		typename std::list<Record<Key, Data>>::iterator it = dataArray[index].begin();
		while (it->key != key)
			it++;
		dataArray[index].erase(it);
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << "[" << i << "]: ";
			typename std::list<Record<Key, Data>>::iterator it = dataArray[i].begin();
			while (it != dataArray[i].end())
			{
				std::cout << it->data << " ";
				it++;
			}
			std::cout << "\n";
		}
	}
};