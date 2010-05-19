
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall)

add_executable (test-vector.run test-vector.cxx)
target_link_libraries (test-vector.run blas)

add_executable (test-matrix.run test-matrix.cxx)
target_link_libraries (test-matrix.run blas)

add_executable (test-property-list.run test-property-list.cxx)
target_link_libraries (test-property-list.run blas)

add_executable (test-util.run test-util.cxx)

add_executable (test-btree-node.run test-btree-node.cxx)

add_executable (test-btree.run test-btree.cxx)

add_executable (test-hash-func.run test-hash-func.cxx)
target_link_libraries (test-hash-func.run Base)

add_executable (test-parameter-key.run test-parameter-key.cxx)
target_link_libraries (test-parameter-key.run blas Base)

add_executable (test-unique-parameter.run test-unique-parameter.cxx)

add_executable (test-parameter-list.run test-parameter-list.cxx)
target_link_libraries (test-parameter-list.run blas Base)

add_executable (test-free-space.run test-free-space.cxx)
target_link_libraries (test-free-space.run blas)

add_executable(test-chain.run test-chain.cxx)

add_executable(test-chain-node.run test-chain-node.cxx)

add_executable(test-distance-displacement-calc.run test-distance-displacement-calc.cxx)
target_link_libraries (test-distance-displacement-calc.run blas)

add_executable (test-periodic-box.run test-periodic-box.cxx)
target_link_libraries (test-periodic-box.run blas)

add_executable (test-distance-evaluate-base.run test-distance-evaluate-base.cxx)
target_link_libraries (test-distance-evaluate-base.run blas)

add_executable (test-distance-evaluate-direct.run test-distance-evaluate-direct.cxx)
target_link_libraries (test-distance-evaluate-direct.run blas)

add_executable (test-matrix-storage-item.run test-matrix-storage-item.cxx)
target_link_libraries (test-matrix-storage-item.run blas)

add_executable (test-matrix-storage.run test-matrix-storage.cxx)
target_link_libraries (test-matrix-storage.run blas)

add_executable (test-distance-evaluate-with-storage.run test-distance-evaluate-with-storage.cxx)
target_link_libraries (test-distance-evaluate-with-storage.run blas)

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
target_link_libraries (test-random-generator-mt-sfmt-sse2.run Base blas)

add_executable (test-random-generator-boxmuller-sse2.run test-random-generator-boxmuller.cxx)
set_source_files_properties (test-random-generator-boxmuller.cxx COMPILE_FLAGS "-msse2 -DHAVE_SSE2")
target_link_libraries (test-random-generator-boxmuller-sse2.run blas)

add_executable (test-interaction-method.run test-interaction-method.cxx)
target_link_libraries (test-interaction-method.run blas)

add_executable (test-interaction-4list.run test-interaction-4list.cxx)
target_link_libraries (test-interaction-4list.run blas Base)

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

add_executable (test-interaction-4listset.run test-interaction-4listset.cxx)
target_link_libraries (test-interaction-4listset.run blas Base)

add_executable (test-minimizer-base.run test-minimizer-base.cxx)
target_link_libraries (test-minimizer-base.run blas)

add_executable (test-minimizer-line-base.run test-minimizer-line-base.cxx)
target_link_libraries (test-minimizer-line-base.run blas)

add_executable (test-minimizer-parameter-flat-4propertylist.run test-minimizer-parameter-flat-4propertylist.cxx)
target_link_libraries (test-minimizer-parameter-flat-4propertylist.run blas)

add_executable (test-minimizer-parameter-hierarchy-4propertylist.run test-minimizer-parameter-hierarchy-4propertylist.cxx)
target_link_libraries (test-minimizer-parameter-hierarchy-4propertylist.run blas)

add_executable (test-minimizer-func-4propertylist.run test-minimizer-func-4propertylist.cxx)
target_link_libraries (test-minimizer-func-4propertylist.run blas)

add_executable (test-minimizer-line-base-4propertylist-op.run test-minimizer-line-base-4propertylist-op.cxx)
target_link_libraries (test-minimizer-line-base-4propertylist-op.run blas)

add_executable (test-minimizer-line-tracking.run test-minimizer-line-tracking.cxx)
target_link_libraries (test-minimizer-line-tracking.run blas)

add_executable (test-minimizer-line-tracking-4propertylist-op.run test-minimizer-line-tracking-4propertylist-op.cxx)
target_link_libraries (test-minimizer-line-tracking-4propertylist-op.run blas)

add_executable (test-minimizer-steep.run test-minimizer-steep.cxx)
target_link_libraries (test-minimizer-steep.run blas)

add_executable (test-minimizer-steep-4propertylist-op.run test-minimizer-steep-4propertylist-op.cxx)
target_link_libraries (test-minimizer-steep-4propertylist-op.run blas)

add_executable (test-minimizer-conjg.run test-minimizer-conjg.cxx)
target_link_libraries (test-minimizer-conjg.run blas)

add_executable (test-minimizer-conjg-4propertylist-op.run test-minimizer-conjg-4propertylist-op.cxx)
target_link_libraries (test-minimizer-conjg-4propertylist-op.run blas)

add_executable (test-minimizer-lbfgs.run test-minimizer-lbfgs.cxx)
target_link_libraries (test-minimizer-lbfgs.run blas)

add_executable (test-minimizer-lbfgs-4propertylist-op.run test-minimizer-lbfgs-4propertylist-op.cxx)
target_link_libraries (test-minimizer-lbfgs-4propertylist-op.run blas)

add_executable (test-monomer-propagator.run test-monomer-propagator.cxx)
target_link_libraries (test-monomer-propagator.run blas)

add_executable (test-monomer-propagator-op.run test-monomer-propagator-op.cxx)
target_link_libraries (test-monomer-propagator-op.run blas)

add_executable (test-monomer-propagator-particle-conste-vverlet.run test-monomer-propagator-particle-conste-vverlet.cxx)
target_link_libraries (test-monomer-propagator-particle-conste-vverlet.run blas)

add_executable (test-propagator.run test-propagator.cxx)
target_link_libraries (test-propagator.run blas)

add_executable (test-propagator-op.run test-propagator-op.cxx)
target_link_libraries (test-propagator-op.run blas)

add_executable (test-propagator-berendsen-vverlet.run test-propagator-berendsen-vverlet.cxx)
target_link_libraries (test-propagator-berendsen-vverlet.run Base blas)

add_executable (test-propagator-langevin-vverlet.run test-propagator-langevin-vverlet.cxx)
target_link_libraries (test-propagator-langevin-vverlet.run Base blas)

add_executable (test-pdb-data-structure-op.run test-pdb-data-structure-op.cxx)
target_link_libraries (test-pdb-data-structure-op.run Base blas)

add_executable (test-interaction-angle-harmonic.run test-interaction-angle-harmonic.cxx)
target_link_libraries (test-interaction-angle-harmonic.run blas Base)

add_executable (test-interaction-dihedral-periodic.run test-interaction-dihedral-periodic.cxx)
target_link_libraries (test-interaction-dihedral-periodic.run blas Base)


