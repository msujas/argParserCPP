#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>


bool isIn(std::string s, std::string pattern);

std::vector<std::string> splitString(std::string inputString, std::string delimiter=",");

template <typename T1>
T1 convertString(const std::string &stringValue)
{
    std::istringstream iss(stringValue);
    T1 outValue;
    iss >> outValue;
    if (iss.fail())
    {
        std::cout << "Error: type conversion failed for argument: " << stringValue << std::endl;
        throw std::invalid_argument("type conversion failed");
    }
    return outValue;
}

class ArgParser{   
private:
    std::vector<std::string> kwargs;
    std::vector<std::string> shortKwargs;
    std::map<std::string, std::string> kwargValues;
    std::vector<std::string> posArgs;
    std::vector<std::string> allArgs;
    std::vector<std::string> flagList;
    std::vector<std::string> shortFlagList;
    std::map<std::string, bool> flagValues;
    std::map<std::string, std::string> posValues;
    std::map<std::string,std::string> allValues;
    std::string helpString;
    std::map<std::string,std::string> argHelpStrings;
    std::string boolToString(bool value);
    int npositionals {0};
    std::vector<std::string> multiPosValues;
    std::string multiName {""};
    bool multi {false};
public:
    
    void checkArgs(std::string name);
    void addKW(const std::string fullName,std::string defaultValue = "", std::string shortName = "", std::string help = "");

    void addFlag(std::string name, bool returnValue = true, std::string shortName="", std::string help = "");
    void addPositional(const std::string name, std::string defaultValue = "", std::string help = "");
    void addMultiPositional(const std::string name,std::string help = "");
    void readArguments(int argc, char *argv[]);
    std::map<std::string, std::string> getAllArgs();
template <typename T>
T getArg(const std::string &name)
{
    const std::string stringValue = allValues[name];
    T argValue = convertString<T>(stringValue);
    return argValue;
}

template <typename T2>
std::vector<T2> getVectorArg(const std::string &name)
{
    const std::string stringValue = allValues[name];
    std::vector<std::string> stringSplit = splitString(stringValue);
    std::vector<T2> outVector;
    for (std::string s : stringSplit)
    {
        T2 item = convertString<T2>(s);
        outVector.push_back(item);
    }
    return outVector;
}
    bool getFlag(const std::string& name);
    
    ArgParser(){
        addKW("help", "", "h", "display this help message and exit");
    };
    std::vector<std::string> getMultiArgs();

};