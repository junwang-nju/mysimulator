
#ifndef _Property_H_
#define _Property_H_

#include "var-vector.h"
#include "monomer-type.h"
#include "monomer-kind.h"

namespace std {

  class Property {

    public:

      uint MonomerType;

      uint MonomerKindID;

      int Index;

      varVector<uint> Info;

      varVector<double> Coordinate;

      varVector<double> Velocity;

      varVector<double> Gradient;

      varVector<uint> Mask;

      varVector<double> dMask;

      varVector<double> Mass;

      varVector<varVector<double> > internalCoordinate;

      varVector<varVector<double> > internalVelocity;

      varVector<varVector<double> > internalGradient;

      varVector<double> ivMass;

      Property()
        : MonomerType(UnknownType), MonomerKindID(UnknownKind), Index(-1),
          Info(), Coordinate(), Velocity(), Gradient(), Mask(), dMask(), 
          Mass(), internalCoordinate(), internalVelocity(), internalGradient(),
          ivMass() {
      }

      void Activate() { Mask=1U; dMask=1.; }

      void Activate(const uint& idx) { Mask[idx]=1U; dMask[idx]=1.; }

      void DeAvtivate() { Mask=0U; dMask=0.; }

      void DeActivate(const uint& idx) { Mask[idx]=0U; dMask[idx]=0.; }

  };

}

#endif

