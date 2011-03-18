
#ifndef _Unit_Connectivity_H_
#define _Unit_Connectivity_H_

#include "data/unit/composition.h"

namespace std {

  Map<Vector<unsigned int>,char>  ConnectedID;
  Vector<Vector<unsigned int> > ConnectNeighborID;

  void loadAminoAcidConnectivity(const char* ROOT=".") {
    if(!IsAvailable(ConnectedID)) allocate(ConnectedID);
  }

}

#endif

