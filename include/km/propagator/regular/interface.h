
#ifndef _Propagator_Regular_Interface_H_
#define _Propagator_Regular_Interface_H_

#include "propagator/interface.h"

namespace mysimulator {

  template <typename T,typename GT,
            typename GRNG=BoxMuller<MersenneTwisterStandard> >
  class PropagatorRegular : public Propagator<T,GT,GRNG> {

    public:

      typedef PropagatorRegular<T,GT,GRNG>    Type;
      typedef Propagator<T,GT,GRNG>   ParentType;

      PropagatorRegular() : ParentType() {}
      virtual ~PropagatorRegular() { Clear(*this); }

      virtual void Evolute(System<T,GT>& S) {
        for(unsigned int i=0;i<1;++i) // Max not defined!!!!
          this->_bind[0]->Evolute(S.Location(),S.Gradient(),
                                  S.InteractionGroup(0),this->_props[0]);
      }

    private:

      PropagatorRegular(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename GT,typename GRNG>
  void Clear(PropagatorRegular<T,GT,GRNG>& P) {
    typedef typename PropagatorRegular<T,GT,GRNG>::ParentType PType;
    Clear(static_cast<PType&>(P));
  }

}

#endif

