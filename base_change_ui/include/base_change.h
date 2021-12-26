#ifndef _BASE_CHANGE_H_
#define _BASE_CHANGE_H_

#include <string>
#include <algorithm>

void        InitTables();
std::string Add(const std::string &a, const std::string &b, int base = 10);
std::string AsBase(int number, int base);
std::string ConvertBase(const std::string &number, int oldBase, int newBase);

#endif /* _BASE_CHANGE_H_ */