
#ifndef _Lattice_Enumerate_Check_Base_Load_Square2D_Specification_H_
#define _Lattice_Enumerate_Check_Base_Load_Square2D_Specification_H_

#include "lattice/enumerate/check/base/interface.h"
#include "array/2d/allocate.h"

namespace mysimulator {

  template <LatticeEnumCheckMethodName EN>
  void LatticeEnumCheckBase<SquareLattice,2U,LN>::load() {
    if(IsValid(SegMap)) return;
    allocate(SegMap,60);
    for(unsigned int i=0;i<10;++i)
    for(unsigned int j=0;j<6;++i)
      allocate(SegMap,((i!=0)&&(j==2)?2:1),2);
    // Length 1
    SegMap[0][0][0]=0;            SegMap[0][0][1]=1;
    SegMap[1][0][0]=0;            SegMap[1][0][1]=2;
    SegMap[2][0][0]=0;            SegMap[2][0][1]=1;
    SegMap[3][0][0]=1;            SegMap[3][0][1]=2;
    SegMap[4][0][0]=2;            SegMap[4][0][1]=3;
    SegMap[5][0][0]=3;            SegMap[5][0][1]=4;
    // Length 2
    SegMap[6][0][0]=0;            SegMap[6][0][1]=2;
    SegMap[7][0][0]=0;            SegMap[7][0][1]=5;
    SegMap[8][0][0]=0;            SegMap[8][0][1]=2;
    SegMap[8][1][0]=5;            SegMap[8][1][1]=6;
    SegMap[9][0][0]=2;            SegMap[9][0][1]=5;
    SegMap[10][0][0]=6;           SegMap[10][0][1]=9;
    SegMap[11][0][0]=9;           SegMap[11][0][1]=12;
    // Length 3
    SegMap[12][0][0]=0;           SegMap[12][0][1]=5;
    SegMap[13][0][0]=0;           SegMap[13][0][1]=14;
    SegMap[14][0][0]=0;           SegMap[14][0][1]=5;
    SegMap[14][1][0]=15;          SegMap[14][1][1]=18;
    SegMap[15][0][0]=5;           SegMap[15][0][1]=14;
    SegMap[16][0][0]=18;          SegMap[16][0][1]=27;
    SegMap[17][0][0]=27;          SegMap[17][0][1]=36;
    // Length 4
    SegMap[18][0][0]=0;           SegMap[18][0][1]=13;
    SegMap[19][0][0]=0;           SegMap[19][0][1]=38;
    SegMap[20][0][0]=0;           SegMap[20][0][1]=13;
    SegMap[20][1][0]=38;          SegMap[20][1][1]=50;
    SegMap[21][0][0]=13;          SegMap[21][0][1]=38;
    SegMap[22][0][0]=50;          SegMap[22][0][1]=75;
    SegMap[23][0][0]=75;          SegMap[23][0][1]=100;
    // Length 5
    SegMap[24][0][0]=0;           SegMap[24][0][1]=36;
    SegMap[25][0][0]=0;           SegMap[25][0][1]=107;
    SegMap[26][0][0]=0;           SegMap[26][0][1]=36;
    SegMap[26][1][0]=107;         SegMap[26][1][1]=142;
    SegMap[27][0][0]=36;          SegMap[27][0][1]=107;
    SegMap[28][0][0]=142;         SegMap[28][0][1]=213;
    SegMap[29][0][0]=213;         SegMap[29][0][1]=284;
    // Length 6
    SegMap[30][0][0]=0;           SegMap[30][0][1]=98;
    SegMap[31][0][0]=0;           SegMap[31][0][1]=293;
    SegMap[32][0][0]=0;           SegMap[32][0][1]=98;
    SegMap[33][1][0]=293;         SegMap[32][1][1]=390;
    SegMap[33][0][0]=98;          SegMap[33][0][1]=293;
    SegMap[34][0][0]=390;         SegMap[34][0][1]=585;
    SegMap[35][0][0]=585;         SegMap[35][0][1]=780;
    // Length 7
    SegMap[36][0][0]=0;           SegMap[36][0][1]=272;
    SegMap[37][0][0]=0;           SegMap[37][0][1]=815;
    SegMap[38][0][0]=0;           SegMap[38][0][1]=272;
    SegMap[38][1][0]=815;         SegMap[38][1][1]=1086;
    SegMap[39][0][0]=272;         SegMap[39][0][1]=815;
    SegMap[40][0][0]=1086;        SegMap[40][0][1]=1629;
    SegMap[41][0][0]=1629;        SegMap[41][0][1]=2172;
    // Length 8
    SegMap[42][0][0]=0;           SegMap[42][0][1]=740;
    SegMap[43][0][0]=0;           SegMap[43][0][1]=2219;
    SegMap[44][0][0]=0;           SegMap[44][0][1]=740;
    SegMap[44][1][0]=2219;        SegMap[44][1][1]=2958;
    SegMap[45][0][0]=740;         SegMap[45][0][1]=2219;
    SegMap[46][0][0]=2958;        SegMap[46][0][1]=4437;
    SegMap[47][0][0]=4437;        SegMap[47][0][1]=5916;
    // Length 9
    SegMap[48][0][0]=0;           SegMap[48][0][1]=2034;
    SegMap[49][0][0]=0;           SegMap[49][0][1]=6101;
    SegMap[50][0][0]=0;           SegMap[50][0][1]=2034;
    SegMap[50][1][0]=6101;        SegMap[50][1][1]=8134;
    SegMap[51][0][0]=2034;        SegMap[51][0][1]=6101;
    SegMap[52][0][0]=8134;        SegMap[52][0][1]=12201;
    SegMap[53][0][0]=12201;       SegMap[53][0][1]=16268;
    // Length 10
    SegMap[54][0][0]=0;           SegMap[54][0][1]=5513;
    SegMap[55][0][0]=0;           SegMap[55][0][1]=16538;
    SegMap[56][0][0]=0;           SegMap[56][0][1]=5513;
    SegMap[56][1][0]=16538;       SegMap[56][1][1]=22050;
    SegMap[57][0][0]=5513;        SegMap[57][0][1]=16538;
    SegMap[58][0][0]=22050;       SegMap[58][0][1]=33075;
    SegMap[59][0][0]=33075;       SegMap[59][0][1]=44100;
  }

}

#endif

