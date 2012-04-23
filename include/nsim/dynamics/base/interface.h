
#ifndef _Dynamics_Base_Interface_H_
#define _Dynamics_Base_Interface_H_

#include "system/interface.h"

#ifndef PARAM
#define PARAM(U)  SP.Param[U]
#else
#error "Duplicate Definition for Macro PARAM"
#endif

#ifndef _LINK
#define _LINK(W) {\
    Pointer<T>(PARAM(W##Src##TimeStep))=&TimeStep; \
    MassMethodName u=static_cast<MassMethodName>(PARAM(W##Mod##Mass).u); \
    if(u==ArrayMass) { \
      if(!IsSameStructure(AMass,X)) ImprintStructure(AMass,X); \
      Pointer<Array2D<T> >(PARAM(W##Src##Mass))=&AMass; \
    } else if(u==UniqueMass) Pointer<T>(PARAM(W##Src##Mass))=&UMass; \
    else fprintf(stderr,"Unknowm Mass Method!\n"); \
  }
#else
#error "Duplicate Definition for Macro _LINK"
#endif

namespace mysimulator {

  template <typename T>
  struct DynamicsBase {

    public:

      typedef DynamicsBase<T>   Type;

      T TimeStep;
      T RunPeriod;
      T StartTime;
      unsigned int NumSteps;
      T NowTime;
      T TimeBwOutput;
      unsigned int NumStepsBwOutput;
      bool IsFirstOutput;
      bool IsTerminated;

      T UMass;
      Array2D<T> AMass;

      bool BindFlag;
      Unique64Bit WriteFunc;
      Unique64Bit WriteParam;

      DynamicsBase()
        : TimeStep(0), RunPeriod(0), StartTime(0), NumSteps(0), NowTime(0),
          TimeBwOutput(0), NumStepsBwOutput(0), IsFirstOutput(false),
          IsTerminated(false),
          UMass(0), AMass(), BindFlag(false), WriteFunc(), WriteParam() {}
      ~DynamicsBase() { Clear(*this); }

      bool IsValid() const {
        return (TimeStep>0)&&(WriteFunc.ptr!=NULL)&&(NumStepsBwOutput>0);
      }

      void UpdateNumSteps() {
        NumSteps=static_cast<unsigned int>(RunPeriod/TimeStep+0.5);
        UpdateRunPeriod();
      }
      void UpdateRunPeriod() { RunPeriod=NumSteps*TimeStep; }
      void UpdateNowTime(const T& delta) { NowTime+=delta; }
      void UpdateNowTime(unsigned int n) { UpdateNowTime(n*TimeStep); }
      void UpdateNumStepsBwOutput() {
        NumStepsBwOutput=static_cast<unsigned int>(TimeBwOutput/TimeStep+0.5);
        UpdateTimeBwOutput();
      }
      void UpdateTimeBwOutput() { TimeBwOutput=NumStepsBwOutput*TimeStep; }

      template <template<typename> class CT,typename T1>
      void _Link(SystemPropagator<T,CT>& SP, const Array2D<T1>& X) {
        assert(SP.IsValid()&&X.IsValid());
        switch(SP.Method) {
          case SystemConstEVelVerlet:
            _LINK(VelVerletConstE)
            break;
          default:
            fprintf(stderr,"Propagator Method DO NOT fit Dynamics!\n");
        }
      }

      template <typename IDT,typename PT,typename GT,typename BT,
                template<typename> class CT>
      void Link(System<T,IDT,PT,GT,BT,CT>& S) {
        assert(S.IsValid());
        for(unsigned int i=0;i<S.Propagtors.Size();++i)
          _Link(S.Propagtors[i],S.Content.X);
      }

    private:

      DynamicsBase(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(DynamicsBase<T>& D) {
    assert(!D.BindFlag);
    Clear(D.AMass); D.UMass=0; D.IsTerminated=false; D.IsFirstOutput=false;
    D.NumStepsBwOutput=0; D.TimeBwOutput=0; D.NowTime=0; D.NumSteps=0;
    D.StartTime=0; D.RunPeriod=0;  D.TimeStep=0;
    Clear(D.WriteFunc); Clear(D.WriteParam);
  }

}

#ifdef _LINK
#undef _LINK
#endif

#ifdef PARAM
#undef PARAM
#endif

#endif

