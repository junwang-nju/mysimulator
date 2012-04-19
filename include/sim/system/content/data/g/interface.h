
#ifndef _System_Content_Data_G_Interface_H_
#define _System_Content_Data_G_Interface_H_

#include "array/2d/release.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentDataG {

    public:

      typedef SystemContentDataG<T>  Type;

      T** Gradient;

      SystemContentDataG() : Gradient(NULL) {}
      ~SystemContentDataG() { clearData(); }

      void clearData() { release(Gradient); }
      bool isvalid() const { return Gradient!=NULL; }

    private:

      SystemContentDataG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentDataG<T>& D) { D.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentDataG<T>& D) { return D.isvalid(); }

}

#endif

