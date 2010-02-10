
#ifndef _Fixed_Vector_H_
#define _Fixed_Vector_H_

#include "object-with-storage.h"
#include "vector-base.h"

namespace std {

  template <typename T, unsigned int ND>
  class fixVector : public ObjectWStorage<VectorBase<T> > {

    private:

      T runData[ND];

    public:

      typedef T DataType;

      typedef fixVector<T,ND>  Type;

      typedef ObjectWStorage<VectorBase<T> >  ParentType;

      fixVector() : ParentType() {
        this->data()=runData;
        this->SetSize(ND);
        this->SetHeadTail();
      }

      fixVector(const Type& V) {
        myError("Cannot create from fixed vector");
      }

      virtual ~fixVector() {}

      Type& operator=(const Type& V) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(V));
        return *this;
      }

      template <typename inputT>
      Type& operator=(const inputT& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      void clear() { myError("fix vector Cannot be cleared!"); }

      virtual const char* type() const { return "Fixed Vector"; }

  };

}

#endif

