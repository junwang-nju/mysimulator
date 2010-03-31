
#ifndef _Property_List_H_
#define _Property_List_H_

#include "var-vector.h"
#include "ref-vector.h"

namespace std {

  template <typename T, template <typename> class VecType>
  class PropertyList : public VecType<T> {

    public:

      typedef PropertyList<T,VecType>   Type;

      typedef VecType<T>    ParentType;

      typedef refVector<T>  PropertyType;

    protected:

      VecType<PropertyType> Struct;

    public:

      PropertyList() : ParentType() { assert(VecType<T>::IsVector); }

      PropertyList(const VectorBase<unsigned int>& ShpSize) : ParentType() {
        allocate(ShpSize);
      }

      PropertyList(const Type&) {
        myError("Cannot create from Property List");
      }

      virtual ~PropertyList() { clear(); }

      void clear() {
        static_cast<ParentType*>(this)->clear();
        for(unsigned int i=0;i<Struct.size();++i)   Struct[i].clear();
        Struct.clear();
      }

      Type& operator=(const Type& PLB) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(PLB));
        return *this;
      }

      template <template <typename> class iVecType>
      Type& operator=(const PropertyList<T,iVecType>& PL) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(PL));
        return *this;
      }

      Type& operator=(const VectorBase<T>& V) {
        static_cast<ParentType*>(this)->operator=(V);
        return *this;
      }

      Type& operator=(const T& Value) {
        static_cast<ParentType*>(this)->operator=(Value);
        return *this;
      }

      const unsigned int size() const { return Struct.size(); }

      const unsigned int dataSize() const {
        return static_cast<const ParentType*>(this)->size();
      }

      const unsigned int numberUnits() const { return size(); }

      const VecType<PropertyType>& Structure() const { return Struct; }

      VecType<PropertyType>& Structure() { return Struct; }

      const PropertyType& operator[](const unsigned int I) const {
        return Struct[I];
      }

      PropertyType& operator[](const unsigned int I) { return Struct[I]; }

      const PropertyType* beginUnit() const { return Struct.begin(); }

      const PropertyType* endUnit() const { return Struct.end(); }

    protected:

      struct AllocateOp {
        template <template <typename> class iVecType>
        void operator()(const VectorBase<unsigned int>& ShapeSize,
                        PropertyList<T,iVecType>& PL) {
          myError("Not Available");
        }
        void operator()(const VectorBase<unsigned int>& ShapeSize,
                        PropertyList<T,varVector>& Self) {
          unsigned int n=ShapeSize.size();
          unsigned int ne=0;
          for(unsigned int i=0;i<n;++i) ne+=ShapeSize[i];
          static_cast<ParentType&>(Self).allocate(ne);
          Self.Structure().allocate(n);
          ne=0;
          for(unsigned int i=0;i<n;ne+=ShapeSize[i++])
            Self[i].refer(static_cast<ParentType&>(Self),ne,ShapeSize[i]);
        }
      };
      
      struct ReferOp {
        template <template <typename> class iVecType,
                  template <typename> class rVecType>
        void operator()(const PropertyList<T,iVecType>&,
                        PropertyList<T,rVecType>&) {
          myError("Not Available");
        }
        template <template <typename> class iVecType>
        void operator()(const PropertyList<T,iVecType>& PL,
                        PropertyList<T,refVector>& Self) {
          static_cast<refVector<T>&>(Self).refer(
              static_cast<const iVecType<T>&>(PL));
          Self.Structure().refer(PL.Structure());
        }
      };

      AllocateOp runAllocateOp;
      
      ReferOp runReferOp;

    public:

      void allocate(const VectorBase<unsigned int>& ShapeSize) {
        runAllocateOp(ShapeSize,*this);
      }

      template <template <typename> class iVecType>
      void refer(const PropertyList<T,iVecType>& PL) {
        runReferOp(PL,*this);
      }

      Type& CanonicalForm() { return *this; }

      const Type& CanonicalForm() const { return *this; }

      void swap(Type& pv) {
        static_cast<ParentType*>(this)->swap(static_cast<ParentType&>(pv));
        Structure().swap(pv.Structure());
      }

  };

}

#endif

