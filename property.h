
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

      varVector<double> Mask;

      varVector<double> Mass;

      varVector<double> internalCoordinate;

      varVector<double> internalVelocity;

      varVector<double> internalGradient;

      varVector<double> ivMass;

      Property()
        : MonomerType(UnknownType), MonomerKindID(UnknownKind), Index(-1),
          Info(), Coordinate(), Velocity(), Gradient(), Mask(), Mass(),
          internalCoordinate(), internalVelocity(), internalGradient(),
          ivMass() {
      }

      Property& operator=(const Property& P) {
        MonomerType=P.MonomerType;
        MonomerKindID=P.MonomerKindID;
        Info=P.Info;
        Coordinate=P.Coordinate;
        Velocity=P.Velocity;
        Gradient=P.Gradient;
        Mask=P.Mask;
        Mass=P.Mass;
        internalCoordinate=P.internalCoordinate;
        internalVelocity=P.internalVelocity;
        internalGradient=P.internalGradient;
        ivMass=P.ivMass;
        return *this;
      }

  };

}

#endif

