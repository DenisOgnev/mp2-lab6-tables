#pragma once
#include <exception>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>

int max = 0;
int max1 = 0;
int len = 0;

template<class Key, class Data>
class Record {
public:
	Key key;
	Data data;

	bool operator ==(const Key&);
	bool operator !=(const Key&);
	bool operator <(const Key&);
	friend std::ostream& operator<<(std::ostream& os, const Record<Key, Data>& d)
	{
		std::string str1 = std::to_string(d.key);
		std::string str2 = std::to_string(d.data);
		len = max + max1 + 5;
		std::string indent1;
		std::string indent2;
		for (int i = 0; i < max - str1.length(); i++)
		{
			indent1 += " ";
		}
		for (int i = 0; i < max1 - str2.length(); i++)
		{
			indent2 += " ";
		}
		for (int i = 0; i < len; i++)
		{
			os << "-";
		}
		os << "\n|" << d.key << indent1 << " | " << indent2 << d.data << "|\n";
		return os;
	}
};

template<class Key, class Data>
bool comp(const Record<Key, Data> &r1, const Record<Key, Data> &r2)
{
	return r1.key > r2.key;
}

template<class Key, class Data>
struct Comparator
{
	bool operator()(const Record<Key, Data> &r1, const Record<Key, Data> &r2)
	{
		return r1.key < r2.key;
	}
};

template<class Key, class Data>
inline bool Record<Key, Data>::operator<(const Key& _key)
{
	return key < _key;
}

template<class Key, class Data>
inline bool Record<Key, Data>::operator!=(const Key& _key)
{
	return key != _key;
}

template<class Key, class Data>
inline bool Record<Key, Data>::operator==(const Key& _key)
{
	return key == _key;
}

template<class Key, class Data>
class Table {
protected:
	int size;
	int count;
	Record<Key, Data>* dataArray;

public:

	Table()
	{
		size = 0;
		count = 0;
		dataArray = nullptr;
	}

	Table(int _size) : size(_size), count(0)
	{
		dataArray = new Record<Key, Data>[size];
	}

	int getSize() const
	{
		return size;
	}

	int getCount() const
	{
		return count;
	}

	Record<Key, Data> getRecord(int i) const
	{
		return dataArray[i];
	}

	void Add(Key key, Data data) {
		dataArray[count].key = key;
		dataArray[count].data = data;
		++count;
	}

	Data Find(Key key) {
		for (int i = 0; i < count; ++i)
			if (dataArray[i].key == key)
				return dataArray[i].data;
		throw std::exception("Not found");
	}

	void print()
	{
		int _max = 0;
		int _max1 = 0;
		std::string maxData = "";
		std::string maxKey = "";
		for (int i = 0; i < count; i++)
		{
			if (std::to_string(dataArray[i].key).length() > _max)
			{
				_max = _max + std::to_string(dataArray[i].key).length() - maxKey.length();
				maxKey = std::to_string(dataArray[i].key);
			}
			//_max = _max + std::to_string(dataArray[i].key).length();
			if (std::to_string(dataArray[i].data).length() > _max1)
			{
				_max1 = _max1 + std::to_string(dataArray[i].data).length() - maxData.length();
				maxData = std::to_string(dataArray[i].data);
			}
		}
		max = _max;
		max1 = _max1;
		for (int i = 0; i < count; i++)
			std::cout << dataArray[i];
		for (int i = 0; i < len; i++)
			std::cout << "-";
		std::cout << std::endl;
		max = 0;
		max1 = 0;
	}
};


template<class Key, class Data>
class SortTable : public Table<Key, Data >
{
public:
	SortTable(size_t _size);
	SortTable(const SortTable<Key, Data>& table);
	SortTable(const Table<Key, Data>& table); //реализовать любым способом 
	void Add(Key key, Data data);
	Data Find(Key key);
	void Delete(const Key& key);
	Data& operator[](const Key& key);
};

template<class Key, class Data>
SortTable<Key, Data>::SortTable(size_t _size) : Table<Key, Data>::Table(_size) { };

template<class Key, class Data>
SortTable<Key, Data>::SortTable(const SortTable<Key, Data>& table) {
	this->size = table.size;
	this->count = table.count;
	this->dataArray = new Record<Key, Data>[this->size];
	for (int i = 0; i < this->count; ++i)
		this->dataArray[i] = table.dataArray[i];

}

template<class Key, class Data>
SortTable<Key, Data>::SortTable(const Table<Key, Data>& table)
{
	int mode = 0;
	std::cout << "Enter type of sort\n0 for std::sort, 1 for usual sort\n";
	std::cin >> mode;

	this->size = table.getSize();
	this->count = table.getCount();
	this->dataArray = new Record<Key, Data>[this->size];
	for (int i = 0; i < this->count; ++i)
		this->dataArray[i] = table.getRecord(i);

	if (mode == 0)
	{
		clock_t start = clock();
		std::sort(this->dataArray, this->dataArray + this->count, Comparator<Key, Data>{});
		clock_t end = clock();
		std::cout << "\nTime: " << (double)(end - start) / CLOCKS_PER_SEC << " sec\n";
	}
	else
	{
		clock_t start = clock();
		for (int i = 0; i < this->count; i++)
			for (int j = 0; j < this->count; j++)
				if (this->dataArray[i].key < this->dataArray[j].key)
					std::swap(this->dataArray[i], this->dataArray[j]);
		clock_t end = clock();
		std::cout << "\nTime: " << (double)(end - start) / CLOCKS_PER_SEC << " sec\n";
	}
}

template<class Key, class Data>
void SortTable<Key, Data>::Add(Key key, Data data) {
	int i = 0;
	while (i < this->count)
	{
		if (this->dataArray[i].key <= key)
		{
			i++;
			continue;
		}
		break;
	}
	for (int j = this->count; j > i; j--)
	{
		this->dataArray[j].key = this->dataArray[j - 1].key;
		this->dataArray[j].data = this->dataArray[j - 1].data;
	}
	this->dataArray[i].key = key;
	this->dataArray[i].data = data;
	++this->count;
}

template<class Key, class Data>
Data SortTable<Key, Data>::Find(Key key) {
	int l = 0, r = this->count - 1;
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (this->dataArray[mid].key > key)
			r = mid;
		else l = mid;
	}
	if (this->dataArray[l].key == key) return this->dataArray[l].data;
	if (this->dataArray[r].key == key) return this->dataArray[r].data;
	throw std::runtime_error("Not Found");
}

template<class Key, class Data>
void SortTable<Key, Data>::Delete(const Key& key)
{
	int i = 0;
	while (this->dataArray[i].key != key)
	{
		i++;
		if (i == this->count)
			throw std::runtime_error("Not Found");
	}
	for (i; i < this->count; i++)
	{
		this->dataArray[i].key = this->dataArray[i + 1].key;
		this->dataArray[i].data = this->dataArray[i + 1].data;
	}
	this->count--;
}

template<class Key, class Data>
Data& SortTable<Key, Data>::operator[](const Key& key)
{
	int i = 0;
	while (this->dataArray[i].key != key)
	{
		i++;
		if (i == this->count)
			throw std::runtime_error("Not Found");
	}
	return this->dataArray[i].data;
}