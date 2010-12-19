
#ifndef _Propagtor_Berendsen_BelocityVerlet_Move_H_
#define _Propagtor_Berendsen_BelocityVerlet_Move_H_

#include "data/basic/unique-parameter.h"
#include "data/name/monomer-propagator-berendsen-vverlet.h"
#include "data/name/subsys-propagator-berendsen-vverlet.h"

namespace std {

  template <typename T>
  void BVMove_BeforeG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    T fac;
    fac=
      1+static_cast<UniqueParameter&>(SP[BV_HalfTimeStepIvRelaxT]).value<T>()*
       (static_cast<UniqueParameter&>(
            SP[BV_TemperatureDOFIvDKineticEnergy]).value<T>()-1.);
    static_cast<UniqueParameter&>(SP[BV_DualKineticEnergy]).value<T>()*=fac;
    copy(SP[BV_BScaleFactor],sqroot(fac));
    for(unsigned int i=0;i<SP.merPg.size;++i) {
      reinterpret_cast<mMoveFunc>(
          SP.merPg[i][BV_MovePreProcess].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
      reinterpret_cast<mMoveFunc>(
          SP.merPg[i][BV_MoveBeforeG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
    }
  }

  template <typename T>
  void BVMove_AfterG(subsysPropagator<T>& SP) {
    typedef
    void (*mMoveFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    for(unsigned int i=0;i<SP.merPg.size;++i) {
      scale(*reinterpret_cast<Vector<T>*>(
              SP.merPg[i][GVector].ptr),
            *reinterpret_cast<Vector<T>*>(
              SP.merPg[i][MskVector].ptr));
      reinterpret_cast<mMoveFunc>(
          SP.merPg[i][BV_MoveAfterG].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
    }
    T fac=0.;
    for(unsigned int i=0;i<SP.merPg.size;++i)
      fac+=static_cast<UniqueParameter&>(SP.merPg[i][MassData]).value<T>()*
           normSQ(*reinterpret_cast<Vector<T>*>(SP.merPg[i][VVector].ptr));
    copy(SP[BV_DualKineticEnergy],fac);
    copy(SP[BV_TemperatureDOFIvDKineticEnergy],
         static_cast<UniqueParameter&>(SP[BV_TemperatureDOF]).value<T>()/fac);
    fac=(1.+
         static_cast<UniqueParameter&>(
           SP[BV_TemperatureDOFIvDKineticEnergy]).value<T>()*
         static_cast<UniqueParameter&>(
           SP[BV_HalfTimeStepIvRelaxT]).value<T>())*
         static_cast<UniqueParameter&>(
           SP[BV_IvHalfTimeStepIvRelaxTPlusOne]).value<T>();
    static_cast<UniqueParameter&>(SP[BV_DualKineticEnergy]).value<T>()*=fac;
    copy(SP[BV_AScaleFactor],sqroot(fac));
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mMoveFunc>(
          SP.merPg[i][BV_MovePostProcess].ptr)(
          SP.merPg[i],static_cast<Vector<UniqueParameter>&>(SP));
  }

}

#endif

