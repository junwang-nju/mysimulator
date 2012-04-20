
#ifndef _System_Propagator_Interface_H_
#define _System_Propagator_Interface_H_

#include "system/propagator/method-name.h"
#include "unique/64bit/interface.h"
#include "array/1d/release.h"

namespace mysimulator {

  template <typename T,template<typename> class ContentType>
  struct SystemPropagator {

    public:

      typedef SystemPropagator<T,ContentType>  Type;
      typedef (*OperationFuncType)(Type&,ContentType<T>&);

      SystemPropagatorMethodName  Method;
      Unique64Bit*                MerIDRange;
      Unique64Bit*                Param;
      OperationFuncType*          EvFunc;
      OperationFuncType           InitFunc;
      OperationFuncType*          UpdFunc;
      OperationFuncType           ClrFunc;

      SystemPropagator()
        : Method(SystemPropagatorUnassigned),
          MerIDRange(NULL),Param(NULL),
          EvFunc(NULL),InitFunc(NULL),UpdFunc(NULL),ClrFunc(NULL) {}
      ~SystemPropagator() { clearData(); }

      void clearData() {
        if(ClrFunc!=NULL) clear();
        ClrFunc=NULL; release(UpdFunc); InitFunc=NULL; release(EvFunc);
        release(Param); release(MerIDRange);
        Method=SystemPropagatorUnassigned;
      }
      bool isvalid() const {
        return (ClrFunc!=NULL)&&(EvFunc!=NULL)&&(InitFunc!=NULL)&&
               (MerIDRange!=NULL)&&(Method!=SystemPropagatorUnassigned)&&
               ((Param!=NULL)||(Method==SystemFixPosition));
      }

      void init(ContentType<T>& C) { InitFunc(*this,C); }
      void propagate(ContentType<T>& C,unsigned int move) {
        EvFunc[move](*this,C);
      }
      void update(ContentType<T>& C, unsigned int update) {
        UpdFunc[update](*this,C);
      }
      void clear(ContentType<T>& C) { ClrFunc(*this,C); }

    private:

      SystemPropagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,template<typename> class CT>
  void release(SystemPropagator<T,CT>& P) { P.clearData(); }

  template <typename T,template<typename> class CT>
  bool IsValid(const SystemPropagator<T,CT>& P) { return P.isvalid(); }

}

#endif
