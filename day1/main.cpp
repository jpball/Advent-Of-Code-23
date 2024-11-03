#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <set>
#include <unordered_map>
#include <ctype.h>

#define DEBUG_MODE false

#define TEST1_FILE_PATH "test1.txt"
#define TEST2_FILE_PATH "test2.txt"
#define FULL_FILE_PATH "input.txt"

#define TEST_FILE_EXP_VALUE_ONE 142
#define TEST_FILE_EXP_VALUE_TWO 281

// Part one of each day's challenge
int EvalOne(const std::vector<std::string>& data);
// Part two of each day's challenge
int EvalTwo(const std::vector<std::string>& data);
// Read file logic
std::vector<std::string> ReadFile(const std::string& filePath);

 std::unordered_map<std::string, size_t> numericals{
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };



int main(int argc, char** argv)
{    
    // ======
    // Part 1
    // ======
    // Evaluating test file
    const std::vector<std::string> testData = ReadFile(TEST1_FILE_PATH);
    const std::vector<std::string> test2Data = ReadFile(TEST2_FILE_PATH);
    const std::vector<std::string> realData = ReadFile(FULL_FILE_PATH);

    if(DEBUG_MODE){
        std::cout << "----------- EvalOne: TEST -----------" << std::endl;
        int testValueOne = EvalOne(testData);
        std::cout << "Expecting: " << TEST_FILE_EXP_VALUE_ONE << " Actual: " << testValueOne << std::endl;
        if(TEST_FILE_EXP_VALUE_ONE != testValueOne)
        {
            std::cout << "Test One failed.... exiting." << std::endl;
            return -2;
        }
    }
    else
    {
        //--
        // Evaluating real file
        std::cout << "----------- EvalOne: REAL -----------" << std::endl;
        int realValueOne = EvalOne(realData);
        std::cout << "Real file result: " << realValueOne << std::endl;
    }



    // ======
    // Part 2
    // ======

    // Evaluating test file for Part 2
    if(DEBUG_MODE)
    {
        std::cout << "----------- EvalTwo: TEST -----------" << std::endl;
        std:: cout << "Read line(s): " << test2Data.size() << std::endl;
        int testValueTwo = EvalTwo(test2Data);
        std::cout << "Expecting: " << TEST_FILE_EXP_VALUE_TWO << " Actual: " << testValueTwo << std::endl;

        if(TEST_FILE_EXP_VALUE_TWO != testValueTwo)
        {
            std::cout << "Test Two failed.... exiting." << std::endl;
            return -3;
        }
    }
    else
    {
            //--
        // Evaluating real file for Part 2
        std::cout << "----------- EvalTwo: REAL -----------" << std::endl;
        std:: cout << "Read line(s): " << realData.size() << std::endl;
        int realValueTwo = EvalTwo(realData);
        std::cout << "Real file result: " << realValueTwo << std::endl;
        std::cout << "-------------------------------------" << std::endl;
    

    }
    

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

        size_t leftIndex = 0;
        size_t rightIndex = lineWord.size();
        std::string number = "";

        while(!isnumber(lineWord[leftIndex]))
        {
            leftIndex++;
        }
        number.push_back(lineWord[leftIndex]);

        while(!isnumber(lineWord[rightIndex]))
        {
            rightIndex--;
        }
        number.push_back(lineWord[rightIndex]);


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
    std::vector<std::string> updatedData;

    for(const std::string& word : data)
    {
        //std::deque<size_t> numericalLocations(10, std::string::npos);
        size_t soonestNumericalLocation = SIZE_T_MAX;
        std::unordered_map<std::string, size_t>::iterator soonestNumerical;

        size_t latestNumericalLocation = 0;
        std::unordered_map<std::string, size_t>::iterator latestNumerical;

        for(auto it = numericals.begin(); it != numericals.end(); it++)
        {
            size_t location = word.find((*it).first);
            if(location == std::string::npos) continue;
            if(location < soonestNumericalLocation)
            {
                soonestNumericalLocation = location;
                soonestNumerical = it;
            }
            if(location > latestNumericalLocation)
            {
                latestNumericalLocation = location;
                latestNumerical = it;
            }
        }

        std::string cleansedWord = word;
        if(latestNumericalLocation != 0)
        {
            cleansedWord.replace(latestNumericalLocation, (*latestNumerical).first.size(), std::to_string(((*latestNumerical).second)));
        }

        if(soonestNumericalLocation != SIZE_T_MAX)
        {
            cleansedWord.replace(soonestNumericalLocation, (*soonestNumerical).first.size(), std::to_string(((*soonestNumerical).second)));
        }
        

        updatedData.push_back(cleansedWord);
    }


    // Calculate
    int result = 0;
    size_t leftIndex, rightIndex;
    for(auto word : updatedData)
    {
        leftIndex = 0;
        rightIndex = word.size() - 1;

        while(!isdigit(word.at(leftIndex)))
        {
            leftIndex++;
        }

        while(!isdigit(word.at(rightIndex)))
        {
            rightIndex--;
        }
        std::string formedNumber = "";
        formedNumber.push_back(word.at(leftIndex));
        formedNumber.push_back(word.at(rightIndex));
        result += stoi(formedNumber);
    }
    
    return result;
    
    
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

