
#ifndef _System_Propagator_ConstE_VelocityVerlet_Particle_Move_H_
#define _System_Propagator_ConstE_VelocityVerlet_Particle_Move_H_

#include "system/propagate/interface.h"
#include "system/propagate/constE-vverlet-particle/parameter-name.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _BfMoveCEVVerletParticle(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _AfMoveCEVVerletParticle(SysPropagate<T,VT,SCT>&) {
    Error("Improper Content Type!");
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletPartcleGlobalMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim) {
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,nhtim.value<T>(),G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _BfMoveFuncCEVVerletPartcleArrayMass(
      VT<T>& X, VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim) {
    assert(IsValid(X)&&IsValid(V)&&IsValid(G));
    shift(V,*reinterpret_cast<const VT<T>*>(nhtim.ptr[0]),G);
    shift(X,dt,V);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletPartcleGlobalMass(
      VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,nhtim.value<T>(),G);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveFuncCEVVerletPartcleArrayMass(
      VT<T>& V, VT<T>& G, const T& dt, const Unique64Bit& nhtim) {
    assert(IsValid(V)&&IsValid(G));
    shift(V,*reinterpret_cast<const VT<T>*>(nhtim.ptr[0]),G);
  }

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT>
  void _BfMoveCEVVerletParticle(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_RunMoveFunc)(VT<T>&,VT<T>&,VT<T>&,
                                 const T&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _RunMoveFunc mvFunc=
      reinterpret_cast<_RunMoveFunc>(P[CEVVerletParticleBfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvFunc(SE.grpContent[i].X(),SE.grpContent[i].Velocity(),
             SE.grpContent[i].EGData.Gradient(),
             P[CEVVerletParticleTimeStep].value<T>(),
             P[CEVVerletParticleNegHTimeIMass]);
  }

  template <typename T, template<typename> class VT>
  void _AfMoveCEVVerletParticle(SysPropagate<T,VT,SysContentWithEGV>& SE) {
    assert(IsValid(SE));
    typedef void (*_RunMoveFunc)(VT<T>&,VT<T>&,
                                 const T&,const Unique64Bit&);
    Unique64Bit* P=SE.Param.start;
    _RunMoveFunc mvFunc=
      reinterpret_cast<_RunMoveFunc>(P[CEVVerletParticleAfMoveFunc].ptr[0]);
    for(unsigned int i=0;i<SE.grpContent.size;++i)
      mvFunc(SE.grpContent[i].Velocity(),SE.grpContent[i].EGData.Gradient(),
             P[CEVVerletParticleTimeStep].value<T>(),
             P[CEVVerletParticleNegHTimeIMass]);
  }

}

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveCEVVerletParticleBeforeG(SysPropagate<T,VT,SCT>& SE) {
    _BfMoveCEVVerletParticle(SE);
  }

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void MoveCEVVerletParticleAfterG(SysPropagate<T,VT,SCT>& SE) {
    _AfMoveCEVVerletParticle(SE);
  }

}

#endif

