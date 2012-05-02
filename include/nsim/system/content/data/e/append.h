
#ifndef _System_Content_Data_E_Append_H_
#define _System_Content_Data_E_Append_H_

#include "system/content/data/e/interface.h"

namespace mysimulator {

  template <typename T>
  void AppendEnergy(SystemContentDataE<T>& D, const SystemContentDataE<T>& iD) {
    assert(D.IsValid()&&iD.IsValid());
    D.Energy[0]+=iD.Energy[0];
  }

  template <typename T>
  void AppendGrdient(SystemContentDataE<T>&,const SystemContentDataE<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void AppendBoth(SystemContentDataE<T>&,const SystemContentDataE<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void Append(SystemContentDataE<T>& D,const SystemContentDataE<T>& iD) {
    AppendEnergy(D,iD);
  }

}

#endif

