
#include <iostream>

#include "assember.h"




int main(int argc, char *argv[])
{
    std::string filepath = argv[1];
    assember *newFile = new assember(filepath);
    delete newFile;
    system("pause");
}