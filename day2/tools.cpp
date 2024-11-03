
#include "tools.h"

std::vector<std::string> SplitString(const std::string LINE, const std::string SEPARATOR)
{
    
    std::vector<std::string> retVec;
    size_t sepLoc = LINE.find(SEPARATOR);
    size_t prevSepLoc = 0;
    std::string chunkStr;

    
    // "Hello; World; There; Is; An Apple", "; ";
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