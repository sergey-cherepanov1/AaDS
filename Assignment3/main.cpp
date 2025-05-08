/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment2
*/

#include "shannon.h"

int main()
{
    std::string text = "";
    std::vector<std::pair<char, double>> t = read("1", text);
    std::cout << text << '\n';
    std::map<char, std::string> dict;
    for (auto& [key, value] : t)
    {
        dict[key] = "";
    }
    encode(t, dict);
    for (auto& [key, value] : dict)
    {
        std::cout << '[' << key << "] = " << value << ";\n";
    }
    write(text, dict);
}
