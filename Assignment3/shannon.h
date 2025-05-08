/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment2
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

#ifndef SHANNON_H
#define SHANNON_H

std::vector<std::pair<char, double>> read(std::string filename, std::string& t)
{
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    if (!in.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
    }
    std::map<char, double> dict;
    char c;
    int i = 0;
    while (in.get(c))
    {
        if (c != '\n')
        {
            ++i;
            if (dict.find(c) != dict.end())
            {
                dict[c] += 1;
            } else 
            {
                dict[c] = 1;
            }
            t += c;
        }
    }
    in.close();
    for (auto& v: dict)
    {
        v.second /= i;
    }
    std::vector<std::pair<char, double>> sorted(dict.begin(), dict.end());
    std::sort(sorted.begin(), sorted.end(),
        [](auto& a, auto& b) {
            return a.second >= b.second;
        }
    );
    return sorted;
}

void write(std::string& text, std::map<char, std::string>& dict)
{
    std::ofstream out("encoded", std::ios::binary | std::ios::out);
    if (!out.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
    }
    for (auto c: text)
    {
        out << dict[c];
    }
    out.close();
    std::ofstream file("dictionary", std::ios::binary | std::ios::out);
    for (auto [key, value]: dict)
    {
        file << '[' << key << "] = " << value << ";\n";
    }
    file.close();
}

void encode(std::vector<std::pair<char, double>>& freq, std::map<char, std::string>& dict)
{
    int size = freq.size();
    if (size == 1) {return;}
    double sum = 0;
    for (auto& t: freq)
    {
        sum += t.second;
    }
    sum /= 2;
    double t = 0;
    std::vector<std::pair<char, double>> left;
    std::vector<std::pair<char, double>> right;
    int rest = 0;
    for (int i = 0; i < size - 1; ++i)
    {
        ++rest;
        dict[freq[i].first] += "0";
        t += freq[i].second;
        left.push_back(freq[i]);
        if (t + freq[i + 1].second > sum)
        {
            if ((t + freq[i + 1].second - sum) < (sum - t))
            {
                ++rest;
                dict[freq[i + 1].first] += "0";
                t += freq[i + 1].second;
                left.push_back(freq[i + 1]);
                break;
            }
            break;
        }
    }
    for (int j = rest; j < size; ++j)
    {
        dict[freq[j].first] += "1";
        right.push_back(freq[j]);
    }
    encode(left, dict); 
    encode(right, dict);
}


#endif
