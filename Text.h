#pragma once

#include "Word.h"

struct Text {

	Word* *lines;
	int size;

	explicit Text(const int size = 1) {
		this->lines = new Word* [size];
		for (int i = 0; i < size; ++i) this->lines[i] = new Word;
		this->size = size;
	}

	~Text() {
		for (int i = 0; i < this->size; ++i) delete this->lines[i];
		delete[] this->lines;
	}

};