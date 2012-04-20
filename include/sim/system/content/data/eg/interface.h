
#ifndef _System_Content_Data_EG_Interface_H_
#define _System_Content_Data_EG_Interface_H_

#include <cstdlib>

namespace mysimulator {

  template <typename T, typename DataType>
  struct SystemContentDataEG {

    public:

      typedef SystemContentDataEG<T,DataType>   Type;

      T         *Energy;
      DataType  Gradient;
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

  template <typename T, typename DT>
  void release(SystemContentDataEG<T,DT>& D) { D.clearData(); }

  template <typename T, typename DT>
  bool IsValid(const SystemContentDataEG<T,DT>& D) { return D.isvalid(); }

}

#endif

