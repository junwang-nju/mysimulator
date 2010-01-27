
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

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  DVType<T>& DataPack<T,DVType,SVType,IVType>::data() { return Data; }

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  const DVType<T>& DataPack<T,DVType,SVType,IVType>::data() const {
    return Data;
  }

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  SVType<refVector<T> >& DataPack<T,DVType,SVType,IVType>::structure() {
    return Struct;
  }

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  const SVType<refVector<T> >& DataPack<T,DVType,SVType,IVType>::structure()
      const { return Struct; }

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  IVType<int>& DataPack<T,DVType,SVType,IVType>::info() { return Info; }

  template <typename T, template<typename> class DVType,
                        template<typename> class SVType,
                        template<typename> class IVType>
  const IVType<int>& DataPack<T,DVType,SVType,IVType>::info() const {
    return Info;
  }

}

