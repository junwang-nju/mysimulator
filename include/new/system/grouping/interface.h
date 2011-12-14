
#ifndef _System_Grouping_Interface_H_
#define _System_Grouping_Interface_H_

#include "system/grouping/method-name.h"
#include "system/interaction/interface.h"
#include "array/1d/interface.h"
#include "unique/64bit/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysGrouping {

    public:

      typedef SysGrouping<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;
      typedef 
      void (*EvFunc)(SysContentType<T,VecType>&,
                     const SysInteraction<IDType,ParamType,GeomType,T>&,
                     Array1DContent<SysContentType<T,VecType> >&,
                     const Array1DContent<Unique64Bit>&);

      SystemGroupingMethodName  Method;
      Array1D<Unique64Bit> MerIDRange;
      Array1D<Unique64Bit> Param;
      EvFunc evfunc;

      SysGrouping()
        : Method(SystemUnassigned), MerIDRange(), Param(), evfunc(NULL) {}
      ~SysGrouping() { clearData(); }

      void clearData() {
        evfunc=NULL;  release(Param);   release(MerIDRange);
        Method=SystemUnassigned;
      }
      bool isvalid() const {
        return IsValid(evfunc)&&IsValid(MerIDRange)&&(Method!=SystemUnassigned);
      }

    private:

      SysGrouping(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SC>
  void release(SysGrouping<T,IDT,PT,GT,VT,SC>& G) { G.clearData(); }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SC>
  bool IsValid(const SysGrouping<T,IDT,PT,GT,VT,SC>& G) { return G.isvalid(); }

}

#endif

