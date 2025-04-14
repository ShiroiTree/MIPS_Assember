
#include "assember.h"

#include <iostream>
#include <fstream>
#include <sstream>





assember::assember(std::string &filePath)
{
    this->srcFilePath = filePath;
    std::size_t lastpos = this->srcFilePath.rfind('.');
    char target[1024];
    this->srcFilePath.copy(target, lastpos);
    target[lastpos] = '\0';
    this->targetFilePath = target;
    this->targetFilePath += ".data";
    //std::cout << this->targetFilePath << std::endl;

    Run();
}

assember::~assember()
{

}

void assember::Run()
{
    std::ifstream source(this->srcFilePath);
    std::ofstream target(this->targetFilePath);
    std::string line;
    while (getline(source, line))
    {

    }
}

