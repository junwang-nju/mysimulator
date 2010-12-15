
#ifndef _Propagator_Run_H_
#define _Propagator_Run_H_

#include "data/name/propagator-base.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <template<typename,template<typename>class,typename> class IType,
            typename IdType, typename T, template<typename> class DBuffer,
            typename GeomType>
  void Run(IType<T,DBuffer,GeomType>& F,
           Vector<T>* X, Vector<T>* V, Vector<T>* G, const Vector<T>* dMsk,
           const IdType& idx,
           Vector<UniqueParameter>& PGP, Vector<UniqueParameter>* MP,
           const unsigned int& nu, ostream& os) {
    unsigned int no=PGP[CountOutput].u;
    unsigned int ns=PGP[CountStepsInOutput].u;
    double ot=ns*PGP[DeltaTime].value<T>();
    copy(PGP[NowTime],PGP[StartTime].value<T>());
    typedef void (*MvFunc)(
        IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,Vector<T>*,
        const Vector<T>*,const IdType&,Vector<UniqueParameter>&,
        Vector<UniqueParameter>*,const unsigned int&);
    typedef void (*OtFunc)(
        IType<T,DBuffer,GeomType>&,Vector<T>*,Vector<T>*,Vector<T>*,
        const Vector<T>*,const IdType&,Vector<UniqueParameter>&,
        Vector<UniqueParameter>*,const unsigned int&,ostream&);
    reinterpret_cast<OtFunc>(PGP[OutputFunc].ptr)(F,X,V,G,dMsk,idx,
                                                  PGP,MP,nu,os);
    for(unsigned int i=0;i<no;++i) {
      for(unsigned int j=0;j<ns;++j)
        reinterpret_cast<MvFunc>(PGP[StepMove].ptr)(F,X,V,G,dMsk,idx,PGP,MP,nu);
      PGP[NowTime].value<T>()+=ot;
      reinterpret_cast<OtFunc>(PGP[OutputFunc].ptr)(F,X,V,G,dMsk,idx,PGP,MP,
                                                    nu,os);
    }
  }


}

#endif

