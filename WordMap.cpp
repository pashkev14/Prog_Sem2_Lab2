#include "WordMap.h"

void WordMap::setItem(Word* key, const int index) {
	if (index >= 0 && index < this->m_size) {
		delete this->list[index];
		this->list[index] = new Item;
		this->list[index]->key->setText(key->getText(), key->getSize());
	}
}

void WordMap::addCount(const int index) {
	if (index >= 0 && index < this->m_size) this->list[index]->count += 1;
}

Item* WordMap::getItem(const int index) {
	if (index >= 0 && index < this->m_size) return this->list[index];
}

int WordMap::getSize() {
	return this->m_size;
}

void WordMap::swap(Item* first, Item* second) {
	Item* tmp = new Item;
	tmp->key->setText(first->key->getText(), first->key->getSize());
	tmp->count = first->count;
	first->key->setText(second->key->getText(), second->key->getSize());
	first->count = second->count;
	second->key->setText(tmp->key->getText(), tmp->key->getSize());
	second->count = tmp->count;
	delete tmp;
}

void WordMap::sort() {
    bool swapped = true;
    int start = 0;
    int end = this->m_size - 1;
    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (this->list[i]->count < this->list[i + 1]->count) {
                swap(this->list[i], this->list[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (this->list[i]->count < this->list[i + 1]->count) {
                swap(this->list[i], this->list[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}