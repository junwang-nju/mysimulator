
#ifndef _Pair_Information_Item_Input_Output_H_
#define _Pair_Information_Item_Input_Output_H_

#include "data/derived/pair-information-item.h"
#include "data/basic/output-base.h"

namespace std {

  template <typename T>
  OutputBase& operator<<(OutputBase& os, const PairItem<T>& P) {
    os<<"[ "<<P()<<"\t("<<P.status<<" )]";
    return os;
  }

}

#endif

