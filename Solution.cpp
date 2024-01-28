#include "Solution.h"

void Solution::checkFile() {
	this->files->logFile << "Программа начала свою работу.\n";
	if (this->files->inFile.is_open()) this->readSolveAndOut();
	else {
		this->files->outFile << "Ошибка: входной файл не найден.";
		this->files->logFile << "Входной файл не найден.\nПрограмма завершила свою работу.";
	}
}

void Solution::readSolveAndOut() {
	this->files->inFile.unsetf(std::ios::skipws);
	int charsStrCount = 0, linesCount = 1;
	char tmp = 0;
	do {
		this->files->inFile >> tmp;
		if (this->files->inFile.eof()) break;
		if (tmp == '\n') ++linesCount;
		++charsStrCount;
	} 
	while (true);
	if (charsStrCount) {
		this->files->outFile << "Считан следующий текст:\n";
		this->files->logFile << "Считан следующий текст:\n";
		this->files->inFile.clear();
		this->files->inFile.seekg(0, std::ios::beg);
		Text* text = new Text(linesCount);
		int wordsCount = 0, charsWordCount = 0, maxChars = 0, startPos = 0;
		charsStrCount = 0, linesCount = 0;
		do {
			this->files->inFile >> tmp;
			if (!this->files->inFile.eof()) {
				this->files->outFile << tmp;
				this->files->logFile << tmp;
			}
			else {
				if (charsStrCount) {
					this->files->inFile.clear();
					this->files->inFile.seekg(startPos, std::ios::beg);
					char* chars = new char[charsStrCount];
					for (int i = 0; i < charsStrCount; ++i) this->files->inFile >> chars[i];
					text->lines[linesCount]->setText(chars, charsStrCount);
					++linesCount;
					delete[] chars;
				}
				else text->lines[linesCount]->setText(" ", 1);
				if (charsWordCount) ++wordsCount;
				break;
			}
			if (tmp == '\n') {
				if (charsStrCount) {
					this->files->inFile.seekg(startPos, std::ios::beg);
					char* chars = new char[charsStrCount];
					for (int i = 0; i < charsStrCount; ++i) this->files->inFile >> chars[i];
					text->lines[linesCount]->setText(chars, charsStrCount);
					++linesCount;
					delete[] chars;
					this->files->inFile >> tmp;
				}
				else text->lines[linesCount]->setText(" ", 1);
				if (charsWordCount) ++wordsCount;
				charsStrCount = 0;
				charsWordCount = 0;
				startPos = this->files->inFile.tellg();
			}
			else if (tmp == '\t' || (tmp >= 32 && tmp <= 47) || (tmp >= 58 && tmp <= 64) || (tmp >= 91 && tmp <= 96) || (tmp >= 123 && tmp <= 126)) {
				if (charsWordCount) ++wordsCount;
				if (charsWordCount > maxChars) maxChars = charsWordCount;
				charsWordCount = 0;
				++charsStrCount;
			}
			else {
				++charsStrCount;
				++charsWordCount;
			}
		} 
		while (true);
		if (wordsCount) {
			this->files->logFile << "\nЗаписаны следующие слова:\n";
			WordArray* words = new WordArray(wordsCount);
			wordsCount = 0, startPos = 0, charsWordCount = 0, tmp = 0;
			for (int i = 0; i < text->size; ++i) {
				for (int j = 0; j <= text->lines[i]->getSize(); ++j) {
					if (j != text->lines[i]->getSize()) tmp = text->lines[i]->getChar(j);
					if (j == text->lines[i]->getSize() || tmp == '\t' || (tmp >= 32 && tmp <= 47) || (tmp >= 58 && tmp <= 64) || (tmp >= 91 && tmp <= 96) || (tmp >= 123 && tmp <= 126)) {
						if (charsWordCount) {
							this->files->logFile << '\n';
							char* chars = new char[charsWordCount];
							for (int k = startPos; k < startPos + charsWordCount; ++k) {
								chars[k - startPos] = text->lines[i]->getChar(k);
							}
							words->words[wordsCount]->setText(chars, charsWordCount);
							delete[] chars;
							++wordsCount;
						}
						charsWordCount = 0;
					}
					else {
						if (!charsWordCount) startPos = j;
						++charsWordCount;
						this->files->logFile << tmp;
					}
				}
			}
			int uniqueWords = 0;
			for (int i = 0; i < words->size; ++i) {
				bool flag = false;
				for (int j = 0; j < i; ++j) {
					if (words->words[i]->isEqual(words->words[j])) {
						flag = true;
						break;
					}
				}
				if (!flag) ++uniqueWords;
			}
			this->files->logFile << "Производится запись уникальных слов.\n";
			WordMap* map = new WordMap(uniqueWords);
			int curIndex = 0;
			for (int i = 0; i < words->size; ++i) {
				bool flag = false;
				int mapPos = 0;
				for (int j = 0; j < uniqueWords; ++j) {
					if (words->words[i]->isEqual(map->getItem(j)->key)) {
						mapPos = j;
						flag = true;
						break;
					}
				}
				if (!flag) {
					map->setItem(words->words[i], curIndex);
					++curIndex;
				}
				else map->addCount(mapPos);
			}
			this->files->logFile << "Записаны уникальные слова. Производится сортировка таблицы по убыванию кол-ва вхождений.\n";
			map->sort();
			this->files->logFile << "Итоговая таблица уникальных слов:\n";
			this->files->outFile << "\nИтоговая таблица уникальных слов:\n";
			this->files->logFile << std::setw((maxChars > 5 ? maxChars : 5) + 25) << std::setfill('-') << '\n';
			this->files->outFile << std::setw((maxChars > 5 ? maxChars : 5) + 25) << std::setfill('-') << '\n';
			this->files->logFile << "|№   |" << std::setw((maxChars > 5 ? maxChars : 5)) << std::setfill(' ') << std::left << "Слово" << "|Кол-во вхождений|\n";
			this->files->outFile << "|№   |" << std::setw((maxChars > 5 ? maxChars : 5)) << std::setfill(' ') << std::left << "Слово" << "|Кол-во вхождений|\n";
			for (int i = 0; i < map->getSize(); ++i) {
				this->files->logFile << '|' << std::setw(4) << std::left << i + 1 << '|';
				this->files->outFile << '|' << std::setw(4) << std::left << i + 1 << '|';
				for (int j = 0; j < map->getItem(i)->key->getSize(); ++j) {
					this->files->logFile << map->getItem(i)->key->getChar(j);
					this->files->outFile << map->getItem(i)->key->getChar(j);
				}
				this->files->logFile << std::setw((maxChars > 5 ? maxChars : 5) - map->getItem(i)->key->getSize() + 1) << std::setfill(' ') << std::right << '|'; this->files->logFile << std::setw(16) << std::left << map->getItem(i)->count; this->files->logFile << "|\n";
				this->files->outFile << std::setw((maxChars > 5 ? maxChars : 5) - map->getItem(i)->key->getSize() + 1) << std::setfill(' ') << std::right << '|'; this->files->outFile << std::setw(16) << std::left << map->getItem(i)->count; this->files->outFile << "|\n";
			}
			this->files->logFile << std::setw((maxChars > 5 ? maxChars : 5) + 24) << std::setfill('-') << '-';
			this->files->outFile << std::setw((maxChars > 5 ? maxChars : 5) + 24) << std::setfill('-') << '-';
			this->files->logFile << "\nПрограмма завершила свою работу.";
			delete words;
			delete map;
		}
		else {
			this->files->outFile << "Ошибка: в тексте не обнаружено ни одного слова.";
			this->files->logFile << "В тексте не обнаружено ни одного слова.\nПрограмма завершила свою работу.";
		}
		delete text;
	}
	else {
		this->files->outFile << "Ошибка: входной файл пуст.";
		this->files->logFile << "Входной файл пуст.\nПрограмма завершила свою работу.";
	}
}