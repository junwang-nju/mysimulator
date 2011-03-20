
#ifndef _Unit_Connectivity_Operation_H_
#define _Unit_Connectivity_Operation_H_

#include "data/unit/connectivity.h"

namespace std {

  bool IsHaveConnectivity(const Vector<unsigned int>& id) {
    return get(ConnectedID,id)!=NULL;
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

  bool IsHaveConnectivity(const char* name1, const char* name2) {
    static Vector<unsigned int> id(2);
    const unsigned int* pid1=getCompositionID(name1);
    if(pid1==NULL)  { Warn("Unknown Composition Name"); return false; }
    id[0]=*pid1;
    const unsigned int* pid2=getCompositionID(name2);
    if(pid2==NULL)  { Warn("Unknown Composition Name"); }
    id[1]=*pid2;
    return IsHaveConnectivity(id);
  }

}

#endif

