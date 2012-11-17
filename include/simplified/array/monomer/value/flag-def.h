
#ifndef _Array_Monomoer_Value_Flag_Def_H_
#define _Array_Monomoer_Value_Flag_Def_H_

namespace mysimulator {

  template <typename T>
  class __array_value { public: static const bool FLAG; };

  template <typename T>
  const bool __array_value<T>::FLAG =false;

}

#endif

