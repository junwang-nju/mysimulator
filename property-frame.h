
#ifndef _Property_Frame_H_
#define _Property_Frame_H_

#include "ref-vector.h"
#include "var-vector.h"
#include "monomer-type.h"
#include "monomer-kind.h"

namespace std {

  enum PropertyFlag {
    VelocityEnable=1U,
    GradientEnable=2U,
    MassEnable=4U
  };
  
  enum PropertyFeatureList {
      property_info=0,
      property_coordinate,
      property_velocity,
      property_gradient,
      property_mask,
      property_dmask,
      property_mass,
      property_imass,
      property_icoordinate,
      property_ivelocity,
      property_igradient,
      NumberPropertyFeatures
  };

  enum PropertyInfoFeature {
    MonomerTypeID=0,
    MonomerKindID,
    MonomerIndex,
    MonomerDimension
  };

  class Property {
    public:
      refVector<uint>   Info;
      refVector<double> Coordinate;
      refVector<double> Velocity;
      refVector<double> Gradient;
      refVector<uint>   Mask;
      refVector<double> DMask;
      refVector<double> Mass;
      refVector<double> IMass;
      refVector<double> internalCoordinate;
      refVector<double> internalVelocity;
      refVector<double> internalGradient;
      
      Property() : Info(), Coordinate(), Velocity(), Gradient(), Mask(),
                   DMask(), Mass(), IMass(), internalCoordinate(),
                   internalVelocity(), internalGradient() {}
      
      Property(const Property& P) {
        myError("property frame copier is prohibited!");
      }

      Property& operator=(const Property& P) {
        myError("property copier is prohibited!");
        return *this;
      }

      void Activate() { Mask=1U; DMask=1.; }

      void DeActivate() { Mask=0U; DMask=0.; }

      void Activate(const uint& I) { Mask[I]=1U;  DMask[I]=1.; }

      void DeActivate(const uint& I) { Mask[I]=0U;  DMask[I]=0.; }

  };

}

#endif

