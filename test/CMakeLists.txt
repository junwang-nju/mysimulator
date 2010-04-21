
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall)

add_executable (test-vector.run test-vector.cxx)
target_link_libraries (test-vector.run blas Base)

add_executable (test-matrix.run test-matrix.cxx)
target_link_libraries (test-matrix.run blas Base)

add_executable (test-property-list.run test-property-list.cxx)
target_link_libraries (test-property-list.run blas Base)

add_executable (test-util.run test-util.cxx)
target_link_libraries (test-util.run Base)

add_executable (test-btree-node.run test-btree-node.cxx)

add_executable (test-btree.run test-btree.cxx)
target_link_libraries (test-btree.run Base)

add_executable (test-hash-func.run test-hash-func.cxx)
target_link_libraries (test-hash-func.run Base)

add_executable (test-var-parameter-key.run test-var-parameter-key.cxx)
target_link_libraries (test-var-parameter-key.run blas Base)

add_executable (test-fix-parameter-key.run test-fix-parameter-key.cxx)
target_link_libraries (test-fix-parameter-key.run blas Base)

add_executable (test-ref-parameter-key.run test-ref-parameter-key.cxx)
target_link_libraries (test-ref-parameter-key.run blas Base)

add_executable (test-var-parameter-list.run test-var-parameter-list.cxx)
target_link_libraries (test-var-parameter-list.run blas Base)

add_executable (test-fix-parameter-list.run test-fix-parameter-list.cxx)
target_link_libraries (test-fix-parameter-list.run blas Base)

add_executable (test-ref-parameter-list.run test-ref-parameter-list.cxx)
target_link_libraries (test-ref-parameter-list.run blas Base)

add_executable (test-var-free-space.run test-var-free-space.cxx)
target_link_libraries (test-var-free-space.run blas Base)

add_executable (test-fix-free-space.run test-fix-free-space.cxx)
target_link_libraries (test-fix-free-space.run blas Base)

add_executable (test-ref-free-space.run test-ref-free-space.cxx)
target_link_libraries (test-ref-free-space.run blas Base)

add_executable(test-chain.run test-chain.cxx)
target_link_libraries (test-chain.run Base)

add_executable(test-chain-node.run test-chain-node.cxx)
target_link_libraries (test-chain-node.run Base)

add_executable(test-distance-displacement-calc.run test-distance-displacement-calc.cxx)
target_link_libraries (test-distance-displacement-calc.run blas Base)

add_executable (test-var-periodic-box.run test-var-periodic-box.cxx)
target_link_libraries (test-var-periodic-box.run blas Base)

add_executable (test-fix-periodic-box.run test-fix-periodic-box.cxx)
target_link_libraries (test-fix-periodic-box.run blas Base)

add_executable (test-ref-periodic-box.run test-ref-periodic-box.cxx)
target_link_libraries (test-ref-periodic-box.run blas Base)

add_executable (test-var-distance-evaluate-direct.run test-var-distance-evaluate-direct.cxx)
target_link_libraries (test-var-distance-evaluate-direct.run blas Base)

add_executable (test-ref-distance-evaluate-direct.run test-ref-distance-evaluate-direct.cxx)
target_link_libraries (test-ref-distance-evaluate-direct.run blas Base)

add_executable (test-fix-distance-evaluate-direct.run test-fix-distance-evaluate-direct.cxx)
target_link_libraries (test-fix-distance-evaluate-direct.run blas Base)

add_executable (test-random-generator-mt-standard.run test-random-generator-mt-standard.cxx)
target_link_libraries (test-random-generator-mt-standard.run Base)

add_executable (test-random-generator-mt-dsfmt-sse2.run test-random-generator-mt-dsfmt.cxx)
set_source_files_properties (test-random-generator-mt-dsfmt.cxx COMPILE_FLAGS "-msse2 -malign-double -DHAVE_SSE2")
target_link_libraries (test-random-generator-mt-dsfmt-sse2.run Base blas)

add_executable (test-random-generator-mt-sfmt-sse2.run test-random-generator-mt-sfmt.cxx)
set_source_files_properties (test-random-generator-mt-sfmt.cxx COMPILE_FLAGS "-msse2 -malign-double -DHAVE_SSE2")
target_link_libraries (test-random-generator-mt-sfmt-sse2.run Base blas)

add_executable (test-random-generator-boxmuller-sse2.run test-random-generator-boxmuller.cxx)
set_source_files_properties (test-random-generator-boxmuller.cxx COMPILE_FLAGS "-msse2 -malign-double -DHAVE_SSE2")
target_link_libraries (test-random-generator-boxmuller-sse2.run Base blas)

add_executable (test-var-pair-storage.run test-var-pair-storage.cxx)
target_link_libraries (test-var-pair-storage.run blas Base)

add_executable (test-fix-pair-storage.run test-fix-pair-storage.cxx)
target_link_libraries (test-fix-pair-storage.run blas Base)

add_executable (test-ref-pair-storage.run test-ref-pair-storage.cxx)
target_link_libraries (test-ref-pair-storage.run blas Base)

add_executable (test-var-distance-evaluate-with-storage.run test-var-distance-evaluate-with-storage.cxx)
target_link_libraries (test-var-distance-evaluate-with-storage.run blas Base)

add_executable (test-fix-distance-evaluate-with-storage.run test-fix-distance-evaluate-with-storage.cxx)
target_link_libraries (test-fix-distance-evaluate-with-storage.run blas Base)

add_executable (test-var-interaction-list.run test-var-interaction-list.cxx)
target_link_libraries (test-var-interaction-list.run blas Base)

add_executable (test-ref-interaction-list.run test-ref-interaction-list.cxx)
target_link_libraries (test-ref-interaction-list.run blas Base)

add_executable (test-interaction-method.run test-interaction-method.cxx)
target_link_libraries (test-interaction-method.run blas Base)

add_executable (test-interaction-4list.run test-interaction-4list.cxx)
target_link_libraries (test-interaction-4list.run blas Base)

add_executable (test-interaction-particle-particle-harmonic.run test-interaction-particle-particle-harmonic.cxx)
target_link_libraries (test-interaction-particle-particle-harmonic.run blas Base)

add_executable (test-interaction-particle-particle-lj612.run test-interaction-particle-particle-lj612.cxx)
target_link_libraries (test-interaction-particle-particle-lj612.run blas Base)

add_executable (test-interaction-particle-particle-coulomb.run test-interaction-particle-particle-coulomb.cxx)
target_link_libraries (test-interaction-particle-particle-coulomb.run blas Base)

add_executable (test-interaction-particle-particle-lj612cut.run test-interaction-particle-particle-lj612cut.cxx)
target_link_libraries (test-interaction-particle-particle-lj612cut.run blas Base)

add_executable (test-interaction-particle-particle-quadplusharm.run test-interaction-particle-particle-quadplusharm.cxx)
target_link_libraries (test-interaction-particle-particle-quadplusharm.run blas Base)

add_executable (test-interaction-particle-particle-lj1012.run test-interaction-particle-particle-lj1012.cxx)
target_link_libraries (test-interaction-particle-particle-lj1012.run blas Base)

add_executable (test-interaction-4listset.run test-interaction-4listset.cxx)
target_link_libraries (test-interaction-4listset.run blas Base)

add_executable (test-minimizer-steep.run test-minimizer-steep.cxx)
target_link_libraries (test-minimizer-steep.run blas Base)

add_executable (test-minimizer-conjg.run test-minimizer-conjg.cxx)
target_link_libraries (test-minimizer-conjg.run blas Base)

add_executable (test-interaction-particle-particle-lj1012cut.run test-interaction-particle-particle-lj1012cut.cxx)
target_link_libraries (test-interaction-particle-particle-lj1012cut.run blas Base)

add_executable (test-minimizer-lbfgs.run test-minimizer-lbfgs.cxx)
target_link_libraries (test-minimizer-lbfgs.run blas Base)

add_executable (test-monomer-propagator.run test-monomer-propagator.cxx)
target_link_libraries (test-monomer-propagator.run blas Base)

add_executable (test-propagator-parameter-element.run test-propagator-parameter-element.cxx)
target_link_libraries (test-propagator-parameter-element.run blas Base)

add_executable (test-propagator.run test-propagator.cxx)
target_link_libraries (test-propagator.run Base blas)

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

add_executable (test-interaction-particle-particle-core12.run test-interaction-particle-particle-core12.cxx)
target_link_libraries (test-interaction-particle-particle-core12.run blas Base)

add_executable (test-interaction-particle-particle-corelj612.run test-interaction-particle-particle-corelj612.cxx)
target_link_libraries (test-interaction-particle-particle-corelj612.run blas Base)

