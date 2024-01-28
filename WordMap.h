#pragma once

#include "Item.h"

class WordMap {

private:

	Item* *list;
	int m_size;

public:

	explicit WordMap(const int size = 1) {
		this->list = new Item* [size];
		for (int i = 0; i < size; ++i) this->list[i] = new Item;
		this->m_size = size;
	}

	~WordMap() {
		for (int i = 0; i < this->m_size; ++i) delete this->list[i];
		delete[] this->list;
	}

	void setItem(Word* key, const int index);

	void addCount(const int index);

	Item* getItem(const int index);

	int getSize();

	void swap(Item* first, Item* second);

	void sort();

};