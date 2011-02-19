
#ifndef _Interaction_Name_H_
#define _Interaction_Name_H_

#include "data/name/lj612.h"
#include "data/name/lj612cut.h"
#include "data/name/lj1012.h"
#include "data/name/lj1012cut.h"
#include "data/name/core12.h"
#include "data/name/corelj612.h"
#include "data/name/coulomb.h"
#include "data/name/harmonic.h"
#include "data/name/shifted-fene.h"
#include "data/name/quad-plus-harmonic.h"
#include "data/name/driving-constant.h"

#include "data/name/angle-harmonic.h"
#include "data/name/dihedral-periodic.h"

#include "data/name/core-expanded-lj612.h"
#include "data/name/core-expanded-corelj612.h"

#include "data/name/external-object-corelj612.h"
#include "data/name/external-object-lj612cut.h"
#include "data/name/external-object-harmonic.h"

namespace std {

  enum InteractionName {
    Harmonic=0,
    LJ612,
    LJ612Cut,
    LJ1012,
    LJ1012Cut,
    Core12,
    CoreLJ612,
    Coulomb,
    ShiftedFENE,
    QuadPlusHarmonic,
    AngleHarmonic,
    DihedralPeriodic,
    CoreExpandedLJ612,
    CoreExpandedCoreLJ612,
    CentroidCentroidHarmonic,
    ParticleCentroidHarmonic,
    PlaneWallCoreLJ612,
    PlaneWallLJ612Cut,
    SphericShellCoreLJ612,
    SphericShellLJ612Cut,
    AnchorPointHarmonic,
    DrivingConstantForce,
    NumberInteractions
  };

  static Vector<unsigned int> InteractionIdxSize;

  void InitInteractionIndexSize() {
    allocate(InteractionIdxSize,NumberInteractions);
    copy(InteractionIdxSize,0);
    InteractionIdxSize[Harmonic]=2;
    InteractionIdxSize[LJ612]=2;
    InteractionIdxSize[LJ612Cut]=2;
    InteractionIdxSize[LJ1012]=2;
    InteractionIdxSize[LJ1012Cut]=2;
    InteractionIdxSize[Coulomb]=2;
    InteractionIdxSize[Core12]=2;
    InteractionIdxSize[CoreLJ612]=2;
    InteractionIdxSize[ShiftedFENE]=2;
    InteractionIdxSize[QuadPlusHarmonic]=2;
    InteractionIdxSize[CoreExpandedCoreLJ612]=2;
    InteractionIdxSize[CoreExpandedLJ612]=2;
    InteractionIdxSize[AngleHarmonic]=3;
    InteractionIdxSize[DihedralPeriodic]=4;
    InteractionIdxSize[PlaneWallCoreLJ612]=1;
    InteractionIdxSize[PlaneWallLJ612Cut]=1;
    InteractionIdxSize[SphericShellCoreLJ612]=1;
    InteractionIdxSize[SphericShellLJ612Cut]=1;
    InteractionIdxSize[AnchorPointHarmonic]=1;
    InteractionIdxSize[DrivingConstantForce]=1;
  }

  static Vector<unsigned int> InteractionPrmSize;
  
  void InitInteractionParameterSize() {
    allocate(InteractionPrmSize,NumberInteractions);
    copy(InteractionPrmSize,0);
    InteractionPrmSize[Harmonic]=HarmonicNumberParameter;
    InteractionPrmSize[LJ612]=LJ612NumberParameter;
    InteractionPrmSize[LJ612Cut]=LJ612CutNumberParameter;
    InteractionPrmSize[LJ1012]=LJ1012NumberParameter;
    InteractionPrmSize[LJ1012Cut]=LJ1012CutNumberParameter;
    InteractionPrmSize[Coulomb]=CoulombNumberParameter;
    InteractionPrmSize[Core12]=Core12NumberParameter;
    InteractionPrmSize[CoreLJ612]=CoreLJ612NumberParameter;
    InteractionPrmSize[ShiftedFENE]=SfFENENumberParameter;
    InteractionPrmSize[QuadPlusHarmonic]=QuadHarmonicNumberParameter;
    InteractionPrmSize[AngleHarmonic]=AngleHarmonicNumberParameter;
    InteractionPrmSize[CoreExpandedCoreLJ612]=
        CoreExpandedCoreLJ612NumberParameter;
    InteractionPrmSize[CoreExpandedLJ612]=CoreExpandedLJ612NumberParameter;
    InteractionPrmSize[PlaneWallCoreLJ612]=ExtObjCoreLJ612NumberParameter;
    InteractionPrmSize[PlaneWallLJ612Cut]=ExtObjLJ612CutNumberParameter;
    InteractionPrmSize[SphericShellCoreLJ612]=ExtObjCoreLJ612NumberParameter;
    InteractionPrmSize[SphericShellLJ612Cut]=ExtObjLJ612CutNumberParameter;
    InteractionPrmSize[AnchorPointHarmonic]=ExtObjHarmonicNumberParameter;
    InteractionPrmSize[DrivingConstantForce]=DrivingConstantNumberParameter;
  }

}

#include "data/name/gao-enhanced-sampling.h"

namespace std {

  enum MetaInteractionName {
    GaoEnhancedSampling=0,
    NumberMetaInteractions
  };

  static Vector<unsigned int> InteractionMetaPrmSize;

  void InitInteractionMetaParameterSize() {
    allocate(InteractionMetaPrmSize,NumberInteractions);
    InteractionMetaPrmSize[GaoEnhancedSampling]=
      GaoEnhancedSamplingNumberParameter;
  }

}

#endif
