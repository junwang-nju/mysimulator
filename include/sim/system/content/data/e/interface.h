
#ifndef _System_Content_Data_E_Interface_H_
#define _System_Content_Data_E_Interface_H_

#include <cstdlib>

namespace mysimulator {

  template <typename T>
  struct SystemContentDataE {

    public:

      typedef SystemContentDataE<T>   Type;

      T* Energy;
      bool isRefer;

      SystemContentDataE() : Energy(NULL), isRefer(false); {}
      ~SystemContentDataE() { clearData(); }

      void clearData() {
        if(isRefer) Energy=NULL; else release(Energy);
        isRefer=false;
      }
      bool isvalid() const { return Energy!=NULL; }

    private:

      SystemContentDataE(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void release(SystemContentDataE<T>& D) { D.clearData(); }

  template <typename T>
  bool IsValid(const SystemContentDataE<T>& D) { return D.isvalid(); }

}

#endif

