
#ifndef _System_Content_Data_Null_Append_H_
#define _System_Content_Data_Null_Append_H_

#include "system/content/data/null/interface.h"

namespace mysimulator {

  template <typename T>
  void AppendEnergy(SystemContentDataNull<T>&,const SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void AppendGradient(SystemContentDataNull<T>&,
                      const SystemContentDataNull<T>&){
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void AppendBoth(SystemContentDataNull<T>&,const SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void Append(SystemContentDataNull<T>&,const SystemContentDataNull<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

}

#endif

