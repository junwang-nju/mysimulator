
include_directories (${TEST_SOURCE_DIR}/include)
add_definitions (-Wall)

add_executable (test-vector.run test-vector.cxx)
target_link_libraries (test-vector.run blas)

add_executable (test-matrix.run test-matrix.cxx)
target_link_libraries (test-matrix.run blas)

add_executable (test-list.run test-list.cxx)
target_link_libraries (test-list.run blas)

add_executable (test-btree.run test-btree.cxx)
target_link_libraries (test-btree.run blas)

add_executable (test-geometry.run test-geometry.cxx)
target_link_libraries (test-geometry.run blas)

add_executable (test-hash-func.run test-hash-func.cxx)

add_executable (test-unique-parameter.run test-unique-parameter.cxx)
target_link_libraries (test-unique-parameter.run blas)
set_source_files_properties (test-unique-parameter.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

add_executable (test-parameter-list.run test-parameter-list.cxx)
target_link_libraries (test-parameter-list.run blas)

add_executable(test-chain.run test-chain.cxx)
target_link_libraries (test-chain.run blas)

add_executable(test-buffer.run test-buffer.cxx)
target_link_libraries (test-buffer.run blas)

add_executable (test-referable-object.run test-referable-object.cxx)
target_link_libraries (test-referable-object.run blas)

add_executable (test-map.run test-map.cxx)
target_link_libraries (test-map.run blas)

add_executable (test-random.run test-random.cxx)
target_link_libraries (test-random.run blas)
set_source_files_properties (test-random.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

add_executable (test-interaction.run test-interaction.cxx)
target_link_libraries(test-interaction.run blas)

add_executable (test-minimizer.run test-minimizer.cxx)
target_link_libraries(test-minimizer.run blas)

#add_executable (test-interaction-pairwise-base.run test-interaction-pairwise-base.cxx)
#target_link_libraries (test-interaction-pairwise-base.run blas)

#add_executable (test-interaction-pairwise-harmonic.run test-interaction-pairwise-harmonic.cxx)
#target_link_libraries (test-interaction-pairwise-harmonic.run blas)

#add_executable (test-interaction-pairwise-lj612.run test-interaction-pairwise-lj612.cxx)
#target_link_libraries (test-interaction-pairwise-lj612.run blas)

#add_executable (test-interaction-pairwise-core12.run test-interaction-pairwise-core12.cxx)
#target_link_libraries (test-interaction-pairwise-core12.run blas)

#add_executable (test-interaction-pairwise-lj612cut.run test-interaction-pairwise-lj612cut.cxx)
#target_link_libraries (test-interaction-pairwise-lj612cut.run blas)

#add_executable (test-interaction-pairwise-lj1012.run test-interaction-pairwise-lj1012.cxx)
#target_link_libraries (test-interaction-pairwise-lj1012.run blas)

#add_executable (test-interaction-pairwise-lj1012cut.run test-interaction-pairwise-lj1012cut.cxx)
#target_link_libraries (test-interaction-pairwise-lj1012cut.run blas)

#add_executable (test-interaction-pairwise-corelj612.run test-interaction-pairwise-corelj612.cxx)
#target_link_libraries (test-interaction-pairwise-corelj612.run blas)

#add_executable (test-interaction-pairwise-coulomb.run test-interaction-pairwise-coulomb.cxx)
#target_link_libraries (test-interaction-pairwise-coulomb.run blas)

#add_executable (test-interaction-pairwise-quadharm.run test-interaction-pairwise-quadharm.cxx)
#target_link_libraries (test-interaction-pairwise-quadharm.run blas)

#add_executable (test-minimizer-buffer-base.run test-minimizer-buffer-base.cxx)
#target_link_libraries (test-minimizer-buffer-base.run blas)

#add_executable (test-line-minimizer-buffer-base.run test-line-minimizer-buffer-base.cxx)
#target_link_libraries (test-line-minimizer-buffer-base.run blas)

#add_executable (test-tracking-line-minimizer-buffer.run test-tracking-line-minimizer-buffer.cxx)
#target_link_libraries (test-tracking-line-minimizer-buffer.run blas)

#add_executable (test-steep-minimizer-buffer.run test-steep-minimizer-buffer.cxx)
#target_link_libraries (test-steep-minimizer-buffer.run blas)

#add_executable (test-conjg-minimizer-buffer.run test-conjg-minimizer-buffer.cxx)
#target_link_libraries (test-conjg-minimizer-buffer.run blas)

#add_executable (test-lbfgs-minimizer-buffer.run test-lbfgs-minimizer-buffer.cxx)
#target_link_libraries (test-lbfgs-minimizer-buffer.run blas)

add_executable (test-propagator-conste-vverlet.run test-propagator-conste-vverlet.cxx)
target_link_libraries (test-propagator-conste-vverlet.run blas)

add_executable (test-propagator-berendsen-vverlet.run test-propagator-berendsen-vverlet.cxx)
target_link_libraries (test-propagator-berendsen-vverlet.run blas)

add_executable (test-propagator-langevin-vverlet.run test-propagator-langevin-vverlet.cxx)
target_link_libraries (test-propagator-langevin-vverlet.run blas)

#add_executable (test-system-op.run test-system-op.cxx)
#target_link_libraries (test-system-op.run blas)

#add_executable (test-interaction-core-expand-corelj612.run test-interaction-core-expand-corelj612.cxx)
#target_link_libraries (test-interaction-core-expand-corelj612.run blas)

#add_executable (test-interaction-core-expand-lj612.run test-interaction-core-expand-lj612.cxx)
#target_link_libraries (test-interaction-core-expand-lj612.run blas)

#add_executable (test-interaction-particle-centroid-harmonic.run test-interaction-particle-centroid-harmonic.cxx)
#target_link_libraries (test-interaction-particle-centroid-harmonic.run blas)

#add_executable (test-interaction-centroid-harmonic.run test-interaction-centroid-harmonic.cxx)
#target_link_libraries (test-interaction-centroid-harmonic.run blas)

#add_executable (test-interaction-pairwise-fene.run test-interaction-pairwise-fene.cxx)
#target_link_libraries (test-interaction-pairwise-fene.run blas)

#add_executable (test-interaction-angle-harmonic.run test-interaction-angle-harmonic.cxx)
#target_link_libraries (test-interaction-angle-harmonic.run blas)

#add_executable (test-interaction-dihedral-periodic.run test-interaction-dihedral-periodic.cxx)
#target_link_libraries (test-interaction-dihedral-periodic.run blas)

#add_executable (test-interaction-wall-base.run test-interaction-wall-base.cxx)
#target_link_libraries (test-interaction-wall-base.run blas)

#add_executable (test-distance-evaluate-wall.run test-distance-evaluate-wall.cxx)
#target_link_libraries (test-distance-evaluate-wall.run blas)

#add_executable (test-interaction-wall-corelj612.run test-interaction-wall-corelj612.cxx)
#target_link_libraries (test-interaction-wall-corelj612.run blas)

#add_executable (test-interaction-wall-lj612cut.run test-interaction-wall-lj612cut.cxx)
#target_link_libraries (test-interaction-wall-lj612cut.run blas)

#add_executable (test-interaction-sphere-wall-lj612cut.run test-interaction-sphere-wall-lj612cut.cxx)
#target_link_libraries (test-interaction-sphere-wall-lj612cut.run blas)

#add_executable (test-interaction-sphere-wall-corelj612.run test-interaction-sphere-wall-corelj612.cxx)
#target_link_libraries (test-interaction-sphere-wall-corelj612.run blas)

#add_executable (test-interaction-anchor-harmonic.run test-interaction-anchor-harmonic.cxx)
#target_link_libraries (test-interaction-anchor-harmonic.run blas)

#add_executable (test-interaction-centroid-anchor-harmonic.run test-interaction-centroid-anchor-harmonic.cxx)
#target_link_libraries (test-interaction-centroid-anchor-harmonic.run blas)

#add_executable (test-pdb-data.run test-pdb-data.cxx)
#target_link_libraries (test-pdb-data.run blas)

add_executable (test-lapack.run test-lapack.cxx)
target_link_libraries (test-lapack.run lapack)

#add_executable (test-interaction-calc.run test-interaction-calc.cxx)
#target_link_libraries (test-interaction-calc.run blas)

add_executable (test-neighbor-list.run test-neighbor-list.cxx)
target_link_libraries (test-neighbor-list.run blas)

add_executable (test-lattice.run test-lattice.cxx)
target_link_libraries (test-lattice.run blas)

add_executable (test-boundary.run test-boundary.cxx)
target_link_libraries (test-boundary.run blas)

add_executable (test-meta-calc.run test-meta-calc.cxx)
target_link_libraries (test-meta-calc.run blas)

add_executable (test-simple-data-output.run test-simple-data-output.cxx)
target_link_libraries (test-simple-data-output.run blas)

add_executable (test-simple-data-input.run test-simple-data-input.cxx)
target_link_libraries (test-simple-data-input.run blas)

add_executable (test-pdb-info.run test-pdb-info.cxx)
target_link_libraries (test-pdb-info.run blas)

add_executable (test-pdb2contact.run test-pdb2contact.cxx)
target_link_libraries (test-pdb2contact.run blas)

add_executable (test-unit.run test-unit.cxx)
target_link_libraries (test-unit.run blas)

########################
#add_executable (test-pdb-data-structure-op.run test-pdb-data-structure-op.cxx)
#target_link_libraries (test-pdb-data-structure-op.run Base blas)


