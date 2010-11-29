
#ifndef _Interaction_Calculate_for_PropertyList_H_
#define _Interaction_Calculate_for_PropertyList_H_

#include "data/basic/property-list.h"

namespace std {

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<unsigned int>& idx,
      T& Energy) {
    CalcInteraction(F,X.structure,idx.data,Energy);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<unsigned int>& idx,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.data,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<unsigned int>& idx,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.data,Energy,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<unsigned int>& idx,
      T& Energy) {
    CalcInteraction(F,X.structure,idx.structure,Energy);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<unsigned int>& idx,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.structure,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<unsigned int>& idx,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.structure,Energy,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<PropertyList<unsigned int> >& idx,
      T& Energy) {
    CalcInteraction(F,X.structure,idx.data,Energy);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<PropertyList<unsigned int> >& idx,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.data,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const Vector<PropertyList<unsigned int> >& idx,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.data,Energy,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<Vector<unsigned int> >& idx,
      T& Energy) {
    CalcInteraction(F,X.structure,idx.structure,Energy);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<Vector<unsigned int> >& idx,
      PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.structure,Gradient.structure);
  }

  template <typename T,typename InteractionType>
  void CalcInteraction(
      InteractionType& F,
      const PropertyList<T>& X, const PropertyList<Vector<unsigned int> >& idx,
      T& Energy, PropertyList<T>& Gradient) {
    CalcInteraction(F,X.structure,idx.structure,Energy,Gradient.structure);
  }

}

#endif
