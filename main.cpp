/*
	Программа по исследованию текста на уникальные слова
	Автор: Савин Павел Алексеевич, группа 2309. Версия 2.1.2
	Даты: Начало: 06.03.2023 Окончание: 20.03.2023
*/

#include "Solution.h"

int main() {
	Solution* solver = new Solution;
	solver->checkFile();
	delete solver;
	return 0;
}