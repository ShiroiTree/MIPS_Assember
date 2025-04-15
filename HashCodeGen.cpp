
#include <string>
#include <iostream>

int getHash(std::string &raw)
{
    int len = raw.length();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        res = (res * 233 + raw[i]) % (100000007);
    }
    return res;
}

int main()
{
    while (1)
    {
        std::string raw;
        std::cin >> raw;
        std::cout << getHash(raw) << std::endl;
    }
}