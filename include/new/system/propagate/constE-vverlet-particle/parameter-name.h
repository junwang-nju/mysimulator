
#ifndef _System_Propagate_ConstE_VelocityVerlet_Particle_Parameter_Name_H_
#define _System_Propagate_ConstE_VelocityVerlet_Particle_Parameter_Name_H_

namespace mysimulator {

  enum ParameterConstEVelVerletParticleName {
    CEVVerletParticleTimeStep=0,
    CEVVerletParticleMass,
    CEVVerletParticleNegHTimeIMass,
    CEVVerletParticleUpdateHTIMFunc,
    CEVVerletParticleBfMoveFunc,
    CEVVerletParticleAfMoveFunc,
    NumberParameterConstEVelVerletParticle
  };

}

#endif

