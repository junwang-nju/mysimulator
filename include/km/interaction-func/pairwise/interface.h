
#ifndef _Interaction_Func_Pairwise_Interface_H_
#define _Interaction_Func_Pairwise_Interface_H_

#include "interaction-func/interface.h"

namespace mysimulator {

  template <typename T,typename GeomType>
  class InteractionFuncPairwise : public InteractionFunc<T,GeomType> {

    public:

      typedef InteractionFuncPairwise<T,GeomType> Type;
      typedef InteractionFunc<T,GeomType>   ParentType;

      virtual
      void EMethod(const ArrayNumeric<ArrayNumeric<T> >& X,
                   const Array<unsigned int>& ID,const Array<Unique64Bit>& P,
                   const GeomType& Geo,T& Energy) {
        if(this->_update) {
          if(this->_neighbor.IsValid())   GetPre4E();
          else {
          }
        }
      }

    protected:

      virtual void GetPre4E() {
      }
      virtual
      void EFunc(const ArrayNumeric<T>&,const Array<Unique64Bit>&,T*)=0;

    private:

      InteractionFuncPairwise(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

}

#endif

