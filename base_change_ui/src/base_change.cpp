#include "base_change.h"

using namespace std;

const int MIN_BASE = 2;
const int MAX_BASE = 36;

static bool tablesInitialised = false;
static char tblIntToChar[MAX_BASE] = {0};
static int  tblCharToInt[256] = {0};

void InitTables() {
    if (tablesInitialised) return;

    for (int i = 0; i < 10; i++) {
        tblIntToChar[i] = '0' + i;
        tblCharToInt[tblIntToChar[i]] = i;
    }

    for (int i = 0; i < 26; i++) {
        tblIntToChar[i + 10] = 'a' + i;
        tblCharToInt['a' + i] = i + 10;
        tblCharToInt['A' + i] = i + 10;
    }

    tablesInitialised = true;
}

// Adds two numbers using long addition.
string Add(const string &a, const string &b, int base) {
    InitTables();
    if (base > MAX_BASE || base < MIN_BASE) return "";

    // Reserve storage for the result.
    string result;
    result.reserve(1 + std::max(a.size(), b.size()));

    // Column positions and carry flag.
    int apos = a.size();
    int bpos = b.size();
    int carry = 0;

    // Do long arithmetic.
    while (carry > 0 || apos > 0 || bpos > 0) {
        if (apos > 0) carry += tblCharToInt[(unsigned char)a[--apos]];
        if (bpos > 0) carry += tblCharToInt[(unsigned char)b[--bpos]];
        result.push_back(tblIntToChar[carry % base]);
        carry /= base;
    }

    // The result string is backwards.  Reverse and return it.
    reverse(result.begin(), result.end());
    return result;
}

// Converts a single value to some base, intended for single-digit conversions.
string AsBase(int number, int base) {
    InitTables();
    if (number <= 0) return "0";
    string result;
    while (number > 0) {
        result += tblIntToChar[number % base];
        number /= base;
    }
    reverse(result.begin(), result.end());
    return result;
}

// Converts a number from one base to another.
string ConvertBase(const string &number, int oldBase, int newBase) {
    InitTables();
    string result;

    for (unsigned digit = 0; digit < number.size(); digit++) {
        int value = tblCharToInt[(unsigned char)number[digit]];
        if (result.empty()) {
            result = AsBase(value, newBase);
        } else {
            string temp = result;
            for (int i = 1; i < oldBase; i++) {
                temp = Add(result, temp, newBase);
            }
            result = Add(temp, AsBase(value, newBase), newBase);
        }
    }

    return result;
}