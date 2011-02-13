
#ifndef _Propagator_Operation_H_
#define _Propagator_Operation_H_

#include "data/propagator/propagator.h"
#include "operation/parameter/subsys-propagator-op.h"
#include "operation/propagate/vverlet-move.h"
#include "data/derived/dual-vector.h"

namespace std {

  template <typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType, typename T>
  void assignMove(Propagator<T>& P, const unsigned int& pgtype) {
    typedef void (*MoveFunc)(Propagator<T>&,IType<T,DBuffer,GeomType>&,
                             ParameterType&);
    switch(pgtype) {
      case VelocityVerlet:
        P[PgStep].ptr=
          reinterpret_cast<void*>(static_cast<MoveFunc>(VVerletStep));
        break;
      default:
        Error("unknown propagator type");
    }
  }

  unsigned int composeSubsysPropagatorType(const unsigned int& pgtype,
                                           const unsigned int& ensembletype) {
    if(pgtype==VelocityVerlet) {
      if(ensembletype==ConstantE)       return ConstantE_VelocityVerlet;
      else if(ensembletype==Berendsen)  return Berendsen_VelocityVerlet;
      else if(ensembletype==Langevin)   return Langevin_VelocityVerlet;
      else Error("unknown ensemble type");
    } else Error("unknown propagator type");
    return 0;
  }

  template <typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType, typename T>
  void allocate(Propagator<T>& P, const unsigned int& pgtype,
                const Vector<unsigned int>& ensembletype,
                const Vector<Vector<unsigned int> >& mertype) {
    assert(ensembletype.size==mertype.size);
    allocate(static_cast<Vector<UniqueParameter>&>(P),
             PropagatorParameterSize[pgtype]);
    assignMove<ParameterType,IType,DBuffer,GeomType,T>(P,pgtype);
    copy(P[MoveMode],pgtype);
    allocate(P.sysPg,ensembletype.size);
    for(unsigned int i=0;i<ensembletype.size;++i)
      allocate(P.sysPg[i],composeSubsysPropagatorType(pgtype,ensembletype[i]),
                          mertype[i]);
  }

  template <typename T>
  void mapData(Propagator<T>& P, const Vector<unsigned int>* id) {
    for(unsigned int i=0;i<P.sysPg.size;++i)
      for(unsigned int k=0;k<P.sysPg[i].merPg.size;++k) {
        P.sysPg[i].merPg[k][XVector].ptr=
          reinterpret_cast<void*>(&(P.X[id[i][k]]));
        P.sysPg[i].merPg[k][VVector].ptr=
          reinterpret_cast<void*>(&(P.V[id[i][k]]));
        P.sysPg[i].merPg[k][GVector].ptr=
          reinterpret_cast<void*>(&(P.G[id[i][k]]));
        P.sysPg[i].merPg[k][MskVector].ptr=
          reinterpret_cast<void*>(&(P.Msk[id[i][k]]));
      }
  }

  template <typename T>
  void mapData(Propagator<T>& P, const PropertyList<unsigned int>& id) {
    assert(P.sysPg.size<=id.nunit);
    mapData(P,id.structure);
  }

  template <typename T>
  void mapData(Propagator<T>& P, const DualVector<unsigned int>& id) {
    assert(P.sysPg.size<=id.size);
    mapData(P,id.data);
  }

  template <typename ParameterType,
            template <typename,template<typename>class,typename> class IType,
            template <typename> class DBuffer, typename GeomType, typename T>
  void assignOutput(Propagator<T>& P,
                    void (*OFunc)(Propagator<T>&,IType<T,DBuffer,GeomType>&,
                                  ParameterType&,ostream&)) {
    P[PgOutput].ptr=reinterpret_cast<void*>(OFunc);
  }

}

#endif

