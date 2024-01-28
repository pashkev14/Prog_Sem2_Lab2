#pragma once

#include "Files.h"
#include "Text.h"
#include "WordArray.h"
#include "WordMap.h"
#include <iomanip>

class Solution {

private:

	Files* files;

	void readSolveAndOut();

public:

	Solution() {
		this->files = new Files;
	}

	~Solution() {
		delete this->files;
	}

	void checkFile();

};