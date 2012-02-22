
#ifndef _PDB_Residue_Key_Library_H_
#define _PDB_Residue_Key_Library_H_

#include "pdb/atom/name.h"
#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int KeySize4Residue=(NumberAtomNames-1)/32+1;

  static const unsigned int KeyLibrarySize=42;

  static const unsigned int
  KeyLibrary4Residue[KeyLibrarySize][KeySize4Residue] = {
   { 0x2F,        0xE220,       0X0 },
   { 0x2F,        0x0,          0x0 },
   { 0x2100106F,  0x4220C22C,   0x6C00C },
   { 0x2100106F,  0xc,          0x0 },
   { 0x3006F,     0x8000C220,   0x1 },
   { 0x3006F,     0x0,          0x0 },
   { 0x6006F,     0xC220,       0x0 },
   { 0x6006F,     0x0,          0x0 },
   { 0x82F,       0x1C220,      0x0 },
   { 0xC00106F,   0x220C220,    0xC0 },
   { 0xC00106F,   0x0,          0x0 },
   { 0x1800106F,  0x220C220,    0x0 },
   { 0x1800106F,  0x0,          0x0 },
   { 0xF,         0xC20,        0x0 },
   { 0xF,         0x0,          0x0 },
   { 0x420C06F,   0x4400C220,   0x10 },
   { 0x21AF,      0x39D81120,   0x0 },
   { 0x21AF,      0x0,          0x0 },
   { 0x606F,      0xB801C220,   0x3 },
   { 0x606F,      0x0,          0x0 },
   { 0x10106F,    0x4220C221,   0x1D24 },
   { 0x10106F,    0x1,          0x0 },
   { 0x18006F,    0x220C220,    0x130 },
   { 0x18006F,    0x220C240,    0x130 },
   { 0x18006F,    0x0,          0x0 },
   { 0x18006F,    0x220C3C0,    0x130 },
   { 0x18006F,    0x220C200,    0x130 },
   { 0x2060606F,  0x4400C220,   0x230 },
   { 0x2060606F,  0x0,          0x0 },
   { 0x106F,      0x4220C200,   0x4 },
   { 0x106F,      0x0,          0x0 },
   { 0x22F,       0x1C220,      0x0 },
   { 0x22F,       0x0,          0x0 },
   { 0x52F,       0x1C21220,    0x0 },
   { 0x52F,       0x0,          0x0 },
   { 0xC2C0606F,  0x400C222,    0x11910 },
   { 0xC2C0606F,  0x2,          0x0 },
   { 0x2060606F,  0x4400C230,   0x2030 },
   { 0x2060606F,  0x10,         0x0 },
   { 0x1AF,       0x1DC1220,    0x0 },
   { 0x1AF,       0x0,          0x0 }
  };

  static const PDBResidueName
  Residue4Key[KeyLibrarySize] = {
    Ala,
    Ala,
    Arg,
    Arg,
    Asn,
    Asn,
    Asp,
    Asp,
    Cys,
    Gln,
    Gln,
    Glu,
    Glu,
    Gly,
    Gly,
    His,
    Ile,
    Ile,
    Leu,
    Leu,
    Lys,
    Lys,
    Met,
    Met,
    Met,
    Met,
    Met,
    Phe,
    Phe,
    Pro,
    Pro,
    Ser,
    Ser,
    Thr,
    Thr,
    Trp,
    Trp,
    Tyr,
    Tyr,
    Val,
    Val
  };

}

#endif

