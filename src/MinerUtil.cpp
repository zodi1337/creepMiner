//  cryptoport.io Burst Pool Miner
//
//  Created by Uray Meiviar < uraymeiviar@gmail.com > 2014
//  donation :
//
//  [Burst  ] BURST-8E8K-WQ2F-ZDZ5-FQWHX
//  [Bitcoin] 1UrayjqRjSJjuouhJnkczy5AuMqJGRK4b

#include "Miner.h"

bool Burst::isNumberStr(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

std::string Burst::getFileNameFromPath(const std::string& strPath)
{
    size_t iLastSeparator = 0;
    return strPath.substr((iLastSeparator = strPath.find_last_of("/\\")) != std::string::npos ? iLastSeparator + 1 : 0, strPath.size() - strPath.find_last_of("."));
}

std::vector<std::string> Burst::splitStr(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    splitStr(s, delim, elems);
    return elems;
}

std::vector<std::string>& Burst::splitStr(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

bool Burst::isValidPlotFile(const std::string filePath)
{
    bool result = false;
    std::string fileName = getFileNameFromPath(filePath);
    if(getAccountIdFromPlotFile(fileName)  != "" &&
       getStartNonceFromPlotFile(fileName) != "")
    {
        struct stat info;
        int statResult = stat( filePath.c_str(), &info );
        
        if( statResult == 0)
        {
            if( (info.st_mode & S_IFDIR) == 0)
            {
                std::ifstream testRead(filePath);
                if(testRead.good())
                {
                    result = true;
                }
                testRead.close();
            }
        }
    }
    
    return result;
}

std::string Burst::getAccountIdFromPlotFile(const std::string path)
{
    size_t filenamePos = path.find_last_of("/\\");
    if(filenamePos == std::string::npos)
    {
        filenamePos = 0;
    }
    std::vector<std::string> fileNamePart = splitStr(path.substr(filenamePos+1,path.length()-(filenamePos+1)),'_');
    if(fileNamePart.size() > 3)
    {
        std::string accountIdPart = fileNamePart[0];
        if(isNumberStr(accountIdPart))
        {
            return accountIdPart;
        }
    }
    return "";
}

std::string Burst::getNonceCountFromPlotFile(const std::string path)
{
    size_t filenamePos = path.find_last_of("/\\");
    if(filenamePos == std::string::npos)
    {
        filenamePos = 0;
    }
    std::vector<std::string> fileNamePart = splitStr(path.substr(filenamePos+1,path.length()-(filenamePos+1)),'_');
    if(fileNamePart.size() > 3)
    {
        std::string nonceCountPart = fileNamePart[2];
        if(isNumberStr(nonceCountPart))
        {
            return nonceCountPart;
        }
    }
    return "";
}

std::string Burst::getStaggerSizeFromPlotFile(const std::string path)
{
    size_t filenamePos = path.find_last_of("/\\");
    if(filenamePos == std::string::npos)
    {
        filenamePos = 0;
    }
    std::vector<std::string> fileNamePart = splitStr(path.substr(filenamePos+1,path.length()-(filenamePos+1)),'_');
    if(fileNamePart.size() > 3)
    {
        std::string staggerPart = fileNamePart[3];
        if(isNumberStr(staggerPart))
        {
            return staggerPart;
        }
    }
    return "";
}

std::string Burst::getStartNonceFromPlotFile(const std::string path)
{
    size_t filenamePos = path.find_last_of("/\\");
    if(filenamePos == std::string::npos)
    {
        filenamePos = 0;
    }
    std::vector<std::string> fileNamePart = splitStr(path.substr(filenamePos+1,path.length()-(filenamePos+1)),'_');
    if(fileNamePart.size() > 3)
    {
        std::string nonceStartPart = fileNamePart[1];
        if(isNumberStr(nonceStartPart))
        {
            return nonceStartPart;
        }
    }
    return "";
}