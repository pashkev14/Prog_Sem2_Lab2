#pragma once

#include "Word.h"

struct Item {

	Word* key;
	int count;

	Item() {
		this->key = new Word;
		this->count = 1;
	}

	~Item() {
		delete this->key;
	}

};