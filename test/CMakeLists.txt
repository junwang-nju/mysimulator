
include_directories (${TEST_SOURCE_DIR}/include)
link_directories (${TEST_SOURCE_DIR}/lib)
add_definitions (-Wall)

add_executable (test-vector-impl.run test-vector-impl.cxx)
target_link_libraries (test-vector-impl.run blas Base)

add_executable (test-util.run test-util.cxx)
target_link_libraries (test-util.run Base)

add_executable (test-btree-node.run test-btree-node.cxx)

add_executable (test-btree.run test-btree.cxx)
target_link_libraries (test-btree.run Base)

add_executable (test-var-vector.run test-var-vector.cxx)
target_link_libraries (test-var-vector.run blas Base)

add_executable (test-fix-vector.run test-fix-vector.cxx)
target_link_libraries (test-fix-vector.run blas Base)

add_executable (test-ref-vector.run test-ref-vector.cxx)
target_link_libraries (test-ref-vector.run blas Base)

add_executable (test-hash-func.run test-hash-func.cxx)
target_link_libraries (test-hash-func.run Base)

add_executable (test-var-matrix-rectangle.run test-var-matrix-rectangle.cxx)
target_link_libraries (test-var-matrix-rectangle.run blas Base)

add_executable (test-fix-matrix-rectangle.run test-fix-matrix-rectangle.cxx)
target_link_libraries (test-fix-matrix-rectangle.run blas Base)

add_executable (test-ref-matrix-rectangle.run test-ref-matrix-rectangle.cxx)
target_link_libraries (test-ref-matrix-rectangle.run blas Base)

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

add_executable (test-var-matrix-triangle.run test-var-matrix-triangle.cxx)
target_link_libraries (test-var-matrix-triangle.run blas Base)

add_executable (test-ref-matrix-triangle.run test-ref-matrix-triangle.cxx)
target_link_libraries (test-ref-matrix-triangle.run blas Base)

add_executable (test-fix-matrix-triangle.run test-fix-matrix-triangle.cxx)
target_link_libraries (test-fix-matrix-triangle.run blas Base)

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

add_executable (test-var-property-list.run test-var-property-list.cxx)
target_link_libraries (test-var-property-list.run blas Base)

add_executable (test-ref-property-list.run test-ref-property-list.cxx)
target_link_libraries (test-ref-property-list.run blas Base)

add_executable (test-var-interaction-list.run test-var-interaction-list.cxx)
target_link_libraries (test-var-interaction-list.run blas Base)

add_executable (test-ref-interaction-list.run test-ref-interaction-list.cxx)
target_link_libraries (test-ref-interaction-list.run blas Base)

