#ifndef HEXUTILS_H
#define HEXUITLS_H

#include <string>
#include <sstream>

bool checkHexString(const std::string& str)
{
	return str.find_first_not_of("0123456789abcdefABCDEF", 0) == std::string::npos;
}

uint64_t hexStrToUInt32(const std::string& str)
{
	if (!checkHexString(str) && str.size() > 8) return 0;
	std::istringstream sstream(str);
	uint64_t value;
	sstream >> std::hex >> value;
	return value;
}

size_t clamp(const size_t& min, const size_t& max, const size_t& value)
{
	return value > min ? (value < max ? value : max) : min;
}

#endif