/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment3
*/

#include <gtest/gtest.h>
#include "shannon.h"

TEST(ReadUncompressedTest, BasicTest)
{
    std::string text;
    std::ofstream test_file("test_uncompressed.txt");
    test_file << "aabbcc";
    test_file.close();

    auto result = readUncompressed("test_uncompressed.txt", text);

    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(text, "aabbcc");
    EXPECT_DOUBLE_EQ(result[0].second, 2./6);
    EXPECT_DOUBLE_EQ(result[1].second, 2./6);
    EXPECT_DOUBLE_EQ(result[2].second, 2./6);
}

TEST(EncodeTest, BasicEncoding)
{
    std::vector<std::pair<char, double>> freq =
    {
        {'a', 0.5},
        {'b', 0.3},
        {'c', 0.2}
    };
    std::map<char, std::string> dict;
    for (auto& [key, value] : freq)
    {
        dict[key] = "";
    }

    encode(freq, dict);

    ASSERT_EQ(dict.size(), 3);
    std::set<std::string> codes;
    for (auto& [k, v] : dict)
    {
        codes.insert(v);
    }
    EXPECT_EQ(codes.size(), 3);
}

TEST(CompressionCycleTest, EndToEnd)
{
    std::ofstream test_file("test_input.txt");
    test_file << "aaabbbccd";
    test_file.close();

    std::string text;
    auto freq = readUncompressed("test_input.txt", text);

    std::map<char, std::string> dict;
    for (auto& [key, value] : freq)
    {
        dict[key] = "";
    }
    encode(freq, dict);
    writeCompressed(text, dict);
    readDecodeWrite();
    std::ifstream decoded("decoded");
    std::string decoded_text((std::istreambuf_iterator<char>(decoded)),
                             std::istreambuf_iterator<char>());

    EXPECT_EQ(decoded_text, "aaabbbccd");
}

TEST(ReadUncompressedTest, EmptyFile)
{
    std::string text;
    std::ofstream("empty.txt").close();
    auto result = readUncompressed("empty.txt", text);
    EXPECT_TRUE(result.empty());
    EXPECT_TRUE(text.empty());
}

TEST(EncodeTest, SingleSymbol)
{
    std::vector<std::pair<char, double>> freq = {{'a', 1.0}};
    std::map<char, std::string> dict;
    encode(freq, dict);
    EXPECT_EQ(dict['a'], "");
}

TEST(EncodeTest, CodeLengths)
{
    std::vector<std::pair<char, double>> freq =
    {
        {'a', 0.4},
        {'b', 0.3},
        {'c', 0.2},
        {'d', 0.1}
    };
    std::map<char, std::string> dict;
    for (auto& [k, v] : freq) dict[k] = "";

    encode(freq, dict);

    EXPECT_LT(dict['a'].size(), dict['d'].size());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
