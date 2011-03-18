
#ifndef _Unit_Connectivity_H_
#define _Unit_Connectivity_H_

#include "data/unit/composition.h"

namespace std {

  Map<Vector<unsigned int>,char>  ConnectedID;

  void loadAminoAcidConnectivity(const char* ROOT=".") {
    if(!IsAvailable(ConnectedID)) allocate(ConnectedID);
    char *buff=new char[1024];
    strncpy(buff,ROOT,strlen(ROOT));
    strcpy(buff+strlen(ROOT),"/connect.amino-acid");
    FileInput FI;
    allocate(FI,buff);
    Vector<char> name;
    release(FI);
    delete[] buff;
  }

}

#endif

