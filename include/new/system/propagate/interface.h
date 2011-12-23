
#ifndef _System_Propagate_Interface_H_
#define _System_Propagate_Interface_H_

#include "system/propagate/method-name.h"
#include "array/1d/interface.h"
#include "unique/64bit/interface.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T, template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType>
  struct SysPropagate {

    public:

      typedef SysPropagate<T,VecType,SysContentType>    Type;
      typedef void (*MethodType)(Type&);

      SystemPropagateMethodName Method;
      Array1D<Unique64Bit>  MerIDRange;
      Array1D<SysContentType<T,VecType> > grpContent;
      Array1D<Unique64Bit>  Param;
      Array1D<MethodType>   evfunc;
      MethodType            initfunc;
      Array1D<MethodType>   updfunc;
      MethodType            clrfunc;

      SysPropagate()
        : Method(SysPropagateUnassigned),MerIDRange(),grpContent(),
          Param(), evfunc(), initfunc(NULL), updfunc(), clrfunc(NULL) {}
      ~SysPropagate() { clearData(); }

      void clearData() {
        if(clrfunc!=NULL)  clear();
        clrfunc=NULL;
        release(updfunc); initfunc=NULL; release(evfunc); release(Param);
        release(grpContent);  release(MerIDRange);
        Method=SysPropagateUnassigned;
      }
      bool isvalid() const {
        return IsValid(clrfunc)&&IsValid(evfunc)&&IsValid(initfunc)&&
               IsValid(grpContent)&&
               IsValid(MerIDRange)&&(Method!=SysPropagateUnassigned)&&
               (IsValid(Param)||(Method==SysFixPosition));
      }

      void buildGroupContent(SysContentType<T,VecType>& SC) {
        assert(IsValid(MerIDRange)&&IsValid(grpContent));
        assert(MerIDRange.size==grpContent.size);
        for(unsigned int i=0;i<MerIDRange.size;++i)
          refer(grpContent[i],SC,MerIDRange[i].u[0],MerIDRange[i].u[1]);
      }

      void init() { initfunc(*this); }
      void propagate(const unsigned int& move) { evfunc[move](*this); }
      void update(const unsigned int& update) { updfunc[update](*this); }
      void clear() { clrfunc(*this); }

    private:

      SysPropagate(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template<typename T,template<typename>class VT,
           template<typename,template<typename>class> class SCT>
  void release(SysPropagate<T,VT,SCT>& SE) { SE.clearData(); }

  template<typename T,template<typename>class VT,
           template<typename,template<typename>class> class SCT>
  bool IsValid(const SysPropagate<T,VT,SCT>& SE) { return SE.isvalid(); }

}

#endif

