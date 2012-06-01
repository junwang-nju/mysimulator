
#ifndef _Interaction_Parameter_Dihedral_Periodic_Interface_H_
#define _Interaction_Parameter_Dihedral_Periodic_Interface_H_

#include "interaction-parameter/interface.h"
#include "interaction-parameter/dihedral-periodic/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameterDihedralPeriodic : public InteractionParameter<T> {

    public:

      typedef InteractionParameterDihedralPeriodic<T>   Type;
      typedef InteractionParameter<T> ParentType;

      InteractionParameterDihedralPeriodic() : ParentType() {}
      virtual ~InteractionParameterDihedralPeriodic() { Clear(*this); }

      virtual void Allocate() {
        this->_tag=DihedralPeriodic;
        assert(this->_data.IsValid());
        const unsigned int nu=
          Value<unsigned int>(this->_data[DihedralPeriodicNumberUnit]);
        const unsigned int n=
          DihedralPeriodicShift+nu*DihedralPeriodicUnitNumberParameter;
        Clear(this->_data);
        this->_data.Allocate(n);
        Value<unsigned int>(this->_data[DihedralPeriodicNumberUnit])=nu;
      }

      virtual void Build() {
        const unsigned int nu=
          Value<unsigned int>(this->_data[DihedralPeriodicNumberUnit]);
        unsigned int sf=DihedralPeriodicShift;
        for(unsigned int i=0;i<nu;++i) {
          Value<T>(this->_data[sf+DihedralPeriodicStrFreq])=
            Value<T>(this->_data[sf+DihedralPeriodicStrength])*
            Value<unsigned int>(this->_data[sf+DihedralPeriodicFrequency]);
          sf+=DihedralPeriodicUnitNumberParameter;
        }
      }

    private:

      InteractionParameterDihedralPeriodic(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameterDihedralPeriodic<T>& P) {
    typedef typename InteractionParameterDihedralPeriodic<T>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

  template <typename T>
  void _Copy(InteractionParameterDihedralPeriodic<T>& P,
             const InteractionParameterDihedralPeriodic<T>& BP) {
    typedef typename InteractionParameterDihedralPeriodic<T>::ParentType PType;
    _Copy(static_cast<PType&>(P),static_cast<const PType&>(BP));
  }

}

#endif

