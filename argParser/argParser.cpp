#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include "argParser.h"
#include <string>

int min(int a, int b){
    return (a < b) ? a : b;
}

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

std::string ArgParser::kwHelpName(std::string name, std::string shortname){
    return "--" + name + "/-" + shortname + ":";
}

std::string ArgParser::posHelpName(std::string name){
    return "--" + name + ":";
}

void ArgParser::checkHelpNameLen(std::string helpName){
    if (helpName.size() > longestHelpName){
        longestHelpName = helpName.size();
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
    helpName = kwHelpName(fullName, shortName);
    checkHelpNameLen(helpName);
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
    helpName = kwHelpName(name, shortName);
    checkHelpNameLen(helpName);
}

void ArgParser::addPositional(const std::string name, std::string defaultValue, std::string help ){
    npositionals++;
    checkArgs(name);
    posArgs.push_back(name);
    posValues[name] = defaultValue;
    allValues[name] = defaultValue;
    allArgs.push_back(name);
    argHelpStrings[name] = help;
    helpName = name + ":";
    if (helpName.size() > longestHelpName){
        longestHelpName = helpName.size();
    }
    helpName = posHelpName(name);
    checkHelpNameLen(helpName);

}
void ArgParser::addMultiPositional(const std::string name , std::string help){
    //arbitrary length positional
    if (multi){
        std::cout << "only one multi positional argument can be declared\n";
        exit(-1);
    }
    multi = true;
    multiName = name;
    allArgs.push_back(name);
    argHelpStrings[name] = help;
    helpName = posHelpName(name);
    checkHelpNameLen(helpName);
    /*
    for (int i; i < length; i++){
        posArgs.push_back(name);
    }
    */
}

std::string ArgParser::makeDescriptionString(std::string helpstring, std::string descstring){

    int descriptionSpace {maxLineLength - longestHelpName - helpSpacing};
    
    auto helpdescspace {longestHelpName  + helpSpacing - helpstring.size()}; //auto to prevent conversion warning of size_type to int
    if (helpstring.size() + descstring.size()+ helpSpacing < maxLineLength){
        return helpstring + std::string(helpdescspace,' ')+ descstring + "\n";
    }

    std::string newstring = descstring.substr(0, descriptionSpace) + "\n";

    for (int i = 0; i < descstring.size()/descriptionSpace; i++){
        int endline = min(descriptionSpace, descstring.size() - descriptionSpace*(i+1));
        newstring += std::string(longestHelpName+helpSpacing, ' ') +  descstring.substr(descriptionSpace*(i+1), endline) + "\n";
    }
    return helpstring + std::string(helpdescspace,' ') + newstring;
}

void ArgParser::readArguments(int argc, char *argv[])
{   

    if (longestHelpName > maxLineLength){
        maxLineLength = longestHelpName + 140;
    }
    int descriptionSpace {longestHelpName + helpSpacing};
    std::string descriptionString;
    std::vector<std::string> givenKeywords;
    std::vector<int> paPositions; //positional argument positions

    std::string filename = argv[0];
    helpString = "usage: " + filename + " ";
    for (int i = 0; i < kwargs.size(); i++){
        helpString += "[--" + kwargs[i] + "/-" + shortKwargs[i] + "] ";
    }
    for (int i = 0; i < flagList.size(); i++){
        helpString += "[--" + flagList[i] + "/-" + shortFlagList[i] + "] ";
    }
    for (std::string arg : posArgs){
        helpString += "<" + arg + "> ";
    }
    if (multi){
        helpString += "<" + multiName+ "(multiple positions)> ";
    } 
    helpString += "\n---------\n\nkey word arguments:\n\n";

    for (int i = 0; i < kwargs.size(); i++){
        helpName = kwHelpName(kwargs[i],shortKwargs[i]);
        nspaces = longestHelpName + helpSpacing - helpName.size();
        //descriptionString = argHelpStrings[kwargs[i]];
        descriptionString = makeDescriptionString(helpName, argHelpStrings[kwargs[i]]);
        helpString +=  descriptionString ;//helpName + std::string(nspaces, ' ') + argHelpStrings[kwargs[i]] + "\n";
    }
    helpString += "\nflags\n\n";
    for (int i = 0; i < flagList.size(); i++){
        helpName = kwHelpName(flagList[i], shortFlagList[i]);
        nspaces = longestHelpName + helpSpacing - helpName.size();
        descriptionString = makeDescriptionString(helpName, argHelpStrings[kwargs[i]]);
        helpString += descriptionString; //helpName + std::string(nspaces,' ') + argHelpStrings[flagList[i]] + "\n";
    }
    helpString += "\npositional arguments:\n\n";
    for (std::string arg : posArgs){
        helpName = posHelpName(arg);
        nspaces = longestHelpName + helpSpacing - helpName.size();
        descriptionString = makeDescriptionString(helpName, argHelpStrings[arg]);
        helpString += descriptionString; //helpName + std::string(nspaces, ' ') + argHelpStrings[arg] + "\n";
    }
    if (multi){
        helpName = posHelpName(multiName);
        nspaces = longestHelpName + helpSpacing - helpName.size();
        descriptionString = makeDescriptionString(helpName, argHelpStrings[multiName]);
        helpString += descriptionString; //helpName + std::string(nspaces, ' ') + argHelpStrings[multiName] + "\n";

    }
    helpString += "\n";
    for (int i = 1; i < argc; i++){
        bool flag = false;
        bool inKW = false;
        std::string argument = argv[i];
        if (argument == "--help" | argument == "-h"){
            std::cout << helpString;
            exit(0);
        }
        for (int j = 0; j < kwargs.size(); j++){
            std::string kw = kwargs[j];
            std::string skw = shortKwargs[j];
            if (argument == "--" + kw | argument == "-" + skw){
                kwargValues[kw] = argv[i + 1];
                allValues[kw] = argv[i + 1];
                i++;
                inKW = true;
                break;
            }
            
        }

        if (!inKW){
            for (int j = 0; j < flagList.size(); j++)
            {
                if (argument == "--" + flagList[j] | argument == "-" + shortFlagList[j]){
                    flagValues[flagList[j]] = !flagValues[flagList[j]];
                    allValues[flagList[j]] = boolToString(flagValues[flagList[j]]);
                    flag = true;
                    break;
                }
            }
            if (flag){
                continue;
            }
            paPositions.push_back(i);
        }
        if (argument[0] == '-' & !inKW & !flag){
            std::string message {argument + " not in keyword or flag arguments, exiting"};
            //throw std::invalid_argument(argument + " not in keyword or flag arguments");
            std::cout << message;
            exit(-1);
        }
    }
    if (paPositions.size() > posArgs.size() & !multi){
        //throw std::invalid_argument("too many positional arguments given");
        std::cout << "error: number of given arguments greater than number registered, and multiple positional arguments not added\nexiting\n";
        exit(-1);
    }
    for (int i = 0; i < paPositions.size(); i++){

        if (i < npositionals){
            posValues[posArgs[i]] = argv[paPositions[i]];
            allValues[posArgs[i]] = argv[paPositions[i]];
        }
        else{
            multiPosValues.push_back(argv[paPositions[i]]);
        }
        
    }
}

std::map<std::string, std::string> ArgParser::getAllArgs(){
    return allValues;
}

std::vector<std::string> ArgParser::getMultiArgs(){
    //get values of multipositional arguments as a string vector
    return multiPosValues;
}


bool ArgParser::getFlag(const std::string &name)
{
    return flagValues[name];
};

