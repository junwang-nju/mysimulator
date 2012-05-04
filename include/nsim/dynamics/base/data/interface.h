
#ifndef _Dynamics_Base_Data_Interface_H_
#define _Dynamics_Base_Data_Interface_H_

#include "system/propagator/interface.h"

#define NAME(W,M,U)   W##M##U
#define PTR(W,U)      W##Ptr##U
#define MOD(W,U)      W##Mod##U
#define SRC(W,U)      W##Src##U

#define PARAM(U)  SP.Param[U]
#define VALUE(T,U)  Value<T>(PARAM(U))
#define POINTER(T,U)  Pointer<T>(PARAM(U))

#define _LINKElement(W,U,OBJ) POINTER(T,PTR(W,U))=&OBJ;
#define _LINKArray(W,U,OBJ) \
  if(!IsSameStructure(OBJ,X)) Imprint(OBJ,X); \
  POINTER(Array2D<T>,SRC(W,U))=&OBJ;
#define _LINK(W) \
  _LINKElement(W,TimeStep,TimeStep) \
  MassMethodName u=VALUE(unsigned int,MOD(W,Mass)); \
  if(u==ArrayMass) { _LINKArray(W,Mass,AMass) } \
  else if(u==UniqueMass) _LINKElement(W,Mass,UMass) \
  else fprintf(stderr,"Unknowm Mass Method!\n");

namespace mysimulator {

  template <typename T>
  struct DynamicsBaseData {

    public:

      typedef DynamicsBaseData<T>   Type;

      T TimeStep;
      T RunPeriod;
      T StartTime;
      unsigned int NumSteps;
      T NowTime;

      T UMass;
      Array2D<T> AMass;

      DynamicsBaseData() : TimeStep(0), RunPeriod(0), StartTime(0),
                           NumSteps(0), NowTime(0), UMass(0), AMass() {}
      ~DynamicsBaseData() { Clear(*this); }

      bool IsValid() const { return TimeStep>0; }

      void UpdateNumSteps() {
        NumSteps=static_cast<unsigned int>(RunPeriod/TimeStep+0.5);
        UpdateRunPeriod();
      }
      void UpdateRunPeriod() { RunPeriod=NumSteps*TimeStep; }
      void UpdateNowTime(const T& delta) { NowTime+=delta; }
      void UpdateNowTime(unsigned int n) { UpdateNowTime(n*TimeStep); }

      template <template<typename> class CT>
      void _Link(SystemPropagator<T,CT>& SP, const Array2D<T>& X) {
        assert(SP.IsValid()&&X.IsValid());
        switch(SP.Method) {
          case SystemConstEVelVerlet:
            _LINK(VelVerletConstE)
            break;
          default:
            fprintf(stderr,"Propagator Method DO NOT fit Dynamics!\n");
        }
      }

    private:

      DynamicsBaseData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(DynamicsBaseData<T>& D) {
    Clear(D.AMass); D.UMass=0; D.NowTime=0; D.NumSteps=0; D.StartTime=0;
    D.RunPeriod=0;  D.TimeStep=0;
  }

}

#endif

