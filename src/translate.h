
#include <map>

#ifndef TRS_H
#define TRS_H

#define ADD_Hash    5289433
#define ADDI_Hash   32437910
#define ADDU_Hash   32437922
#define ADDIU_Hash  -31901375
#define SUB_Hash    6270594
#define SLT_Hash    6268515
#define MUL_Hash    5944870
#define AND_Hash    5291763
#define ANDI_Hash   32980800
#define LUI_Hash    5890578
#define OR_Hash     25977
#define ORI_Hash    6052746
#define XOR_Hash    6540657
#define XORI_Hash   23973081
#define SLL_Hash    6268507
#define SLLV_Hash   60562151
#define SRA_Hash    6269894
#define SRAV_Hash   60885322
#define SRL_Hash    6269905
#define SRLV_Hash   60887885
#define BEQ_Hash    5343968
#define BNE_Hash    5346053
#define BGEZ_Hash   45250364
#define BGTZ_Hash   45253859
#define BLEZ_Hash   45521809
#define BLTZ_Hash   45525304
#define J_Hash      106
#define JAL_Hash    5777343
#define JR_Hash     24812
#define JALR_Hash   46120942
#define LB_Hash     25262
#define LW_Hash     25283
#define SB_Hash     26893
#define SW_Hash     26914

std::map<std::string, std::string> regRemaping = {
    {"$0" ,"00000"},{"$1" ,"00001"},{"$2" ,"00010"},{"$3" ,"00011"},
    {"$4" ,"00100"},{"$5" ,"00101"},{"$6" ,"00110"},{"$7" ,"00111"},
    {"$8" ,"01000"},{"$9" ,"01001"},{"$10","01010"},{"$11","01011"},
    {"$12","01100"},{"$13","01101"},{"$14","01110"},{"$15","01111"},
    {"$16","10000"},{"$17","10001"},{"$18","10010"},{"$19","10011"},
    {"$20","10100"},{"$21","10101"},{"$22","10110"},{"$23","10111"},
    {"$24","11000"},{"$25","11001"},{"$26","11010"},{"$27","11011"},
    {"$28","11100"},{"$29","11101"},{"$30","11110"},{"$31","11111"},

    {"$zero","00000"},{"$at","00001"},{"$v0","00010"},{"$v1","00011"},
    {"$a0"  ,"00100"},{"$a1","00101"},{"$a2","00110"},{"$a3","00111"},
    {"$t0"  ,"01000"},{"$t1","01001"},{"$t2","01010"},{"$t3","01011"},
    {"$t4"  ,"01100"},{"$t5","01101"},{"$t6","01110"},{"$t7","01111"},
    {"$s0"  ,"10000"},{"$s1","10001"},{"$s2","10010"},{"$s3","10011"},
    {"$s4"  ,"10100"},{"$s5","10101"},{"$s6","10110"},{"$s7","10111"},
    {"$t8"  ,"11000"},{"$t9","11001"},{"$k0","11010"},{"$k1","11011"},
    {"$gp"  ,"11100"},{"$sp","11101"},{"$fp","11110"},{"$ra","11111"}
};

#endif