#include "Word.h"

void Word::setSize(const int size) {
	this->m_size = size;
}

void Word::setText(const char* text, const int size) {
	delete[] this->m_text;
	this->setSize(size);
	this->m_text = new char[size];
	for (int i = 0; i < size; ++i) m_text[i] = text[i];
}

char* Word::getText() {
	return this->m_text;
}

char Word::getChar(const int index) {
	if (index >= 0 && index <= this->m_size) return this->m_text[index];
	return 0;
}

int Word::getSize() {
	return this->m_size;
}

bool Word::isEqual(const Word* other) {
	if (this->m_size == other->m_size) {
		for (int i = 0; i < this->m_size; ++i) if (this->m_text[i] != other->m_text[i]) return false;
		return true;
	}
	return false;
}