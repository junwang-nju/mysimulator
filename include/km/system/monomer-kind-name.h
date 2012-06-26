
#ifndef _System_Monomer_Kind_Name_H_
#define _System_Monomer_Kind_Name_H_

namespace mysimulator {

  enum MonomerKindName {
    ParticleUnit = 0,
    WallUnit
  };

  static const unsigned int MonomerAltDimension[]={
    0,    // ParticleUnit
    1     // WallUnit
  };

}

#endif

