#pragma once
#include <string>
#include "render.h"
std::string* fileToString(const char * fileName);
shader makeShaderFrom(const char * vertSource, const char * fragSource);
shader makeShaderFrom(std::string fileName);