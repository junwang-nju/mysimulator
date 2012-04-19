
#ifndef _System_Content_Data_EG_Interface_H_
#define _System_Content_Data_EG_Interface_H_

#include "array/2d/release.h"

namespace mysimulator {

  template <typename T>
  struct SystemContentDataEG {

    public:

      typedef SystemContentDataEG<TType;

      T*        Energy;
      T**       Gradient;
      bool      isRefer;

      SystemContentDataEG() : Energy(NULL), Gradient(NULL), isRefer(false) {}
      ~SystemContentDataEG() { clearData(); }

      void clearData() {
        if(isRefer) Energy=NULL;  else release(Energy);
        release(Gradient);
        isRefer=false;
      }
      bool isvalid() const { return (Energy!=NULL)&&(Gradient!=NULL); }

    private:

      SystemContentDataEG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentDataEG<T>& D) { D.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentDataEG<T>& D) { return D.isvalid(); }

}

#endif

