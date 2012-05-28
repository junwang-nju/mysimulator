
#ifndef _Step_Propagator_H_
#define _Step_Propagator_H_

#include "array2d-numeric/interface.h"
#include "array2d/interface.h"
#include "unique/64bit/interface.h"
#include "step-propagator/name.h"

namespace mysimulator {

  template <typename T>
  class StepPropagator {

    public:

      typedef StepPropagator<T>   Type;
      template <typename T1> friend void Clear(StepPropagator<T1>&);

      StepPropagator() : _tag(UnassignedStepPropagator), _range(), _param(),
                         _X(), _G(), _V() {}
      virtual ~StepPropagator() { Clear(*this); }

      bool IsValid() const {
        return (_tag!=UnassignedStepPropagator)&&_range.IsValid()&&
               _param.IsValid()&&_X.IsValid();
      }

      virtual bool IsDynamics() const   = 0;
      virtual bool IsMinimizer() const  = 0;
      virtual void Allocate()           = 0;
      virtual void Init()               = 0;
      virtual void Clean()              = 0;
      virtual void Update()             = 0;
      virtual void Update1()            = 0;
      virtual void Update2()            = 0;
      virtual void Update3()            = 0;
      virtual void Update4()            = 0;
      virtual void Update5()            = 0;
      virtual void Update6()            = 0;
      virtual void Update7()            = 0;
      virtual void Evolute1()           = 0;
      virtual void Evolute2()           = 0;
      virtual void Evolute3()           = 0;
      virtual void Evolute4()           = 0;
      virtual void Load(Array<Unique64Bit>&) = 0;
      virtual const T KineticEnergy() const = 0;

      void AllocateRange(unsigned int n) { _range.Allocate(n,2); }

      const StepPropagatorName Name() const { return _tag; }
      Array<unsigned int>& Range(unsigned int n) {
        assert(_range.IsValid());
        return _range[n];
      }
      const Array<unsigned int>& Range(unsigned int n) const {
        assert(_range.IsValid());
        return _range[n];
      }
      Unique64Bit& Parameter(unsigned int n) { return _param[n]; }
      const Unique64Bit& Parameter(unsigned int n) const { return _param[n]; }

      void IntroduceX(Array2DNumeric<T>& X) { _Introduce(_X,X); }
      void IntroduceG(Array2DNumeric<T>& G) { _Introduce(_G,G); }
      void IntroduceV(Array2DNumeric<T>& V) { _Introduce(_V,V); }
      void Detach() { Clear(_X);  Clear(_G);  Clear(_V); }

    protected:

      StepPropagatorName        _tag;
      Array2D<unsigned int>     _range;
      Array<Unique64Bit>        _param;
      Array<Array2DNumeric<T> > _X;
      Array<Array2DNumeric<T> > _G;
      Array<Array2DNumeric<T> > _V;

      template <template<typename> class AType>
      void _Introduce(Array<AType<T> >& A,AType<T>& IA) {
        assert(_range.IsValid());
        assert(IA.IsValid());
        Clear(A);
        A.Allocate(_range.Size());
        for(unsigned int i=0;i<_range.Size();++i)
          A[i].Refer(IA,_range[i][0],_range[i][1]);
      }

    private:

      StepPropagator(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(StepPropagator<T>& P) {
    Clear(P._V);
    Clear(P._G);
    Clear(P._X);
    Clear(P._param);
    Clear(P._range);
    P._tag=UnassignedStepPropagator;
  }

}

#include "step-propagator/generic/fix-position/interface.h"
#include "step-propagator/dynamics/vel-verlet/const-e/unique-mass/interface.h"
#include "step-propagator/dynamics/vel-verlet/const-e/array-mass/interface.h"
#include "step-propagator/dynamics/vel-verlet/langevin/unique-mass/unique-friction/interface.h"
#include "step-propagator/dynamics/vel-verlet/langevin/unique-mass/array-friction/interface.h"
#include "step-propagator/dynamics/vel-verlet/langevin/array-mass/unique-friction/interface.h"
#include "step-propagator/dynamics/vel-verlet/langevin/array-mass/array-friction/interface.h"
#include "step-propagator/dynamics/vel-verlet/berendsen/unique-mass/interface.h"
#include "step-propagator/dynamics/vel-verlet/berendsen/array-mass/interface.h"
#include "step-propagator/minimizer-shift/line/interface.h"
#include "step-propagator/property-name.h"

namespace mysimulator {

  template <typename T>
  void Introduce(StepPropagator<T>*& P, StepPropagatorName SPN,...) {
    if(P!=NULL) { delete P; P=NULL; }
    MassPropertyName  MassFlag;
    FrictionPropertyName  FricFlag;
    va_list vl;
    va_start(vl,SPN);
    switch(SPN) {
      case VelVerletConstE:
        MassFlag=static_cast<MassPropertyName>(va_arg(vl,unsigned int));
        if(MassFlag==UniqueMass)
          P=new StepPropagatorVelVerletConstE_UMass<T>;
        else if(MassFlag==ArrayMass)
          P=new StepPropagatorVelVerletConstE_AMass<T>;
        break;
      case VelVerletLangevin:
        MassFlag=static_cast<MassPropertyName>(va_arg(vl,unsigned int));
        FricFlag=UnknownFrictionProperty;
        FricFlag=static_cast<FrictionPropertyName>(va_arg(vl,unsigned int));
        if(MassFlag==UniqueMass) {
          if(FricFlag==UniqueFriction)
            P=new StepPropagatorVelVerletLangevin_UMassUFric<T>;
          else if(FricFlag==ArrayFriction)
            P=new StepPropagatorVelVerletLangevin_UMassAFric<T>;
        } else if(MassFlag==ArrayMass) {
          if(FricFlag==UniqueFriction)
            P=new StepPropagatorVelVerletLangevin_AMassUFric<T>;
          else if(FricFlag==ArrayFriction)
            P=new StepPropagatorVelVerletLangevin_AMassAFric<T>;
        }
        break;
      case VelVerletBerendsen:
        MassFlag=static_cast<MassPropertyName>(va_arg(vl,unsigned int));
        if(MassFlag==UniqueMass)
          P=new StepPropagatorVelVerletBerendsen_UMass<T>;
        else if(MassFlag==ArrayMass)
          P=new StepPropagatorVelVerletBerendsen_AMass<T>;
        break;
      case FixPosition:
        P=new StepPropagatorFixPosition<T>;
        break;
      case MinimizerLine:
        P=new StepPropagatorMinimizerShiftLine<T>;
        break;
      default:
        fprintf(stderr,"Unknown StepPropagator Name!\n");
    }
    if(P==NULL) { fprintf(stderr,"Improper Property Name!\n"); return; }
    P->Allocate();
    va_end(vl);
  }

}

#endif

