#ifndef __ITEMDATA__
#define __ITEMDATA__


#include <string>
#include <istream>
#include <sstream>

struct ItemData {
    std::string date;
    double low, high, open, close, volume;
    int ivr;

    static ItemData fromCsvLine(std::istream& stream)
    {
        constexpr int count = 7;

        std::string line;
        std::stringstream linestream;
        /**
         * 第一行的数据全部忽略掉
         * 第二行开始的数据是以 , 来进行分割的
        */
        if ( std::getline(stream, line) ) {
            std::string cells[count];
            linestream << line;

            for (int i = 0; i < count && std::getline(linestream, cells[i], ','); i++) 
                ;

            auto doubleOrZero = [](const std::string& str) { return str.empty() ? 0.0 : std::stod(str); };
            auto intOrZero = [](const std::string& str) { return str.empty() ? 0 : std::stoi(str); };

            ItemData result {
                cells[0],
                doubleOrZero(cells[1]),
                doubleOrZero(cells[2]),
                doubleOrZero(cells[3]),
                doubleOrZero(cells[4]),
                doubleOrZero(cells[5]),
                intOrZero(cells[6])
            };
            return result;
        }
        else 
        {
            return {};
        }
    }
};





#endif