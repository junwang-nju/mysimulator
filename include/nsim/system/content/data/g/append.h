
#ifndef _System_Content_Data_G_Append_H_
#define _System_Content_Data_G_Append_H_

#include "system/content/data/g/interface.h"
#include "array/2d/shift.h"

namespace mysimulator {

  template <typename T>
  void AppendEnergy(SystemContentDataG<T>&,const SystemContentDataG<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void AppendGradient(SystemContentDataG<T>& D,const SystemContentDataG<T>& iD){
    assert(D.IsValid()&&iD.IsValid());
    BlasShift(D.Gradient,iD.Gradient);
  }

  template <typename T>
  void AppendBoth(SystemContentDataG<T>&,const SystemContentDataG<T>&) {
    fprintf(stderr,"Not Avaliable!\n");
  }

  template <typename T>
  void Append(SystemContentDataG<T>& D,const SystemContentDataG<T>& iD) {
    AppendGradient(D,iD);
  }

}

#endif

