
#ifndef _Monomer_Type_H_
#define _Monomer_Type_H_

namespace std {

  enum MonomerTypeTable {

    UnknownType=0,

    Particle,

    SphericShell,

    TTableTerminus,

    NumberTypes=TTableTerminus-1

  };

}

#endif

