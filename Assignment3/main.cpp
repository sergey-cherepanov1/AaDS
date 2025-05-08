/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment2
*/

#include "shannon.h"

int main()
{
    std::string text = "";
    std::vector<std::pair<char, double>> t = readUncompressed("uncompressed", text);
    std::map<char, std::string> dict;
    for (auto& [key, value] : t)
    {
        dict[key] = "";
    }
    encode(t, dict);
    writeCompressed(text, dict1);
    readDecodeWrite();
}
