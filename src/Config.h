#pragma once

#include <vector>

#include "Question.h"
#include "Settings.h"

class Config { 
public:
	Settings settings;
	std::vector <Question*> questions;

	void init(std::string filename);
};
