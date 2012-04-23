
#ifndef _Dynamics_Algorithm_VelVerlet_Data_Interface_H_
#define _Dynamics_Algorithm_VelVerlet_Data_Interface_H_

#include "system/interface.h"

#ifndef PARAM
#define PARAM(U) SP.Param[U]
#else
#error "Duplicate Definition for Macro PARAM"
#endif

#ifndef _LINK
#define _LINK(W) \
  MassMethodName u=PARAM(W##Mod##Mass).u; \
  if(u==ArrayMass) { \
    if(!IsSameStructure(ANegHTIM,X)) ImprintStructure(ANegHTIM,X); \
    Pointer<Array2D<T> >(PARAM(W##Src##NegHTIM))=&ANegHTIM; \
  } else if(u==UniqueMass) Pointer<T>(PARAM(W##Src##NegHTIM))=&UNegHTIM; \
  else fprintf(stderr,"Unknown Mass Methods!\n");
#else
#error "Duplicate Definition for Macro _LINK"
#endif

namespace mysimulator {

  template <typename T>
  struct DynamicsVelVerletData {

    public:

      typedef DynamicsVelVerletData<T>    Type;

      T           UNegHTIM;
      Array2D<T>  ANegHTIM;

      DynamicsVelVerletData() : UNegHTIM(0), ANegHTIM() {}
      ~DynamicsVelVerletData() { Clear(*this); }

      bool IsValid() const { return true; }

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

      DynamicsVelVerletData(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(DynamicsVelVerletData<T>& D) { D.UNegHTIM=0; Clear(D.ANegHTIM); }

}

#ifdef _LINK
#undef _LINK
#endif

#ifdef PARAM
#undef PARAM
#endif

#endif

