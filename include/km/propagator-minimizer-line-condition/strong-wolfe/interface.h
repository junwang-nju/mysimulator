
#ifndef _Propagator_Minimizer_Line_Condition_StrongWolfe_Interface_H_
#define _Propagator_Minimizer_Line_Condition_StrongWolfe_Interface_H_

#include "propagator-minimizer-line-condition/wolfe/interface.h"

namespace mysimulator {

  template <typename T>
  class LineMinimizerConditionStrongWolfe : LineMinimizerConditionWolfe<T> {

    public:

      typedef LineMinimizerConditionStrongWolfe<T>  Type;
      typedef LineMinimizerConditionWolfe<T>  ParentType;

      LineMinimizerConditionStrongWolfe() : ParentType() {}
      virtual ~LineMinimizerConditionStrongWolfe() { Clear(*this); }

      virtual void Allocate() { this->_tag=StrongWolfe; }
      virtual bool Check(T ry,T rp,T my,T dp,T cp,T step) {
        return ParentType::Check(ry,rp,my,dp,cp,step)&&(rp<=-cp);
      }

    private:

      LineMinimizerConditionStrongWolfe(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(LineMinimizerConditionStrongWolfe<T>& C) {
    typedef typename LineMinimizerConditionStrongWolfe<T>::ParentType   PType;
    Clear(static_cast<PType&>(C));
  }

}

#endif

