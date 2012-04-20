
#ifndef _System_Content_Data_G_Interface_H_
#define _System_Content_Data_G_Interface_H_

#include <cstdlib>

namespace mysimulator {

  template <typename DataType>
  struct SystemContentDataG {

    public:

      typedef SystemContentDataG<DataType>  Type;

      DataType Gradient;

      SystemContentDataG() : Gradient(NULL) {}
      ~SystemContentDataG() { clearData(); }

      void clearData() { release(Gradient); }
      bool isvalid() const { return Gradient!=NULL; }

    private:

      SystemContentDataG(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename DT>
  void release(SystemContentDataG<DT>& D) { D.clearData(); }

  template <typename DT>
  bool IsValid(const SystemContentDataG<DT>& D) { return D.isvalid(); }

}

#endif

