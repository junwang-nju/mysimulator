
#ifndef _Propagator_Minimizer_Line_Condition_Interface_H_
#define _Propagator_Minimizer_Line_Condition_Interface_H_

#include "propagator-minimizer-line-condition/name.h"

namespace mysimulator {

  template <typename T>
  class LineMinimizerCondition {

    public:

      typedef LineMinimizerCondition<T> Type;
      template <typename T1> friend void Clear(LineMinimizerCondition<T1>&);

      LineMinimizerCondition() : _tag(UnknownCondition) {}
      virtual ~LineMinimizerCondition() { Clear(*this); }

      const LineMinimizerConditionName Name() const { return _tag; }
      virtual void Allocate() = 0;
      virtual bool Check(T,T,T,T,T,T) = 0;

    protected:

      LineMinimizerConditionName _tag;

    private:

      LineMinimizerCondition(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(LineMinimizerCondition<T>& C) {
    C._tag=UnknownCondition;
  }

}

#include "propagator-minimizer-line-condition/armijo/interface.h"
#include "propagator-minimizer-line-condition/wolfe/interface.h"
#include "propagator-minimizer-line-condition/strong-wolfe/interface.h"

namespace mysimulator {

  template <typename T>
  void Introduce(LineMinimizerCondition<T>*& C, LineMinimizerConditionName CN) {
    if(C!=NULL) { delete C; C=NULL; }
    switch(CN) {
      case Armijo: C=new LineMinimizerConditionArmijo<T>; break;
      case Wolfe:  C=new LineMinimizerConditionWolfe<T>;  break;
      case StrongWolfe: C=new LineMinimizerConditionStrongWolfe<T>; break;
      default:
        fprintf(stderr,"Unknown Condition for Line Minimizer!\n");
    }
    if(C!=NULL) C->Allocate();
  }

}

#endif

