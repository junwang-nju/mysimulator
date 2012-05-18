
#ifndef _Minimizer_Interface_H_
#define _Minimizer_Interface_H_

#include "minimizer/method-name.h"
#include "minimizer/line/method-name.h"
#include "minimizer/line/condition/method-name.h"
#include "system/interface.h"

namespace mysimulator {

  template <MinimizerMethodName MMN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,LineMinimizerConditionMethodName LMC>
  struct Minimizer {

    public:

      typedef Minimizer<MMN,LMN,T,IDT,PT,GT,BT,CT,LMC>  Type;

      Minimizer() { fprintf(stderr,"Minimizer Not Available!\n"); }
      ~Minimizer() { Clear(*this); }

      bool IsValid() const { return false; }

      void Load(System<T,IDT,PT,GT,BT,CT>&) {
        fprintf(stderr,"Not Implemented!\n");
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <MinimizerMethodName MMN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,LineMinimizerConditionMethodName LMC>
  void Clear(Minimizer<MMN,LMN,T,IDT,PT,GT,BT,CT,LMC>& M) {}

}

#include "minimizer/steep/interface.h"

#endif

