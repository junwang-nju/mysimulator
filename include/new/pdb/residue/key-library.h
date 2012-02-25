
#ifndef _PDB_Residue_Key_Library_H_
#define _PDB_Residue_Key_Library_H_

#include "pdb/atom/name.h"
#include "pdb/residue/name.h"

namespace mysimulator {

  static const unsigned int KeySize4Residue=(NumberAtomNames-1)/32+1;

  static const unsigned int KeyLibrarySize=51;

  static const unsigned int
  KeyLibrary4Residue[KeyLibrarySize][KeySize4Residue] = {
   { 0x2F,        0xE220,       0X0 },        // Ala
   { 0x2F,        0x0,          0x0 },        // Ala
   { 0x3F,        0xE220,       0X0 },        // ctAla
   { 0x3F,        0x0,          0x0 },        // ctAla
   { 0x2100106F,  0x4220C22C,   0x6C00C },    // Arg
   { 0x2100106F,  0xc,          0x0 },        // Arg
   { 0x3006F,     0x8000C220,   0x1 },        // Asn
   { 0x3006F,     0x0,          0x0 },        // Asn
   { 0x6006F,     0xC220,       0x0 },        // Asp
   { 0x6006F,     0x0,          0x0 },        // Asp
   { 0x82F,       0x1C220,      0x0 },        // Cys
   { 0xC00106F,   0x220C220,    0xC0 },       // Gln
   { 0xC00106F,   0x0,          0x0 },        // Gln
   { 0x1800106F,  0x220C220,    0x0 },        // Glu
   { 0x1800106F,  0x0,          0x0 },        // Glu
   { 0x1800107F,  0x220C220,    0x0 },        // ctGlu
   { 0x1800107F,  0x0,          0x0 },        // ctGlu
   { 0xF,         0xC20,        0x0 },        // Gly
   { 0xF,         0x0,          0x0 },        // Gly
   { 0x1F,        0x0,          0x0 },        // ctGly
   { 0x420C06F,   0x4400C220,   0x10 },       // His
   { 0x420C06F,   0x4000C220,   0x30 },       // His
   { 0x21AF,      0x39D81220,   0x0 },        // Ile
   { 0x21AF,      0x0,          0x0 },        // Ile
   { 0x606F,      0xB801C220,   0x3 },        // Leu
   { 0x606F,      0x0,          0x0 },        // Leu
   { 0x10106F,    0x4220C221,   0x1D24 },     // Lys
   { 0x10106F,    0x1,          0x0 },        // Lys
   { 0x10107F,    0x4220C221,   0x1D24 },     // ctLys
   { 0x10107F,    0x1,          0x0 },        // ctLys
   { 0x18006F,    0x220C220,    0x130 },      // Met
   { 0x18006F,    0x220C240,    0x130 },      // Met
   { 0x18006F,    0x0,          0x0 },        // Met
   { 0x18006F,    0x220C3C0,    0x130 },      // ntMet
   { 0x18006F,    0x220C200,    0x130 },      // ntMet
   { 0x2060606F,  0x4400C220,   0x230 },      // Phe
   { 0x2060606F,  0x0,          0x0 },        // Phe
   { 0x106F,      0x4220C200,   0x4 },        // Pro
   { 0x106F,      0x0,          0x0 },        // Pro
   { 0x22F,       0x1C220,      0x0 },        // Ser
   { 0x22F,       0x0,          0x0 },        // Ser
   { 0x52F,       0x1C21220,    0x0 },        // Thr
   { 0x52F,       0x0,          0x0 },        // Thr
   { 0xC2C0606F,  0x400C222,    0x11910 },    // Trp
   { 0xC2C0606F,  0x2,          0x0 },        // Trp
   { 0x2060606F,  0x4400C230,   0x2030 },     // Tyr
   { 0x2060606F,  0x10,         0x0 },        // Tyr
   { 0x1AF,       0x1DC1220,    0x0 },        // Val
   { 0x1AF,       0x0,          0x0 }         // Val
  };

  static const PDBResidueName
  Residue4Key[KeyLibrarySize] = {
    Ala,
    Ala,
    ctAla,
    ctAla,
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
    ctGlu,
    ctGlu,
    Gly,
    Gly,
    ctGly,
    His,
    His,
    Ile,
    Ile,
    Leu,
    Leu,
    Lys,
    Lys,
    ctLys,
    ctLys,
    Met,
    Met,
    Met,
    ntMet,
    ntMet,
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

