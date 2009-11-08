
#ifndef _Property_Operation_H_
#define _Property_Operation_H_

#include "particle.h"

namespace std {

  void copy_structure(Property& P, const Property& iP) {
    uint flag=0;
    if(iP.MonomerType==Particle) {
      if(iP.Velocity.data()!=NULL)  flag+=Particle_VelocityEnable;
      if(iP.Gradient.data()!=NULL)  flag+=Particle_GradientEnable;
      if(iP.Mass.data()!=NULL)      flag+=Particle_MassEnable;
      allocate_as_Particle(P,iP.Coordinate.size(),flag);
    } else myError("Unknown Monomer Type!");
  }

  void copy(Property& P, const Property& iP) {
    assert(P.MonomerType==iP.MonomerType);
    P.MonomerKindID=iP.MonomerKindID;
    P.Index=iP.Index;
    P.Info=iP.Info;
    P.Mask=iP.Mask;
    P.dMask=iP.dMask;
    P.Coordinate=iP.Coordinate;
    if(iP.MonomerType==Particle) {
      if(iP.Velocity.data()!=NULL)  P.Velocity=iP.Velocity;
      if(iP.Gradient.data()!=NULL)  P.Gradient=iP.Gradient;
      if(iP.Mass.data()!=NULL)  {
        P.Mass=iP.Mass;
        P.ivMass=iP.ivMass;
      }
    } else myError("Unknown Monomer Type!");
  }

  void copy_basic_structure(Property& P, const Property& iP) {
    if(iP.MonomerType==Particle)
      allocate_as_Particle(P,iP.Coordinate.size());
    else myError("Unknown Monomer Type!");
  }

  void copy_basic_data(Property& P, const Property& iP) {
    assert(P.MonomerType==iP.MonomerType);
    P.MonomerKindID=iP.MonomerKindID;
    P.Index=iP.Index;
    P.Info=iP.Info;
    P.Mask=iP.Mask;
    P.dMask=iP.dMask;
    P.Coordinate=iP.Coordinate;
    if(iP.MonomerType==Particle) {
    } else myError("Unknown Monomer Type!");
  }

  void copy_minimize_structure(Property& P, const Property& iP) {
    if(iP.MonomerType==Particle)
      allocate_as_Particle(P,iP.Coordinate.size(),Particle_GradientEnable);
    else myError("Unknown Monomer Type!");
  }

  void copy_minimize_data(Property& P, const Property& iP) {
    assert(P.MonomerType==iP.MonomerType);
    P.MonomerKindID=iP.MonomerKindID;
    P.Index=iP.Index;
    P.Info=iP.Info;
    P.Mask=iP.Mask;
    P.dMask=iP.dMask;
    P.Coordinate=iP.Coordinate;
    if(iP.MonomerType==Particle) {
      P.Gradient=iP.Gradient;
    } else myError("Unknown Monomer Type!");
  }

}

#endif

