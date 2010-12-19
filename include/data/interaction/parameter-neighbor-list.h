
#ifndef _Parameter_Neighbor_List_H_
#define _Parameter_Neighbor_List_H_

#include "data/interaction/parameter-unit.h"
#include "data/basic/property-list.h"

namespace std {

  template <template <typename> class ParameterShapeType, typename T>
  struct ParameterWNeighborList
      : public ParameterShapeType<InteractionParameterUnit> {
    Vector<UniqueParameter> property;
    ParameterShapeType<InteractionParameterUnit> possibleParameter;
    ParameterShapeType<unsigned int> ParameterID;
    PropertyList<T> XBackup;

    typedef ParameterWNeighborList<ParameterShapeType,T>  Type;
    typedef ParameterShapeType<InteractionParameterUnit>  ParentType;

    ParameterWNeighborList()
      : ParentType(), property(), possibleParameter(), XBackup() {}
    ParameterWNeighborList(const Type& P) {
      myError("Cannot create Parameter with Neighbor-List");
    }
    Type& operator=(const Type& P) {
      myError("Cannot copy Parameter with Neighbor-List");
      return *this;
    }
    ~ParameterWNeighborList() { release(*this); }

    T& Cutoff() { return property[0].value<T>(); }
    const T& Cutoff() const { return property[0].value<T>(); }
    T& BufferDistance() { return property[1].value<T>(); }
    const T& BufferDistance() const { return property[1].value<T>(); }
    T& ListRadiusSQ() { return property[2].value<T>(); }
    const T& ListRadiusSQ() const { return property[2].value<T>(); }
  };

  template <template <typename> class ParameterShapeType, typename T>
  bool IsAvailable(const ParameterWNeighborList<ParameterShapeType,T>& P) {
    typedef ParameterShapeType<InteractionParameterUnit>  Parent;
    return IsAvailable(static_cast<const Parent&>(P))&&
           IsAvailable(P.property)&&IsAvailable(P.possibleParameter)&&
           IsAvailable(P.XBackup);
  }

  template <template <typename> class ParameterShapeType, typename T>
  void release(ParameterWNeighborList<ParameterShapeType,T>& P) {
    release(P.property);
    release(P.possibleParameter);
    release(P.XBackup);
    typedef ParameterShapeType<InteractionParameterUnit>  Parent;
    release(static_cast<Parent&>(P));
  }

  template <template <typename> class ParameterShapeType, typename T>
  void copy(ParameterWNeighborList<ParameterShapeType,T>& P,
            const ParameterWNeighborList<ParameterShapeType,T>& cP) {
    assert(IsAvailable(P));
    assert(IsAvailable(cP));
    copy(P.possibleParameter,cP.possibleParameter);
    copy(P.property,cP.property);
    copy(P.XBackup,cP.XBackup);
  }

  template <template <typename> class ParameterShapeType, typename T>
  void refer(ParameterWNeighborList<ParameterShapeType,T>& P,
             const ParameterWNeighborList<ParameterShapeType,T>& rP) {
    assert(IsAvailable(rP));
    release(P);
    refer(P.possibleParameter,rP.possibleParameter);
    refer(P.property,rP.property);
    refer(P.XBackup,rP.XBackup);
    typedef ParameterShapeType<InteractionParameterUnit>  Parent;
    refer(static_cast<Parent&>(P),static_cast<const Parent&>(rP));
  }

}

#endif

