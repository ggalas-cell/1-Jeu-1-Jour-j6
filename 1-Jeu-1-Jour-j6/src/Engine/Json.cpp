#include "Json.h"
#include <iostream>
#include <fstream>

void Json::LoadFile(const char* path) {
	std::ifstream f(path);
	data = json::parse(f);

	
}

