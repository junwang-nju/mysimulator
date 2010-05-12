
#ifndef _Spheric_Shell_H_
#define _Spheric_Shell_H_

#include  "property-frame.h"

namespace std {

  /*
  Property& allocate_as_SphericShell(Property& Prop, uint Dim, uint Flag=0U) {
    Prop.MonomerType=SphericShell;
    Prop.Info.allocate(1);
    Prop.Info[0]=Dim;
    uint runDim=Dim+1;
    Prop.Coordinate.allocate(runDim);
    Prop.Mask.allocate(runDim);
    Prop.dMask.allocate(runDim);
    if(Flag&SphericShell_VelocityEnable)  Prop.Velocity.allocate(runDim);
    if(Flag&SphericShell_GradientEnable)  Prop.Gradient.allocate(runDim);
    if(Flag&SphericShell_MassEnable)  {
      Prop.Mass.allocate(2);
      Prop.ivMass.allocate(2);
    }
  }
  */

}

#endif

