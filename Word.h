#pragma once

class Word {

private:

	char* m_text;
	int m_size;

	void setSize(const int size);

public:

	explicit Word(const char* text = " ", const int size = 1) {
		this->setSize(size);
		this->m_text = new char[size];
		for (int i = 0; i < size; ++i) m_text[i] = text[i];
	}

	~Word() {
		delete[] this->m_text;
	}

	void setText(const char* text, const int size);

	char* getText();

	char getChar(const int index);

	int getSize();

	bool isEqual(const Word* other);

};