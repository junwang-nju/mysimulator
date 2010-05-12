
/**
 * @file parameter-id.h
 * @brief the identities of interaction parameters
 *
 * This file defines various kinds of identities for interaction
 * parameter.
 *
 * @note This should be updated when new interactions are included
 *       input the package.
 */

#ifndef _Parameter_ID_H_
#define _Parameter_ID_H_

namespace std {

  enum ParameterIDDeclaration {
    /**
     * @brief equilibrium radius for lennard-jones 6-12 potential
     */
    lj612_EqRadius=0,
    /**
     * @brief interaction strength for lennard-jones 6-12 potential
     */
    lj612_EqStrength,
    /**
     * @brief square of equilibrium radius for lennard-jones 6-12 potential
     */
    lj612_EqRadiusSQ,
    /**
     * @brief twelve times of interaction strength for lennard-jones 6-12 potential
     */
    lj612_TwlfEqStrength,
    /**
     * @brief equilibrium radius for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_EqRadius=0,
    /**
     * @brief equilibrium strength for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_EqStrength,
    /**
     * @brief cutoff radius for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_CutR,
    /**
     * @brief square of equilibrium radius for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_EqRadiusSQ,
    /**
     * @brief 6 order of actual sigma for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_Sigma6,
    /**
     * @brief actual strength for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_Strength,
    /**
     * @brief twelve times of actual strength for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_TwlfStrength,
    /**
     * @brief the shift potential at cutoff for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_Vc,
    /**
     * @brief the shift strength at cutoff for lennard-jones 6-12 potential with cutoff
     */
    lj612cut_Kc,
    /**
     * @brief equilibrium length of the harmonic interaction
     */
    harmonic_EqLength=0,
    /**
     * @brief equilibrium strength of the harmonic interaction
     */
    harmonic_EqStrength,
    /**
     * @brief double of equilibrium strength of harmonic interaction
     */
    harmonic_DualEqStrength,
    /**
     * @brief equilibrium radius for lennard-jones 10-12 potential
     */
    lj1012_EqRadius=0,
    /**
     * @brief interaction strength for lennard-jones 10-12 potential
     */
    lj1012_EqStrength,
    /**
     * @brief square of equilibrium radius for lennard-jones 10-12 potential
     */
    lj1012_EqRadiusSQ,
    /**
     * @brief sixty times of interaction strength for lennard-jones 6-12 potential
     */
    lj1012_SixtyEqStrength,
    /**
     * @brief strength for coulomb interaction
     */
    coulomb_Strength,
    /**
     * @brief strength for coulomb interaction with distance-dependent dielectric
     */
    coulombwde_Strength,
    /**
     * @brief double of strength for coulomb interaction with distance-dependent dielectric
     */
    coulombwde_DualStrength,
    /**
     * @brief equilibrium length for harmonic plus quadruple interaction
     */
    quadharm_EqLength=0,
    /**
     * @brief equilibrium strength of quadruple part for harmonic plus quadruple interaction
     */
    quadharm_EqQuadStrength,
    /**
     * @brief equilibrium strength of harmonic part for harmonic plus quadruple interaction
     */
    quadharm_EqHarmStrength,
    /**
     * @brief four times of equilibrium strength of quadruple part for harmonic plus quadruple interaction
     */
    quadharm_FourEqQuadStrength,
    /**
     * @brief twice of equilibrium strength of harmonic part for harmonic plus quadruple interaction
     */
    quadharm_DualEqHarmStrength
  };

}

#endif
