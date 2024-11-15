#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

#define DEBUG_MODE true

#define TEST_FILE_PATH "test.txt"
#define FULL_FILE_PATH "input.txt"

#define TEST_FILE_EXP_VALUE_ONE 0
#define TEST_FILE_EXP_VALUE_TWO 0

// Part one of each day's challenge
int EvalOne(const std::vector<std::string>& data);
// Part two of each day's challenge
int EvalTwo(const std::vector<std::string>& data);
// Read file logic
std::vector<std::string> ReadFile(const std::string& filePath);
// Sums all integers in a vector
int SumVector(const std::vector<int>& values);
//--
std::vector<std::string> SplitString(const std::string LINE, const std::string SEPARATOR);
//--
//--
//--
int main(int argc, char** argv)
{
    if(DEBUG_MODE)
    {
        std::cout << "-------------- DEBUG MODE -------------" << std::endl;
        const std::vector<std::string> testData = ReadFile(TEST_FILE_PATH);

        // ======
        // Part 1
        // ======
        std::cout << "----------- EvalOne: TEST -----------" << std::endl;
        std:: cout << "Read line(s): " << testData.size() << std::endl;
        int testValueOne = EvalOne(testData);
        std::cout << "Expecting: " << TEST_FILE_EXP_VALUE_ONE << " Actual: " << testValueOne << std::endl;
        if(TEST_FILE_EXP_VALUE_ONE != testValueOne)
        {
            std::cout << "*** P1 TEST FAILURE ***" << std::endl;
        }
        // ======
        // Part 2
        // ======
        std::cout << "----------- EvalTwo: TEST -----------" << std::endl;
        std:: cout << "Read line(s): " << testData.size() << std::endl;
        int testValueTwo = EvalTwo(testData);
        std::cout << "Expecting: " << TEST_FILE_EXP_VALUE_TWO << " Actual: " << testValueTwo << std::endl;
        if(TEST_FILE_EXP_VALUE_TWO != testValueTwo)
        {
            std::cout << "*** P2 TEST FAILURE ***" << std::endl;
        }
    }
    else
    {
        const std::vector<std::string> realData = ReadFile(FULL_FILE_PATH);

        // ======
        // Part 1
        // ======
        std::cout << "----------- EvalOne: REAL -----------" << std::endl;
        std:: cout << "Read line(s): " << realData.size() << std::endl;
        int realValueOne = EvalOne(realData);
        std::cout << "Real file result: " << realValueOne << std::endl;

        // ======
        // Part 2
        // ======
        std::cout << "----------- EvalTwo: REAL -----------" << std::endl;
        std:: cout << "Read line(s): " << realData.size() << std::endl;
        int realValueTwo = EvalTwo(realData);
        std::cout << "Real file result: " << realValueTwo << std::endl;
    }
    
    std::cout << "-------------------------------------" << std::endl;
    return 0;
}
//--
int EvalOne(const std::vector<std::string>& data)
{
    std::vector<int> values;
    return SumVector(values);
}
//--
int EvalTwo(const std::vector<std::string>& data)
{
    std::vector<int> values;
    return SumVector(values);
}
//--
std::vector<std::string> ReadFile(const std::string& filePath)
{
    std::vector<std::string> retVal;
    std::ifstream file;
    file.open(filePath);
    std::string readStr;
    while(std::getline(file, readStr))
    {
        retVal.push_back(readStr);
    }
    file.close();
    return retVal;
}
//--
int SumVector(const std::vector<int>& values)
{
    int sum = 0;
    for(auto val : values)
    {
        sum += val;
    }

    return sum;
}
//--
std::vector<std::string> SplitString(const std::string LINE, const std::string SEPARATOR)
{
    
    std::vector<std::string> retVec;
    size_t sepLoc = LINE.find(SEPARATOR);
    size_t prevSepLoc = 0;
    std::string chunkStr;

    while(sepLoc != std::string::npos)
    {
        chunkStr = LINE.substr(prevSepLoc, sepLoc - prevSepLoc);
        retVec.push_back(chunkStr);

        prevSepLoc = sepLoc+SEPARATOR.size();
        sepLoc = LINE.find(SEPARATOR, prevSepLoc+1);
    }

    chunkStr = LINE.substr(prevSepLoc, sepLoc - prevSepLoc);
    retVec.push_back(chunkStr);

    return retVec;
}