
#include <string>


#ifndef ASSEMBER
#define ASSEMBER



class assember
{
public:
    assember(std::string &filePath);
    ~assember();

private:
    void Run();
    int getHash(std::string &raw);
    std::string binTohex(std::string &bin);
    std::string hexTobin(std::string &hex, int len);

    std::string srcFilePath;
    std::string targetFilePath;
};








#endif