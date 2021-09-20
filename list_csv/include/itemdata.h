#ifndef __ITEMDATA__
#define __ITEMDATA__


#include <string>
#include <istream>
#include <sstream>

struct ItemData {
    /**
     * csv 的数据当中包含了下面的这几项
     * 一共有 7 项 
    */
    std::string date;
    double low, high, open, close, volume;
    int ivr;

    static ItemData fromCsvLine(std::istream& stream)
    {
        constexpr int count = 7;

        std::string line;
        std::stringstream linestream;

        if ( std::getline(stream, line) ) {
            std::string cells[count];
            linestream << line;
            
            /**
             * 将每一行的数据根据 , 来进行分割，全部存储到数组当中去
            */
            for (int i = 0; i < count && std::getline(linestream, cells[i], ','); i++) 
                ;

            /**
             * 两个 lambda 表达式， 分别完成字符串转浮点数和字符串转整数
            */
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