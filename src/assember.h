
#include <string>


#ifndef ASSEMBER
#define ASSEMBER


class assember
{
public:
    assember(std::string &filePath);
    ~assember();

    void Run();

private:
    std::string srcFilePath;
    std::string targetFilePath;
};








#endif