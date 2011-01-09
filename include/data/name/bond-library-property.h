
#ifndef _Bond_Library_Property_Name_H_
#define _Bond_Library_Property_Name_H_

namespace std {

  enum BondLibraryPropertyName {
    BondNumberPerByte=0,
    NeighborNumberPerSite,
    BondLibraryPropertyNumberParameter
  };

  enum Configure2DShiftName {
    HeadWithZero2D=0,
    HeadWithZeroOne2D,
    AllConfigures2D
  };

  enum Configure3DShiftName {
    HeadWithZero3D=0,
    HeadWithZeroOne3D,
    HeadWithZeroOneTwo3D,
    AllConfigures3D
  };

}

#endif

