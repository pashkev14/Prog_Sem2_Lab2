#pragma once

#include <fstream>

struct Files {

	std::ifstream inFile;
	std::ofstream outFile;
	std::ofstream logFile;
	
	Files(const char* in = "in.txt", const char* out = "out.txt", const char* log = "log.txt") {
		this->inFile.open(in);
		this->outFile.open(out);
		this->logFile.open(log);
	}

	~Files() {
		this->inFile.close();
		this->outFile.close();
		this->logFile.close();
	}

};