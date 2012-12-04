
#ifndef _System_Interaction_Function_Angle_Neighbor_Name_H_
#define _System_Interaction_Function_Angle_Neighbor_Name_H_

namespace mysimulator {

  class AngleNeighborName {

    public:

      static const unsigned int EdgeA           = 0;
      static const unsigned int EdgeB           = EdgeA+1;
      static const unsigned int NumberNeighbor  = EdgeB+1;

  };

  const unsigned int AngleNeighborName::EdgeA;
  const unsigned int AngleNeighborName::EdgeB;
  const unsigned int AngleNeighborName::NumberNeighbor;

}

#endif

