
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall)

add_executable (test-vector.run test-vector.cxx)
target_link_libraries (test-vector.run blas)

add_executable (test-matrix.run test-matrix.cxx)
target_link_libraries (test-matrix.run blas)

add_executable (test-property-list.run test-property-list.cxx)
target_link_libraries (test-property-list.run blas)

add_executable (test-btree-node.run test-btree-node.cxx)

add_executable (test-btree.run test-btree.cxx)

add_executable (test-hash-func.run test-hash-func.cxx)

add_executable (test-parameter-key.run test-parameter-key.cxx)
target_link_libraries (test-parameter-key.run blas)

add_executable (test-unique-parameter.run test-unique-parameter.cxx)
target_link_libraries (test-unique-parameter.run blas)

add_executable (test-parameter-list.run test-parameter-list.cxx)
target_link_libraries (test-parameter-list.run blas)

add_executable (test-free-space.run test-free-space.cxx)
target_link_libraries (test-free-space.run blas)

add_executable(test-chain.run test-chain.cxx)

add_executable(test-chain-node.run test-chain-node.cxx)

add_executable(test-distance-calc.run test-distance-calc.cxx)
target_link_libraries (test-distance-calc.run blas)

add_executable (test-periodic-box.run test-periodic-box.cxx)
target_link_libraries (test-periodic-box.run blas)

add_executable (test-distance-calc-simplebuffer.run test-distance-calc-simplebuffer.cxx)
target_link_libraries (test-distance-calc-simplebuffer.run blas)

add_executable (test-pair-item.run test-pair-item.cxx)

add_executable (test-displacement-calc-direct.run test-displacement-calc-direct.cxx)
target_link_libraries (test-displacement-calc-direct.run blas)

add_executable (test-pair-storage.run test-pair-storage.cxx)
target_link_libraries (test-pair-storage.run blas)

add_executable (test-distance-calc-pairbuffer.run test-distance-calc-pairbuffer.cxx)
target_link_libraries (test-distance-calc-pairbuffer.run blas)

add_executable (test-unique-parameter-128bit.run test-unique-parameter-128bit.cxx)
target_link_libraries (test-unique-parameter-128bit.run blas)
set_source_files_properties (test-unique-parameter-128bit.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")

add_executable (test-random-generator-mt-standard.run test-random-generator-mt-standard.cxx)
target_link_libraries (test-random-generator-mt-standard.run blas)

add_executable (test-random-generator-mt-dsfmt-sse2.run test-random-generator-mt-dsfmt.cxx)
set_source_files_properties (test-random-generator-mt-dsfmt.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")
target_link_libraries (test-random-generator-mt-dsfmt-sse2.run blas)

add_executable (test-random-generator-mt-sfmt-sse2.run test-random-generator-mt-sfmt.cxx)
set_source_files_properties (test-random-generator-mt-sfmt.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")
target_link_libraries (test-random-generator-mt-sfmt-sse2.run blas)

add_executable (test-random-generator-boxmuller-sse2.run test-random-generator-boxmuller.cxx)
set_source_files_properties (test-random-generator-boxmuller.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")
target_link_libraries (test-random-generator-boxmuller-sse2.run blas)

add_executable (test-interaction-pairwise-base.run test-interaction-pairwise-base.cxx)
target_link_libraries (test-interaction-pairwise-base.run blas)

add_executable (test-interaction-pairwise-harmonic.run test-interaction-pairwise-harmonic.cxx)
target_link_libraries (test-interaction-pairwise-harmonic.run blas)

add_executable (test-interaction-pairwise-lj612.run test-interaction-pairwise-lj612.cxx)
target_link_libraries (test-interaction-pairwise-lj612.run blas)

add_executable (test-interaction-pairwise-core12.run test-interaction-pairwise-core12.cxx)
target_link_libraries (test-interaction-pairwise-core12.run blas)

add_executable (test-interaction-pairwise-lj612cut.run test-interaction-pairwise-lj612cut.cxx)
target_link_libraries (test-interaction-pairwise-lj612cut.run blas)

add_executable (test-interaction-pairwise-lj1012.run test-interaction-pairwise-lj1012.cxx)
target_link_libraries (test-interaction-pairwise-lj1012.run blas)

add_executable (test-interaction-pairwise-lj1012cut.run test-interaction-pairwise-lj1012cut.cxx)
target_link_libraries (test-interaction-pairwise-lj1012cut.run blas)

add_executable (test-interaction-pairwise-corelj612.run test-interaction-pairwise-corelj612.cxx)
target_link_libraries (test-interaction-pairwise-corelj612.run blas)

add_executable (test-interaction-pairwise-coulomb.run test-interaction-pairwise-coulomb.cxx)
target_link_libraries (test-interaction-pairwise-coulomb.run blas)

add_executable (test-interaction-pairwise-quadharm.run test-interaction-pairwise-quadharm.cxx)
target_link_libraries (test-interaction-pairwise-quadharm.run blas)

add_executable (test-minimizer-buffer-base.run test-minimizer-buffer-base.cxx)
target_link_libraries (test-minimizer-buffer-base.run blas)

add_executable (test-line-minimizer-buffer-base.run test-line-minimizer-buffer-base.cxx)
target_link_libraries (test-line-minimizer-buffer-base.run blas)

add_executable (test-tracking-line-minimizer-buffer.run test-tracking-line-minimizer-buffer.cxx)
target_link_libraries (test-tracking-line-minimizer-buffer.run blas)

add_executable (test-steep-minimizer-buffer.run test-steep-minimizer-buffer.cxx)
target_link_libraries (test-steep-minimizer-buffer.run blas)

add_executable (test-conjg-minimizer-buffer.run test-conjg-minimizer-buffer.cxx)
target_link_libraries (test-conjg-minimizer-buffer.run blas)

add_executable (test-lbfgs-minimizer-buffer.run test-lbfgs-minimizer-buffer.cxx)
target_link_libraries (test-lbfgs-minimizer-buffer.run blas)

add_executable (test-propagator-conste-vverlet.run test-propagator-conste-vverlet.cxx)
target_link_libraries (test-propagator-conste-vverlet.run blas)

add_executable (test-propagator-berendsen-vverlet.run test-propagator-berendsen-vverlet.cxx)
target_link_libraries (test-propagator-berendsen-vverlet.run blas)

add_executable (test-propagator-langevin-vverlet.run test-propagator-langevin-vverlet.cxx)
target_link_libraries (test-propagator-langevin-vverlet.run blas)

#add_executable (test-system-op.run test-system-op.cxx)
#target_link_libraries (test-system-op.run blas)

add_executable (test-interaction-core-expand-corelj612.run test-interaction-core-expand-corelj612.cxx)
target_link_libraries (test-interaction-core-expand-corelj612.run blas)

add_executable (test-interaction-core-expand-lj612.run test-interaction-core-expand-lj612.cxx)
target_link_libraries (test-interaction-core-expand-lj612.run blas)

add_executable (test-interaction-particle-centroid-harmonic.run test-interaction-particle-centroid-harmonic.cxx)
target_link_libraries (test-interaction-particle-centroid-harmonic.run blas)

add_executable (test-interaction-centroid-harmonic.run test-interaction-centroid-harmonic.cxx)
target_link_libraries (test-interaction-centroid-harmonic.run blas)

add_executable (test-interaction-pairwise-fene.run test-interaction-pairwise-fene.cxx)
target_link_libraries (test-interaction-pairwise-fene.run blas)

add_executable (test-interaction-angle-harmonic.run test-interaction-angle-harmonic.cxx)
target_link_libraries (test-interaction-angle-harmonic.run blas)

add_executable (test-interaction-dihedral-periodic.run test-interaction-dihedral-periodic.cxx)
target_link_libraries (test-interaction-dihedral-periodic.run blas)

#add_executable (test-interaction-wall-base.run test-interaction-wall-base.cxx)
#target_link_libraries (test-interaction-wall-base.run blas)

#add_executable (test-distance-evaluate-wall.run test-distance-evaluate-wall.cxx)
#target_link_libraries (test-distance-evaluate-wall.run blas)

add_executable (test-interaction-wall-corelj612.run test-interaction-wall-corelj612.cxx)
target_link_libraries (test-interaction-wall-corelj612.run blas)

add_executable (test-interaction-wall-lj612cut.run test-interaction-wall-lj612cut.cxx)
target_link_libraries (test-interaction-wall-lj612cut.run blas)

add_executable (test-interaction-sphere-wall-lj612cut.run test-interaction-sphere-wall-lj612cut.cxx)
target_link_libraries (test-interaction-sphere-wall-lj612cut.run blas)

add_executable (test-interaction-sphere-wall-corelj612.run test-interaction-sphere-wall-corelj612.cxx)
target_link_libraries (test-interaction-sphere-wall-corelj612.run blas)

add_executable (test-interaction-ancher-harmonic.run test-interaction-ancher-harmonic.cxx)
target_link_libraries (test-interaction-ancher-harmonic.run blas)

#add_executable (test-pdb-data.run test-pdb-data.cxx)
#target_link_libraries (test-pdb-data.run blas)

add_executable (test-lapack.run test-lapack.cxx)
target_link_libraries (test-lapack.run lapack)

add_executable (test-interaction-calc.run test-interaction-calc.cxx)
target_link_libraries (test-interaction-calc.run blas)

add_executable (test-neighbor-list.run test-neighbor-list.cxx)
target_link_libraries (test-neighbor-list.run blas)

add_executable (test-lattice-sq2d-enum.run test-lattice-sq2d-enum.cxx)
target_link_libraries (test-lattice-sq2d-enum.run blas)

########################
#add_executable (test-pdb-data-structure-op.run test-pdb-data-structure-op.cxx)
#target_link_libraries (test-pdb-data-structure-op.run Base blas)


