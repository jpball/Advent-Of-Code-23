#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tools.h"

#define DEBUG_MODE false

#define TEST_FILE_PATH "test.txt"
#define FULL_FILE_PATH "input.txt"

#define TEST_FILE_EXP_VALUE_ONE 8
#define TEST_FILE_EXP_VALUE_TWO 2286

const size_t GAME_PREFIX_SIZE = std::string("Game ").size();

// Part one of each day's challenge
int EvalOne(const std::vector<std::string>& data);
// Part two of each day's challenge
int EvalTwo(const std::vector<std::string>& data);
// Read file logic
std::vector<std::string> ReadFile(const std::string& filePath);
//
int SumVector(const std::vector<int>& values);

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
    const size_t NUM_RED = 12;
    const size_t NUM_BLUE = 14;
    const size_t NUM_GREEN = 13;
    for(std::string line : data)
    {
        const std::vector<std::string> GAME_DATA_SPLIT = SplitString(line, ": ");
        int gameNum = stoi(GAME_DATA_SPLIT.at(0).substr(GAME_PREFIX_SIZE));

        const std::vector<std::string> GAME_CUBE_SETS = SplitString(GAME_DATA_SPLIT.at(1), "; ");
        // "3 blue, 4 red", "1 red, 2 green, 6 blue", "2 green"

        bool gamePossible = true;
        for(const std::string& CUBE_SET : GAME_CUBE_SETS)
        {
            auto set = SplitString(CUBE_SET, ", ");
            // "3 blue", "4 red"
            int cubeCount;
            size_t spaceIndex;
            for(auto cubeInstance : set)
            {
                spaceIndex = cubeInstance.find(" ");
                cubeCount = stoi(cubeInstance.substr(0, spaceIndex));
                switch(cubeInstance.at(spaceIndex+1))
                {
                    case 'r':
                        if(cubeCount > NUM_RED) gamePossible = false;
                        break;
                    case 'b':
                        if(cubeCount > NUM_BLUE) gamePossible = false;
                        break;
                    case 'g':
                        if(cubeCount > NUM_GREEN) gamePossible = false;
                        break;
                    default:
                        break;
                }
                if(!gamePossible) break;
            }
        }

        if(gamePossible)
        {
            values.push_back(gameNum);
        }
    

    }




    return SumVector(values);
}
//--
int EvalTwo(const std::vector<std::string>& data)
{
    std::vector<int> values;

    for(std::string line : data)
    {
        const std::vector<std::string> GAME_DATA_SPLIT = SplitString(line, ": ");
        int gameNum = stoi(GAME_DATA_SPLIT.at(0).substr(GAME_PREFIX_SIZE));

        const std::vector<std::string> GAME_CUBE_SETS = SplitString(GAME_DATA_SPLIT.at(1), "; ");
        // "3 blue, 4 red", "1 red, 2 green, 6 blue", "2 green"

        int maxRedSoFar = 0;
        int maxBlueSoFar = 0;
        int maxGreenSoFar = 0;
        for(const std::string& CUBE_SET : GAME_CUBE_SETS)
        {
            auto set = SplitString(CUBE_SET, ", ");
            // "3 blue", "4 red"
            int cubeCount;
            size_t spaceIndex;
            for(auto cubeInstance : set)
            {
                spaceIndex = cubeInstance.find(" ");
                cubeCount = stoi(cubeInstance.substr(0, spaceIndex));
                switch(cubeInstance.at(spaceIndex+1))
                {
                    case 'r':
                        if(cubeCount > maxRedSoFar)
                        {
                            maxRedSoFar = cubeCount;
                        }
                        break;
                    case 'b':
                        if(cubeCount > maxBlueSoFar)
                        {
                            maxBlueSoFar = cubeCount;
                        }
                        break;
                    case 'g':
                        if(cubeCount > maxGreenSoFar)
                        {
                            maxGreenSoFar = cubeCount;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        values.push_back(maxRedSoFar*maxBlueSoFar*maxGreenSoFar);


    }




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
int SumVector(const std::vector<int>& values)
{
    int sum = 0;
    for(auto val : values)
    {
        sum += val;
    }

    return sum;
}