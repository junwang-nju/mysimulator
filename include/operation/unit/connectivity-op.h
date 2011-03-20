
#ifndef _Unit_Connectivity_Operation_H_
#define _Unit_Connectivity_Operation_H_

#include "data/unit/connectivity.h"

namespace std {

  bool IsHaveConnectivity(const Vector<unsigned int>& id) {
    return get(ConnectedID,id)==NULL;
  }

  bool IsHaveConnectivity(const unsigned int* id) {
    static Vector<unsigned int> rid;
    refer(rid,id,2);
    return IsHaveConnectivity(rid);
  }

  bool IsHaveConnectivity(const unsigned int id1, const unsigned int id2) {
    static Vector<unsigned int> id(2);
    id[0]=id1;
    id[1]=id2;
    return IsHaveConnectivity(id);
  }

}

#endif

