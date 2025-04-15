
#include "assember.h"
#include "translate.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <algorithm>
#include <iomanip>

assember::assember(std::string &filePath)
{
    this->srcFilePath = filePath;
    std::size_t lastpos = this->srcFilePath.rfind('.');
    char target[1024];
    this->srcFilePath.copy(target, lastpos);
    target[lastpos] = '\0';
    this->targetFilePath = target;
    this->targetFilePath += ".data";
    // std::cout << this->targetFilePath << std::endl;

    Run();
}

assember::~assember()
{
}

std::string assember::binTohex(std::string &bin)
{
    std::bitset<32> bits(bin);
    std::stringstream res;
    res << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << bits.to_ullong();
    return res.str();
}

std::string assember::hexTobin(std::string &hex, int len)
{
    std::string hexValue = hex.substr(2);
    if (hexValue.empty())
    {
        return "0";
    }
    unsigned long long decimal;
    std::stringstream ss;
    ss << std::hex << hexValue;
    ss >> decimal;
    if (decimal == 0)
    {
        return "0";
    }
    std::string binary;
    while (decimal > 0)
    {
        binary = (decimal % 2 == 0 ? "0" : "1") + binary;
        decimal /= 2;
    }
    if (binary.length() < len)
    {
        binary = std::string(len - binary.length(), '0') + binary;
    }
    else if (binary.length() > len)
    {
        binary = binary.substr(binary.length() - len);
    }
    return binary;
}

int assember::getHash(std::string &raw)
{
    int len = raw.length();
    int res = 0;
    for (int i = 0; i < len; i++)
    {
        res = (res * 233 + raw[i]) % (100000007);
    }
    return res;
}

void assember::Run()
{
    std::ifstream source(this->srcFilePath);
    std::ofstream target(this->targetFilePath);
    std::string line;
    std::stringstream output;

    int lineCount = 0;
    while (getline(source, line))
    {
        lineCount += 1;
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        unsigned int opPos = line.find(' ');
        unsigned int aPos, bPos;
        std::string op = line.substr(0, opPos);
        std::string rs, rt, rd, imm, sa;
        std::string binCode;
        std::string hexCode;
        switch (getHash(op))
        {
        case ADD_Hash: // #01
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100000";
            break;
        }
        case ADDI_Hash: // #02
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001000" + rs + rt + imm;
            break;
        }
        case ADDU_Hash: // #03
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100001";
            break;
        }
        case ADDIU_Hash: // #04
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001001" + rs + rt + imm;
            break;
        }
        case SUB_Hash: // #05
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100010";
            break;
        }
        case SLT_Hash: // #06
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "101010";
            break;
        }
        case MUL_Hash: // #07
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "011100" + rs + rt + rd + "00000" + "000010";
            break;
        }
        case AND_Hash: // #08
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100100";
            break;
        }
        case ANDI_Hash: // #09
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001100" + rs + rt + imm;
            break;
        }
        case LUI_Hash: // #10
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001111" + rs + rt + imm;
            break;
        }
        case OR_Hash: // #11
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100101";
            break;
        }
        case ORI_Hash: // #12
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001101" + rs + rt + imm;
            break;
        }
        case XOR_Hash: // #13
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "100110";
            break;
        }
        case XORI_Hash: // #14
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "001110" + rs + rt + imm;
            break;
        }
        case SLLV_Hash: // #15
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "000100";
            break;
        }
        case SLL_Hash: // #16
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rt = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            sa = line.substr(bPos + 1);
            sa = hexTobin(imm, 5);
            binCode = "00000000000" + rt + rd + sa + "000100";
            break;
        }
        case SRAV_Hash: // #17
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "000111";
            break;
        }
        case SRA_Hash: // #18
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rt = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            sa = line.substr(bPos + 1);
            sa = hexTobin(imm, 5);
            binCode = "00000000000" + rt + rd + sa + "000011";
            break;
        }
        case SRLV_Hash: // #19
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            rt = regRemaping[line.substr(bPos + 1)];
            binCode = "000000" + rs + rt + rd + "00000" + "000110";
            break;
        }
        case SRL_Hash: // #20
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rt = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            sa = line.substr(bPos + 1);
            sa = hexTobin(imm, 5);
            binCode = "00000000000" + rt + rd + sa + "000010";
            break;
        }
        case BEQ_Hash: // #21
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rt = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000100" + rs + rt + imm;
            break;
        }
        case BNE_Hash: // #22
        {
            aPos = line.find(',', opPos + 1);
            bPos = line.find(',', aPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rt = regRemaping[line.substr(aPos + 1, bPos - aPos - 1)];
            imm = line.substr(bPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000101" + rs + rt + imm;
            break;
        }
        case BGEZ_Hash: // #23
        {
            aPos = line.find(',', opPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000001" + rs + "00001" + imm;
            break;
        }
        case BGTZ_Hash: // #24
        {
            aPos = line.find(',', opPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000100" + rs + "00000" + imm;
            break;
        }
        case BLEZ_Hash: // #25
        {
            aPos = line.find(',', opPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000110" + rs + "00000" + imm;
            break;
        }
        case BLTZ_Hash: // #26
        {
            aPos = line.find(',', opPos + 1);
            rs = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1);
            imm = hexTobin(imm, 16);
            binCode = "000001" + rs + "00000" + imm;
            break;
        }
        case J_Hash: // #27
        {
            imm = line.substr(opPos + 1);
            imm = hexTobin(imm, 26);
            binCode = "000001" + imm;
            break;
        }
        case JAL_Hash: // #28
        {
            imm = line.substr(opPos + 1);
            imm = hexTobin(imm, 26);
            binCode = "000011" + imm;
            break;
        }
        case JR_Hash: // #29
        {
            rs = regRemaping[line.substr(opPos + 1)];
            binCode = "000000" + rs + "000000000000000001000";
            break;
        }
        case JALR_Hash: // 30
        {
            aPos = line.find(',', opPos + 1);
            rd = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            rs = regRemaping[line.substr(aPos + 1)];
            binCode = "000000" + rs + "00000" + rd + "00000001010";
            break;
        }
        case LB_Hash: // #31
        {
            int cPos;
            aPos = line.find(',', opPos + 1);
            bPos = line.find('(', aPos + 1);
            cPos = line.find(')', bPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1, bPos - aPos - 1);
            rs = regRemaping[line.substr(bPos + 1, cPos - bPos - 1)];
            imm = hexTobin(imm, 16);
            binCode = "100000" + rs + rt + imm;
            break;
        }
        case LW_Hash: // #32
        {
            int cPos;
            aPos = line.find(',', opPos + 1);
            bPos = line.find('(', aPos + 1);
            cPos = line.find(')', bPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1, bPos - aPos - 1);
            rs = regRemaping[line.substr(bPos + 1, cPos - bPos - 1)];
            imm = hexTobin(imm, 16);
            binCode = "100011" + rs + rt + imm;
            break;
        }
        case SB_Hash: // #33
        {
            int cPos;
            aPos = line.find(',', opPos + 1);
            bPos = line.find('(', aPos + 1);
            cPos = line.find(')', bPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1, bPos - aPos - 1);
            rs = regRemaping[line.substr(bPos + 1, cPos - bPos - 1)];
            imm = hexTobin(imm, 16);
            binCode = "101000" + rs + rt + imm;
            break;
        }
        case SW_Hash: // #34
        {
            int cPos;
            aPos = line.find(',', opPos + 1);
            bPos = line.find('(', aPos + 1);
            cPos = line.find(')', bPos + 1);
            rt = regRemaping[line.substr(opPos + 1, aPos - opPos - 1)];
            imm = line.substr(aPos + 1, bPos - aPos - 1);
            rs = regRemaping[line.substr(bPos + 1, cPos - bPos - 1)];
            imm = hexTobin(imm, 16);
            binCode = "101011" + rs + rt + imm;
            break;
        }
        default:
        {
            // error
            break;
        }
        }
        hexCode = binTohex(binCode);
        target << hexCode << '\n';

        binCode.clear();
        hexCode.clear();
    }
}
