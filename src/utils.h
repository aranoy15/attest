#pragma once

#include <vector>
#include <string>

namespace utils
{
/** Функция для парсинга строки по символу */
std::vector<std::string> split(std::string& message, char symbol);
}