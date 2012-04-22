
#ifndef _System_Propagator_Interface_H_
#define _System_Propagator_Interface_H_

#include "system/propagator/method-name.h"
#include "unique/64bit/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class ContentType>
  struct SystemPropagator {

    public:

      typedef SystemPropagator<T,ContentType>   Type;
      typedef void (*OperateFuncType)(Type&);
      typedef ContentType<T>    CType;

      SystemPropagatorMethodName  Method;
      Array1D<Unique64Bit>        IDRange;
      Array1D<CType>              GrpContent;
      Array1D<Unique64Bit>        Param;
      OperateFuncType             InitFunc;
      OperateFuncType             ClrFunc;
      Array1D<OperateFuncType>    EvFunc;
      Array1D<OperateFuncType>    UpdFunc;

      SystemPropagator() : Method(SystemPropagatorUnassigned), IDRange(),
                           GrpContent(), Param(), InitFunc(NULL), ClrFunc(NULL),
                           EvFunc(), UpdFunc() {}
      ~SystemPropagator() { Clear(); }

      void Clear() {
        if(ClrFunc!=NULL)   _Clear();
        ClrFunc=NULL; UpdFunc.Clear();  EvFunc.Clear(); InitFunc=NULL;
        Param.Clear(); IDRange.Clear(); GrpContent.Clear();
        Method=SystemPropagatorUnassigned;
      }
      bool IsValid() const {
        return (ClrFunc!=NULL)&&(InitFunc!=NULL)&&EvFunc.IsValid()&&
               UpdFunc.IsValid()&&IDRange.IsValid()&&GrpContent.IsValid()&&
               (Method!=SystemPropagatorUnassigned)&&
               (Param.IsValid()||(Method==SystemFixPosition));
      }

      void Allocate(SystemPropagatorMethodName PMN) {
      }

      void _Init() { InitFunc(*this); }
      void _Propagate(unsigned int n) { EvFunc[n](*this); }
      void _Update(unsigned int n) { UpdFunc[n](*this); }
      void _Clear() { ClrFunc(*this); }

      void _Build(CType& C) {
        assert(IDRange.IsValid());
        GrpContent.Clear();
        GrpContent.Allocate(IDRange.Size());
        for(unsigned int i=0;i<IDRange.Size();++i)
          GrpContent[i].Refer(C,IDRange[i].uv[0],IDRange[i].uv[1]);
      }

    private:

      SystemPropagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

