
#include "data-pack.h"

namespace std {

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  void DataPack<T,DVType,SVType,IVType>::clear() {
    Data.clear();
    Struct.clear();
    Info.clear();
  }

}

