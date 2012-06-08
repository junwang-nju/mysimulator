
#ifndef _Interaction_Parameter_LJ1012Cut_Interface_H_
#define _Interaction_Parameter_LJ1012Cut_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/lj1012cut/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterLJ1012Cut : public InteractionParameter<T> {

    public:

      typedef InteractionParameterLJ1012Cut<T>    Type;
      typedef InteractionParameter<T>   ParentType;

      InteractionParameterLJ1012Cut() : ParentType() {}
      virtual ~InteractionParameterLJ1012Cut() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=LJ1012Cut;
        this->_data.Allocate(LJ1012CutNumberParameter);
      }
      virtual void Build() {
        assert(this->_data.Size()>=LJ1012CutNumberParameter);
        T R02=Value<T>(this->_data[LJ1012CutEqRadius]);
        T RC2=Value<T>(this->_data[LJ1012CutCutR]);
        T R0RC=R02/RC2;
        R02*=R02;
        RC2*=RC2;
        Value<T>(this->_data[LJ1012CutCutRSQ])=RC2;
        T R0RC2=R02/RC2;
        T R0RC10=R0RC2*R0RC2;
        R0RC10*=R0RC10;
        R0RC10*=R0RC2;
        T R0RC12=R0RC10*R0RC2;
        T Sigma2=R02*(R0RC10*R0RC-1)/(R0RC12*R0RC-1);
        T SGRC2=Sigma2/RC2;
        T SGRC10=SGRC2*SGRC2;
        SGRC10*=SGRC10;
        SGRC10*=SGRC2;
        T SGRC12=SGRC10*SGRC2;
        T VC=5*(SGRC12-SGRC10)-SGRC10;
        T KC=60*(SGRC10-SGRC12)/Value<T>(this->_data[LJ1012CutCutR]);
        T SGR010=SGRC10/R0RC10;
        T SGR012=SGRC12/R0RC12;
        T E=5*(SGR012-SGR010)-SGR010;
        E-=VC;
        E-=KC*(Value<T>(this->_data[LJ1012CutEqRadius])-
               Value<T>(this->_data[LJ1012CutCutR]));
        E=-Value<T>(this->_data[LJ1012CutEqEnergyDepth])/E;
        T Sigma10=Sigma2*Sigma2;
        Sigma10*=Sigma10;
        Sigma10*=Sigma2;
        Sigma10*=E;
        T A=Sigma10*Sigma2*5;
        T B=Sigma10*6;
        Value<T>(this->_data[LJ1012CutFactorA])=A;
        Value<T>(this->_data[LJ1012CutFactorB])=B;
        Value<T>(this->_data[LJ1012CutDiffFactorA])=A*12;
        Value<T>(this->_data[LJ1012CutDiffFactorB])=B*10;
        Value<T>(this->_data[LJ1012CutVc])=VC*E;
        Value<T>(this->_data[LJ1012CutKc])=KC*E;
      }

    private:

      InteractionParameterLJ1012Cut(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterLJ1012Cut<T>& P) {
    typedef typename InteractionParameterLJ1012Cut<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterLJ1012Cut<T>& P,
             const InteractionParameterLJ1012Cut<T>& BP) {
    typedef typename InteractionParameterLJ1012Cut<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

