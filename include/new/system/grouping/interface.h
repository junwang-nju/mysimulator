
#ifndef _System_Grouping_Interface_H_
#define _System_Grouping_Interface_H_

#include "system/grouping/method-name.h"
#include "system/interaction/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysGrouping {

    public:

      typedef SysGrouping<T,IDType,ParamType,GeomType,VecType,SysContentType>
              Type;
      typedef 
      void (*FuncType)(SysContentType<T,VecType>&,
                       SysInteraction<IDType,ParamType,GeomType,T>&,
                       Type&);

      SystemGroupingMethodName  Method;
      Array1D<Unique64Bit> MerIDRange;
      Array1D<SysContentType<T,VecType> > grpContent;
      Array1D<Unique64Bit> Param;
      Array1D<FuncType> evfunc;
      FuncType inifunc;
      Array1D<FuncType> updfunc;

      SysGrouping()
        : Method(SystemUnassigned), MerIDRange(), grpContent(),
          Param(), evfunc(), inifunc(NULL), updfunc() {}
      ~SysGrouping() { clearData(); }

      void clearData() {
        release(updfunc); inifunc=NULL;   release(evfunc);  release(Param);
        release(grpContent);  release(MerIDRange);  Method=SystemUnassigned;
      }
      bool isvalid() const {
        return IsValid(evfunc)&&IsValid(inifunc)&&
               IsValid(MerIDRange)&&IsValid(grpContent)&&
               (Method!=SystemUnassigned)&&
               (IsValid(Param)||(Method==SystemFixPosition));
      }

      void buildGrpContent(SysContentType<T,VecType>& SC) {
        for(unsigned int i=0;i<grpContent.size;++i)
          refer(grpContent[i],SC,MerIDRange[i].u[0],MerIDRange[i].u[1]);
      }

      void init(SysContentType<T,VecType>& SC,
                SysInteraction<IDType,ParamType,GeomType,T>& SI) {
        inifunc(SC,SI,*this);
      }
      void evolute(const unsigned int& method_id,
                   SysContentType<T,VecType>& SC,
                   SysInteraction<IDType,ParamType,GeomType,T>& SI) {
        evfunc[method_id](SC,SI,*this);
      }
      void update(const unsigned int& method_id,
                  SysContentType<T,VecType>& SC,
                  SysInteraction<IDType,ParamType,GeomType,T>& SI) {
        updfunc[method_id](SC,SI,*this);
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

