#pragma once

#include "Word.h"

struct WordArray {

	Word* *words;
	int size;

	WordArray(const int size = 1) {
		this->words = new Word* [size];
		for (int i = 0; i < size; ++i) this->words[i] = new Word;
		this->size = size;
	}

	~WordArray() {
		for (int i = 0; i < this->size; ++i) delete this->words[i];
		delete[] this->words;
	}

};