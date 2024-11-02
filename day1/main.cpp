#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

#define DEBUG_MODE true

#define TEST_FILE_PATH "test.txt"
#define FULL_FILE_PATH "input.txt"

#define TEST_FILE_EXP_VALUE_ONE 142
#define TEST_FILE_EXP_VALUE_TWO 0

// Part one of each day's challenge
int EvalOne(const std::vector<std::string>& data);
// Part two of each day's challenge
int EvalTwo(const std::vector<std::string>& data);
// Read file logic
std::vector<std::string> ReadFile(const std::string& filePath);

int main(int argc, char** argv)
{
    if(sizeof(TEST_FILE_PATH) == 0 || sizeof(FULL_FILE_PATH) == 0)
    {
        std::cout << "-- Must provide file name(s)" << std::endl;
        return -1;
    }
    /*
    ======
    Part 1
    ======
    */
    // Evaluating test file
    std::cout << "----------- EvalOne: TEST -----------" << std::endl;
    const std::vector<std::string> testData = ReadFile(TEST_FILE_PATH);

    if(DEBUG_MODE)
    {
        std:: cout << "Read line(s): " << testData.size() << std::endl;
    }

    int testValueOne = EvalOne(testData);
    std::cout << "Expecting: " << TEST_FILE_EXP_VALUE_ONE << " Actual: " << testValueOne << std::endl;
    if(TEST_FILE_EXP_VALUE_ONE != testValueOne)
    {
        std::cout << "Test One failed.... exiting." << std::endl;
        return -2;
    }

    //--
    // Evaluating real file
    std::cout << "----------- EvalOne: REAL -----------" << std::endl;
    const std::vector<std::string> realData = ReadFile(FULL_FILE_PATH);

    if(DEBUG_MODE)
    {
        std:: cout << "Read line(s): " << realData.size() << std::endl;
    }
    int realValueOne = EvalOne(realData);
    std::cout << "Real file result: " << realValueOne << std::endl;

    /*
    ======
    Part 2
    ======
    */
    /*
    // Evaluating test file for Part 2
    std::cout << "----------- EvalTwo: TEST -----------" << std::endl;
    std:: cout << "Read line(s): " << testData.size() << std::endl;
    int testValueTwo = EvalTwo(testData);
    std::cout << "Expecting: " << TEST_FILE_EXP_VALUE << " Actual: " << testValueTwo << std::endl;

    //--
    // Evaluating real file for Part 2
    std::cout << "----------- EvalTwo: REAL -----------" << std::endl;
    std:: cout << "Read line(s): " << realData.size() << std::endl;
    int realValueTwo = EvalTwo(realData);
    std::cout << "Real file result: " << realValueTwo << std::endl;
    */
    std::cout << "-------------------------------------" << std::endl;
    return 0;
}
//--
/*
    Combine first digit and last digit and add together
    1abc2 - 12
    pqr3stu8vwx - 38
    a1b2c3d4e5f - 15
    treb7uchet - 77
*/
int EvalOne(const std::vector<std::string>& data)
{
    std::vector<int> extractedNumbers;

    for(int i = 0; i < data.size(); i++)
    {
        std::string lineWord = data.at(i);

        size_t l_index = 0;
        size_t r_index = lineWord.size();
        std::string number = "";

        while(!isnumber(lineWord[l_index]))
        {
            l_index++;
        }
        number.push_back(lineWord[l_index]);

        while(!isnumber(lineWord[r_index]))
        {
            r_index--;
        }
        number.push_back(lineWord[r_index]);


        extractedNumbers.push_back(stoi(number));
    }

    // Calculate total
    int sum = 0;
    for(int i = 0; i < extractedNumbers.size(); i++)
    {
        sum += extractedNumbers.at(i);
    }

    return sum;
}
//--
int EvalTwo(const std::vector<std::string>& data)
{
    return 0;
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

