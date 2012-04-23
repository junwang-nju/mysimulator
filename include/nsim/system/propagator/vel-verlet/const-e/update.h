
#ifndef _System_Propagator_VelVerlet_ConstE_Update_H_
#define _System_Propagator_VelVerlet_ConstE_Update_H_

#include "system/propagator/interface.h"
#include "system/propagator/vel-verlet/const-e/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void _UpdateVelVerletConstEHTIM(SystemPropagator<T,CT>& P) {
    fprintf(stderr,"Improper Content Type!\n");
  }

  template <typename T,template<typename> class CT>
  void _UpdateVelVerletConstEVelositySQ(SystemPropagator<T,CT>& P) {
    fprintf(stderr,"Improper Content Type!\n");
  }

  template <typename T,template<typename> class CT>
  void _UpdateVelVerletConstEKEnergySimple(SystemPropagator<T,CT>& P) {
    fprintf(stderr,"Improper Content Type!\n");
  }

}

#include "system/content/with-egv/interface.h"

#if !(defined(VALUE)||defined(FUNC)||defined(PTR)||defined(SRC))
#define PTR(U)    VelVerletConstE##Ptr##U
#define SRC(U)    VelVerletConstE##Src##U
#define FUNC(U)   VelVerletConstE##Func##U
#define VALUE(U)  VelVerletConstE##Val##U
#else
#error "Duplicate Definition for PTR,FUNC,VALUE"
#endif

#if !(defined(PARAM)||defined(SVALUE)||defined(VVALUE))
#define PARAM(U)  P.Param[U]
#define SVALUE(U) (*Pointer<T>(PARAM(SRC(U))))
#define VVALUE(U) Value<T>(PARAM(VALUE(U)))
#else
#error "Duplicate Definition for PARAM,SVALUE,VVALUE"
#endif

#include "unique/64bit/io.h"

namespace mysimulator {

  template <typename T>
  void _UpdateVelVerletConstEHTIM(SystemPropagator<T,SystemContentWithEGV>& P) {
    typedef void (*UpFunc)(const T&,const Unique64Bit&,Unique64Bit&);
    UpFunc F=reinterpret_cast<UpFunc>(PARAM(FUNC(UpdateHTIM)).ptr);
    F(SVALUE(TimeStep),PARAM(PTR(Mass)),PARAM(PTR(NegHTIM)));
  }

  template <typename T>
  void _UpdateVelVerletConstEVelositySQ(
      SystemPropagator<T,SystemContentWithEGV>& P) {
    typedef void (*Func)(Unique64Bit&,const Array1D<SystemContentWithEGV<T> >&);
    Func F=reinterpret_cast<Func>(PARAM(FUNC(UpdateVSQ)).ptr);
    F(PARAM(PTR(VelocitySQ)),P.GrpContent);
  }

  template <typename T>
  void _UpdateVelVerletConstEKEnergySimple(
      SystemPropagator<T,SystemContentWithEGV>& P) {
    typedef void (*UpFunc)(T&,const Unique64Bit&,const Unique64Bit&);
    UpFunc F=reinterpret_cast<UpFunc>(PARAM(FUNC(UpdateKESimple)).ptr);
    F(VVALUE(KineticEnergy),PARAM(PTR(Mass)),PARAM(PTR(VelocitySQ)));
  }

}

#if defined(PARAM)||defined(SVALUE)||defined(VVALUE)
#undef VVALUE
#undef SVALUE
#undef PARAM
#endif

#if defined(VALUE)||defined(FUNC)||defined(PTR)||defined(SRC)
#undef VALUE
#undef FUNC
#undef SRC
#undef PTR
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void UpdateVelVerletConstEHTIM(SystemPropagator<T,CT>& P) {
    _UpdateVelVerletConstEHTIM(P);
  }

  template <typename T,template<typename> class CT>
  void UpdateVelVerletConstEVelositySQ(SystemPropagator<T,CT>& P) {
    _UpdateVelVerletConstEVelositySQ(P);
  }

  template <typename T,template<typename> class CT>
  void UpdateVelVerletConstEKEnergySimple(SystemPropagator<T,CT>& P) {
    _UpdateVelVerletConstEKEnergySimple(P);
  }

  template <typename T,template<typename> class CT>
  void UpdateVelVerletConstEKEnergy(SystemPropagator<T,CT>& P) {
    UpdateVelVerletConstEVelositySQ(P);
    UpdateVelVerletConstEKEnergySimple(P);
  }

}

#endif

