
#ifndef _Interaction_Parameter_Interface_H_
#define _Interaction_Parameter_Interface_H_

#include "array/interface.h"
#include "unique/64bit/interface.h"
#include "interaction-func/name.h"

namespace mysimulator {

  template <typename T>
  class InteractionParameter {

    public:

      typedef InteractionParameter<T>   Type;
      template <typename T1> friend void Clear(InteractionParameter<T1>&);

      InteractionParameter() : _tag(UnknownInteractionFunc), _data() {}
      ~InteractionParameter() { Clear(*this); }

      bool IsValid() const { return _data.IsValid(); }
      Unique64Bit& operator[](unsigned int n) { return _data[n]; }
      const Unique64Bit& operator[](unsigned int n) const { return _data[n]; }

      void Copy(const InteractionParameter<T>& F) { _data.Copy(F._data); }

      virtual void Allocate()=0;
      virtual void Build()=0;

    protected:

      InteractionFuncName _tag;
      Array<Unique64Bit> _data;

    private:

      InteractionParameter(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T>
  void Clear(InteractionParameter<T>& P) { Clear(P._data); }

  template <typename T>
  void _Copy(InteractionParameter<T>& P,const InteractionParameter<T>& BP) {
    P.Copy(BP);
  }

}

#endif

