#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include "argParser.h"
#include <string>


bool isIn(std::string s, std::string pattern){
    if (s.find(pattern)!= -1){
        return true;
    }
    else {
        return false;
    }
}

std::vector<std::string> splitString(std::string inputString, std::string delimiter){
    int pos;
    std::string substring;
    std::vector<std::string> outVector;
    std::string  tempString = inputString;
    if (delimiter ==" "){
        while (isIn(tempString,"  ")){ // check if 2 consecutive spaces in string, replace with 1
            tempString = tempString.replace(tempString.find("  "),2," ");
        }
        if (tempString.find(" ") == 0){
            tempString = tempString.replace(0,1,"");
        }
    }
    while (true){
        pos = tempString.find(delimiter);
        substring = tempString.substr(0,pos);
        outVector.push_back(substring);
        if (tempString.find(delimiter) == -1){
            break;
        }
        tempString.erase(0,pos+delimiter.length());    
    }
    return outVector;
}

std::string ArgParser::boolToString(bool value)
{
    if (value)
    {
        return "true";
    }
    return "false";
}

void ArgParser::checkArgs(std::string name)
{
    for (std::string arg : allArgs)
    {
        if (name == arg)
        {
            std::cout << "Error: '" + name + "' is declared more than once\n";
            throw std::runtime_error("is declared more than once");
        }
    }
}


void ArgParser::addKW(const std::string fullName, std::string defaultValue , std::string shortName , std::string help )
{
    checkArgs(fullName);
    if (shortName == "")
    {
        shortName = fullName;
    }
    shortKwargs.push_back(shortName);
    kwargs.push_back(fullName);
    kwargValues[fullName] = defaultValue;
    allValues[fullName] = defaultValue;
    allArgs.push_back(fullName);
    argHelpStrings[fullName] = help;
}
    
void ArgParser::addFlag(std::string name, bool returnValue , std::string shortName , std::string help )
{
    if (shortName == "")
    {
        shortName = name;
    }
    flagList.push_back(name);
    shortFlagList.push_back(shortName);
    flagValues[name] = !returnValue;
    allValues[name] = boolToString(!returnValue);
    argHelpStrings[name] = help;
}
void ArgParser::addPositional(const std::string name, std::string defaultValue, std::string help )
{
    checkArgs(name);
    posArgs.push_back(name);
    posValues[name] = defaultValue;
    allValues[name] = defaultValue;
    allArgs.push_back(name);
    argHelpStrings[name] = help;
}
void ArgParser::addMultiPositional(const std::string name, const int length )
{
    allArgs.push_back(name);
    /*
    for (int i; i < length; i++){
        posArgs.push_back(name);
    }
    */
}
void ArgParser::readArguments(int argc, char *argv[])
{
    std::vector<int> paPositions;

    std::string filename = argv[0];
    helpString = "usage: " + filename + " ";
    for (int i = 0; i < kwargs.size(); i++)
    {
        helpString += "[--" + kwargs[i] + "/-" + shortKwargs[i] + "] ";
    }
    for (int i = 0; i < flagList.size(); i++)
    {
        helpString += "[--" + flagList[i] + "/-" + shortFlagList[i] + "] ";
    }
    for (std::string arg : posArgs)
    {
        helpString += "<" + arg + "> ";
    }
    helpString += "\n---------\n\nkey word arguments:\n\n";

    for (int i = 0; i < kwargs.size(); i++)
    {
        helpString += "--" + kwargs[i] + "/-" + shortKwargs[i] + ": " + argHelpStrings[kwargs[i]] + "\n";
    }
    helpString += "\nflags\n\n";
    for (int i = 0; i < flagList.size(); i++)
    {
        helpString += "--" + flagList[i] + "/-" + shortFlagList[i] + ": " + argHelpStrings[flagList[i]] + "\n";
    }
    helpString += "\npositional arguments:\n\n";
    for (std::string arg : posArgs)
    {
        helpString += arg + ": " + argHelpStrings[arg] + "\n";
    }
    helpString += "\n";
    for (int i = 1; i < argc; i++)
    {
        bool flag = false;
        bool inKW = false;
        std::string argument = argv[i];
        if (argument == "--help" | argument == "-h")
        {
            std::cout << helpString;
            exit(0);
        }
        for (int j = 0; j < kwargs.size(); j++)
        {
            std::string kw = kwargs[j];
            std::string skw = shortKwargs[j];
            if (argument == "--" + kw | argument == "-" + skw)
            {
                kwargValues[kw] = argv[i + 1];
                allValues[kw] = argv[i + 1];
                i++;
                inKW = true;
                break;
            }
        }

        if (!inKW)
        {
            for (int j = 0; j < flagList.size(); j++)
            {
                if (argument == "--" + flagList[j] | argument == "-" + shortFlagList[j])
                {
                    flagValues[flagList[j]] = !flagValues[flagList[j]];
                    allValues[flagList[j]] = boolToString(flagValues[flagList[j]]);
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                continue;
            }
            paPositions.push_back(i);
        }
    }
    if (paPositions.size() > posArgs.size())
    {
        std::cout << "warning: number of given arguments greater than number registered\n";
    }
    for (int i = 0; i < paPositions.size(); i++)
    {
        if (i > posArgs.size() - 1)
        {
            break;
        }
        posValues[posArgs[i]] = argv[paPositions[i]];
        allValues[posArgs[i]] = argv[paPositions[i]];
    }
}

std::map<std::string, std::string> ArgParser::getAllArgs()
{
    return allValues;
}



bool ArgParser::getFlag(const std::string &name)
{
    return flagValues[name];
};

