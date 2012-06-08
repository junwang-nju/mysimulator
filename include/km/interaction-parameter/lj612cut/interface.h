
#ifndef _Interaction_Parameter_LJ612Cut_Interface_H_
#define _Interaction_Parameter_LJ612Cut_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj612cut/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterLJ612Cut : public InteractionParameter<T> {

    public:

      typedef InteractionParameterLJ612Cut<T>   Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterLJ612Cut() : ParentType() {}
      virtual ~InteractionParameterLJ612Cut() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=LJ612Cut;
        this->_data.Allocate(LJ612CutNumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=LJ612CutNumberParameter);
        T R0RC, R0RC6, R06, RC6, R0RC7;
        R06=Value<T>(this->_data[LJ612CutEqRadius]);
        RC6=Value<T>(this->_data[LJ612CutCutR]);
        assert(RC6>R06);
        R0RC=R06/RC6;
        R06*=R06*R06;   R06*=R06;
        RC6*=RC6;
        Value<T>(this->_data[LJ612CutCutRSQ])=RC6;
        RC6*=RC6*RC6;
        R0RC6=R06/RC6;
        R0RC7=R0RC6*R0RC;
        T Sigma6=R06*(1-R0RC7)/(1-R0RC6*R0RC7);
        T SGRC6=Sigma6/RC6;
        T SGRC12=SGRC6*SGRC6;
        T VC=SGRC12-SGRC6*2;
        T KC=(SGRC6-SGRC12)/Value<T>(this->_data[LJ612CutCutR])*12;
        T SGR06=Sigma6/R06;
        T E=SGR06*(SGR06-2.);
        E-=VC;
        E-=KC*(Value<T>(this->_data[LJ612CutEqRadius])-
               Value<T>(this->_data[LJ612CutCutR]));
        E=-Value<T>(this->_data[LJ612CutEqEnergyDepth])/E;
        T A=E*Sigma6;
        T B=A*2;
        A=A*Sigma6;
        Value<T>(this->_data[LJ612CutFactorA])=A;
        Value<T>(this->_data[LJ612CutFactorB])=B;
        Value<T>(this->_data[LJ612CutDiffFactorA])=A*12;
        Value<T>(this->_data[LJ612CutDiffFactorB])=B*6;
        Value<T>(this->_data[LJ612CutVc])=VC*E;
        Value<T>(this->_data[LJ612CutKc])=KC*E;
      }

    private:

      InteractionParameterLJ612Cut(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterLJ612Cut<T>& P) {
    typedef typename InteractionParameterLJ612Cut<T>::ParentType  PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterLJ612Cut<T>& P,
             const InteractionParameterLJ612Cut<T>& BP) {
    typedef typename InteractionParameterLJ612Cut<T>::ParentType  PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

